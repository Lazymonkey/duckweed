#include "duckweed.h"

void handle_client(int clientdesc)
{
    char buff[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    if((read(clientdesc, buff, BUFF_SIZE)) < 0) {
        sprintf(buff, "HTTP/1.1 404 \r\nServer: my lhttp server\r\nContent-Type:\
                text/html\r\nContent-Length: %d\r\n\r\n%s", (int)strlen("<html><h1>\
                Not Found</h1></html>"), "<html><h1>Not Found</h1></html>");
        send(clientdesc, buff, strlen(buff), 0);
        close(clientdesc);
    }
    parse_request(clientdesc, buff);
}


void parse_request(int clientdesc, char *buff)
{
    char request_method[10]={0};
    char request_path[256]={0};
    char http_version[12]={0};
    char request_content[256] ={0};
    parse_request_header(buff, request_method, request_path, http_version, request_content);
    send_response( clientdesc, request_path, http_version, request_content);
}

void parse_request_header(char *buff, char *method, char *path, char *version,  char *rc)
{
    char *ptr = buff;
    char tmp[256] ={0};
    //request method
    sscanf(ptr,"%[^ ]", method);

    //request path
    ptr = ptr + strlen(method) + 1;
    sscanf(ptr, "%[^ ]", path);

    //http version not used in application
    ptr = ptr + strlen(path) + 1;
    sscanf(ptr, "%[^\r]", version);

    //ignore all string begin after HTTP/version until \r\n\r\n
    ptr = ptr + strlen(version) + 2;
    while(ptr[0] !='\r')
    {
        sscanf(ptr,"%[^\r]", tmp);
        ptr = ptr + strlen(tmp) + 2;
    }
    //get post information
    ptr = ptr + 2;
    strcpy(rc, ptr);
}
