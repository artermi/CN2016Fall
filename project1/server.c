#include"common.h"

int main(int argc, char** argv){
	int my_port = atoi(argv[1]);
	int socket_fd;
	if( (socket_fd = socket(AF_INET, SOCK_STREAM,0)) < 0){
		perror("You mother fucker, socket fail!!!");
		exit(1);
	}

	struct sockaddr_in srv;
	srv.sin_family = AF_INET;
	srv.sin_port = htons(my_port);
	srv.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(socket_fd, (struct socketaddr*) &srv, sizeof(srv)) < 0){
		perror("Son of bitch!! bind fails !!");
		exit(1);
	}

	if (listen(socket_fd, 1024) < 0){
		close(socket_fd);
		perror("Up yours!! no listen!!!");
		exit(1);
	}

	struct sockaddr_in cli;//the client or sth else.
	int cli_len = sizeof(cli);
	int new_fd = accept(socket_fd, (struct sockaddr*) &cli,cli_len);
	if(new_fd < 0){
		perror("No accept!! 666 Satan!!!");
		exit(1);
	}

	return 0;
}
