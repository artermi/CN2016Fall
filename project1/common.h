#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <utime.h>
#include <pthread.h>
#include <ctype.h>

struct Servers_addr{
	char *addr;
	int port;
};

struct Servers_addr* turn_to_server_struct(char* intup);
int is_addr(char *input);
