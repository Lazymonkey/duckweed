#include "duckweed.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void get_serv_date(char *curtime)
{
    struct tm *timenow;
    time_t now;
    time(&now);
    timenow = localtime(&now);
    strcpy(curtime, asctime(timenow));
}

void get_html_body(const char *filename, char *rev, char *mime_type)
{
    struct stat buf;
    char buff[100] ={0};
    getcwd(buff, sizeof(buff));
    strcat(buff, filename);
    stat(buff, &buf);

   if(S_ISDIR(buf.st_mode)) {
        strcat(buff, "index.htm");
        strcpy(mime_type, "text/html");
        file_exist(buff) ? get_file_contents(buff, rev) : get_dir_list(buff, rev);
   }

   if(S_ISREG(buf.st_mode)) {
        get_file_contents(buff, rev);
        get_mime_type(buff, mime_type);
   }
}

void get_file_contents(const char *filename, char *rev)
{
    struct stat  buff;
    int file_size;
    int fd;

    //get file size
    if((stat(filename, &buff)) < 0)
        file_size = 0;

    file_size = buff.st_size;

    if(access(filename, R_OK) < 0)
        perror("Permission denied");

    fd = open(filename, O_RDONLY);
    read(fd, rev, file_size);
    close(fd);
}

void get_dir_list(const char *path, char *rev)
{
    struct dirent *dirp;
    DIR *dp;
    char tmp[1024]={0};

    sprintf(tmp, "<html>\n<head>\n<title>Browse directory %s</title>\n</head>\n\
            <body><h3>Directory %s</h3>\n<hr />\n<ul>\n", path, path );
    strcat(rev, tmp);

    if((dp = opendir(path)) == NULL)
        perror("can not open dir");

    while((dirp = readdir(dp)) != NULL) {

        if ( strcmp(dirp->d_name, ".") != 0) {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "\t<li><a href=\"%s%s\">%s</a></li>\n", path, dirp->d_name, dirp->d_name);
            strcat(rev, tmp);
        }
    }
    closedir(dp);
}

int file_exist(const char *filename)
{
    struct stat buff;

    if(stat(filename, &buff) < 0) {

        if(ENOENT == errno)
            return 0;
    }
    return 1;
}

