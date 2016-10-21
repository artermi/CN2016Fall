#include "common.h"

int main(int argc, char* argv[]){
//./client [-n number] [-t time] host_1:IP host_2:IP
//
//=====================readin=======================
	int num = 0,tout = 1000;//int number and timeout
	int host_num = 0;
	char* host[argc];
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i],"-n") == 0)
			num = atoi(argv[++i]);

		else if(strcmp(argv[i],"-t") == 0)
			tout = atoi(argv[++i]);

		else{
			host[host_num] = argv[i];
			host_num ++;
		}
	}
	printf("%d %d\n",num,tout);
//
//===================socket=========================
//Maybe I will change it to thread
	int socket_fd;
	if ((socket_fd = socket(AF_INET,SOCK_STREAM, 0))  < 0){
		perror("PUTA!! client socket break");
		exit(1);
	}
	struct sockaddr_in srv;
	struct Servers_addr* server_addr= turn_to_server_struct(host[0]);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(server_addr -> port);
	if(is_addr(server_addr -> addr)){
		srv.sin_addr.s_addr = inet_addr(server_addr -> addr);
	}
	else{
		struct hostent *he = gethostbyname(server_addr -> addr);
		struct in_addr **addr_list;
		addr_list = (struct in_addr **)he -> h_addr_list;
		char sth_tmp[30];
		sprintf(sth_tmp,"%s",inet_ntoa(*addr_list[0]));
		printf("IP Address:%s\n",sth_tmp);
		srv.sin_addr.s_addr = inet_addr(sth_tmp);
	}
	if(connect(socket_fd,(struct sockaddr*) &srv,sizeof(srv)) < 0){
			perror("Rotten vagina!! connect fail");
			exit(1);
	}
	

	return 0;
}
