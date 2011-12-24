#ifndef  LHTTP__H__
#define  LHTTP__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <time.h>

#define PORT 9000
#define LISTEN_NUM 5
#define BUFF_SIZE 1024
#define WEB_SITE  "./www"

//for http header
#define HEADER_LEN 20

void create_socket();
void handle_client(int clientdesc);
void parse_request(int clientdesc, char *buff);
void parse_request_header(char *buff, char *method, char *path, char *http_version,  char *rc);
int file_exist(const char *filename);
void get_dir_list(const char *path, char *rev);
void get_file_contents(const char *filename, char *rev);
void get_html_body(const char *filename, char *rev, char *mime_type);
void get_mime_type(const char *name, char *ret);
void get_serv_date(char *curtime);
void send_response(int clientdesc, char *request_path, char *http_version, char *request_content);

#endif