void get_mime_type( const char *name, char *ret )
{
    char *dot, *buf;

    dot = strrchr(name, '.');

    /* Text */
    if ( strcmp(dot, ".txt") == 0 ) {
        buf = "text/plain";
    } else if ( strcmp( dot, ".css" ) == 0 ) {
        buf = "text/css";
    } else if ( strcmp( dot, ".js" ) == 0 ) {
        buf = "text/javascript";
    } else if ( strcmp(dot, ".xml") == 0 || strcmp(dot, ".xsl") == 0 ) {
        buf = "text/xml";
    } else if ( strcmp(dot, ".xhtm") == 0 || strcmp(dot, ".xhtml") == 0 ||\
            strcmp(dot, ".xht") == 0 ) {
        buf = "application/xhtml+xml";
    } else if ( strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0 || \
            strcmp(dot, ".shtml") == 0 || strcmp(dot, ".hts") == 0 ) {
        buf = "text/html";
    }
    /* Images */
    else if ( strcmp( dot, ".gif" ) == 0 ) {
        buf = "image/gif";
    } else if ( strcmp( dot, ".png" ) == 0 ) {
        buf = "image/png";
    } else if ( strcmp( dot, ".bmp" ) == 0 ) {
        buf = "application/x-MS-bmp";
    } else if ( strcmp( dot, ".jpg" ) == 0 || strcmp( dot, ".jpeg" ) == 0 ||\
            strcmp( dot, ".jpe" ) == 0 || strcmp( dot, ".jpz" ) == 0 ) {
        buf = "image/jpeg";

        /* Audio & Video */
    } else if ( strcmp( dot, ".wav" ) == 0 ) {
        buf = "audio/wav";
    } else if ( strcmp( dot, ".wma" ) == 0 ) {
        buf = "audio/x-ms-wma";
    } else if ( strcmp( dot, ".wmv" ) == 0 ) {
        buf = "audio/x-ms-wmv";
    } else if ( strcmp( dot, ".au" ) == 0 || strcmp( dot, ".snd" ) == 0 ) {
        buf = "audio/basic";
    } else if ( strcmp( dot, ".midi" ) == 0 || strcmp( dot, ".mid" ) == 0 ) {
        buf = "audio/midi";
    } else if ( strcmp( dot, ".mp3" ) == 0 || strcmp( dot, ".mp2" ) == 0 ) {
        buf = "audio/x-mpeg";
    } else if ( strcmp( dot, ".rm" ) == 0  || strcmp( dot, ".rmvb" ) == 0 ||\
            strcmp( dot, ".rmm" ) == 0 ) {
        buf = "audio/x-pn-realaudio";
    } else if ( strcmp( dot, ".avi" ) == 0 ) {
        buf = "video/x-msvideo";
    } else if ( strcmp( dot, ".3gp" ) == 0 ) {
        buf = "video/3gpp";
    } else if ( strcmp( dot, ".mov" ) == 0 ) {
        buf = "video/quicktime";
    } else if ( strcmp( dot, ".wmx" ) == 0 ) {
        buf = "video/x-ms-wmx";
    } else if ( strcmp( dot, ".asf" ) == 0  || strcmp( dot, ".asx" ) == 0 ) {
        buf = "video/x-ms-asf";
    } else if ( strcmp( dot, ".mp4" ) == 0 || strcmp( dot, ".mpg4" ) == 0 ) {
        buf = "video/mp4";
    } else if ( strcmp( dot, ".mpe" ) == 0  || strcmp( dot, ".mpeg" ) == 0 ||\
            strcmp( dot, ".mpg" ) == 0 || strcmp( dot, ".mpga" ) == 0 ) {
        buf = "video/mpeg";

        /* Documents */
    } else if ( strcmp( dot, ".pdf" ) == 0 ) {
        buf = "application/pdf";
    } else if ( strcmp( dot, ".rtf" ) == 0 ) {
        buf = "application/rtf";
    } else if ( strcmp( dot, ".doc" ) == 0  || strcmp( dot, ".dot" ) == 0 ) {
        buf = "application/msword";
    } else if ( strcmp( dot, ".xls" ) == 0  || strcmp( dot, ".xla" ) == 0 ) {
        buf = "application/msexcel";
    } else if ( strcmp( dot, ".hlp" ) == 0  || strcmp( dot, ".chm" ) == 0 ) {
        buf = "application/mshelp";
    } else if ( strcmp( dot, ".swf" ) == 0  || strcmp( dot, ".swfl" ) == 0 ||\
            strcmp( dot, ".cab" ) == 0 ) {
        buf = "application/x-shockwave-flash";
    } else if ( strcmp( dot, ".ppt" ) == 0  || strcmp( dot, ".ppz" ) == 0 ||\
            strcmp( dot, ".pps" ) == 0 || strcmp( dot, ".pot" ) == 0 ) {
        buf = "application/mspowerpoint";

        /* Binary & Packages */
    } else if ( strcmp( dot, ".zip" ) == 0 ) {
        buf = "application/zip";
    } else if ( strcmp( dot, ".rar" ) == 0 ) {
        buf = "application/x-rar-compressed";
    } else if ( strcmp( dot, ".gz" ) == 0 ) {
        buf = "application/x-gzip";
    } else if ( strcmp( dot, ".jar" ) == 0 ) {
        buf = "application/java-archive";
    } else if ( strcmp( dot, ".tgz" ) == 0  || strcmp( dot, ".tar" ) == 0 ) {
        buf = "application/x-tar";
    } else {
        buf = "application/octet-stream";
    }
    strcpy(ret, buf);
}

void send_response(int clientdesc, char *request_path, char *http_version, char *request_content)
{
    char serv_date[128] ={0};
    char mime_type[50] = {0};
    char file_contents[102400];
    char *response_str= NULL;

    memset(file_contents, 0, 102400);
    get_html_body(request_path, file_contents, mime_type);
    get_serv_date(serv_date);
    serv_date[strlen(serv_date) -1] = '\0';
    response_str = (char *) malloc(sizeof(char) * (strlen(file_contents) + 300));
    sprintf(response_str, "%s 200 OK\r\nDate: %s\r\nServer: my lhttp server\r\n\
            Content-Type: %s\r\nContent-Length: %d\r\n\r\n%s", http_version,\
            serv_date, mime_type, (int)strlen(file_contents),file_contents);
    send(clientdesc, response_str,  strlen(response_str) + 1, 0);
    free(response_str);
}
