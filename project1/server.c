#include"common.h"

void *thread_for_client(void *data);

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

	if(show_my_IP_address(socket_fd,my_port) == 0){
		perror("Yo mama so fat!! don't know the IP address!!");
		exit(1);
	}

	struct sockaddr_in cli;//the client or sth else.
	int cli_len = sizeof(cli);
	int new_fd;
	while( new_fd = accept(socket_fd, (struct sockaddr*) &cli,&cli_len)){
		pthread_t sniffer_thread;
		int *new_sock = malloc(1);
		*new_sock = new_fd;
		if(pthread_create(&sniffer_thread,NULL,thread_for_client,(void*) new_sock) < 0){
			perror("could not create thread");
			return 1;
		}
	}
	if(new_fd < 0){
		perror("No accept!! 666 Satan!!!");
		exit(1);
	}
	///to read_in the data

	close(socket_fd);
	return 0;
}

void *thread_for_client(void *data){
	printf("into thread\n");
	int new_fd = *(int*)data;
	int nbytes;
	char buf[512];
	if(nbytes = read(new_fd,buf,sizeof(buf)) <0){
		perror("read in fail!!");
		exit(1);
	}
	else{
		printf("%s\n",buf);
		write(new_fd,buf,sizeof(buf));
	}	
	close(new_fd);
	return NULL;
}
