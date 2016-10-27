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
	char buf_ret[512];
	int k =3;
//get client info
	char client_info[512];
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);
	if (getsockname(new_fd,(struct sockaddr*)&sin,&len) == -1)
		perror("cannot get sock name");
	sprintf(client_info,"%s:%d",inet_ntoa(sin.sin_addr),ntohs(sin.sin_port));
	printf("%s\n",client_info);
	while(nbytes = read(new_fd,buf,sizeof(buf)) >=0 && k--){
		printf("%s\n",buf);
		sprintf(buf_ret,"send back:%s",buf);
		printf("%s\n",buf_ret);
		write(new_fd,buf_ret,sizeof(buf_ret));
		bzero(buf,sizeof(buf));
		bzero(buf_ret,sizeof(buf_ret));
//		sleep(10);
	}	

	close(new_fd);
	return NULL;
}
