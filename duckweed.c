#include "duckweed.h"

int main(int argc, const char *argv[])
{
    if(-1 == (mkdir(WEB_SITE, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))) {
        if(ENOSPC == errno) {
            perror ( "disk do not have enough space!\n" );
            exit(1);
        }
    }

    chdir(WEB_SITE);
    create_socket();
    return 0;
}
