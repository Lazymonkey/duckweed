
#                 {/ ． ．\}
#                 ( (oo)   )
#+--------------oOOo---︶︶︶︶---oOOo------------------+
#     FileName  :           Makefile
#     Describe  :           this is a simple programm for
#     						duckweed as a http server
#     Author    :           Lazy.monkey™
#     Email     :           lazymonkey.me@gmail.com
#     HomePage  :           NULL
#     Version   :           0.0.1
#     LastChange:           2011-12-24 21:10:42
#     History   :			2011,05,08
#+------------------------------------Oooo--------------+

CC = gcc
ARGS = -Wall -c -g
OBJ = create_socket.o handle_client.o send_response.o duckweed.o

duckweed: $(OBJ)
	$(CC) -g $(OBJ) -o duckweed

create_socket.o:  create_socket.c
	$(CC) $(ARGS)  create_socket.c

handle_client.o:  handle_client.c
	$(CC) $(ARGS)  handle_client.c

send_response.o: send_response.c

	$(CC) $(ARGS) send_response.c
duckweed.o:  duckweed.c
	$(CC) $(ARGS)  duckweed.c

clean:
	rm -f $(OBJ) duckweed core.*
