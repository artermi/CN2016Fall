#include "common.h"
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#define FOREVER 0

int num = FOREVER;
int tout = 1000;//int number and timeout

void* working_thread(void * data);
int main(int argc, char* argv[]){
//./client [-n number] [-t time] host_1:IP host_2:IP
//
//=====================readin=======================
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
	printf("number:%d timeout:%d\n",num,tout);
//
//===================thread========================
	signal(SIGPIPE,SIG_IGN);

	pthread_t working[host_num];
	struct working_data data[host_num];
	void *ret;
	for(int i = 0; i < host_num; i++){
		data[i].pak_num  = num;
		data[i].the_host = host[i];
//		printf("thread_creating...\n");
		pthread_create(&(working[i]),NULL,working_thread,(void*)&data[i]);
	}
	for(int i = 0; i < host_num;i++)
		pthread_join(working[i],&ret);
	

	return 0;
}


//===================socket=========================
//
void* working_thread(void * data){
	printf("inside thread!!\n");
	struct working_data* local_data = (struct working_data*) data;
	int  pack_num = local_data -> pak_num;
	char* my_host = local_data -> the_host;
	printf("ping %s\n",my_host);

	int socket_fd;
	if ((socket_fd = socket(AF_INET,SOCK_STREAM, 0))  < 0){
		perror("PUTA!! client socket break");
		exit(1);
	}
//set non blocking
//	fcntl(socket_fd,F_SETFL,O_NONBLOCK);
	
	fd_set fdset;
	struct timeval tv;
	FD_ZERO(&fdset);
	FD_SET(socket_fd,&fdset);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if(tout != 1000){
		tv.tv_sec = tout / 1000;
		tv.tv_usec = (tout % 1000)* 1000;
	}
	int now_pack = 1;
	setsockopt(socket_fd,SOL_SOCKET,SO_RCVTIMEO,(char*)&tv,sizeof(tv));
	setsockopt(socket_fd,SOL_SOCKET,SO_SNDTIMEO,(char*)&tv,sizeof(tv));

	struct sockaddr_in srv;	
	struct Servers_addr* server_addr= turn_to_server_struct(my_host);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(server_addr -> port);
	char* addr_n_port;
	if(is_addr(server_addr -> addr)){
		srv.sin_addr.s_addr = inet_addr(server_addr -> addr);
		addr_n_port = my_host;
	}
	else{
		struct hostent *he = gethostbyname(server_addr -> addr);
		struct in_addr **addr_list;
		addr_list = (struct in_addr **)he -> h_addr_list;
		addr_n_port = (char*) malloc(30);
		sprintf(addr_n_port,"%s",inet_ntoa(*addr_list[0]));
//		printf("IP Address:%s\n",addr_n_port);
		srv.sin_addr.s_addr = inet_addr(addr_n_port);
		sprintf(addr_n_port,"%s:%d",addr_n_port,server_addr -> port);
	}

	while(pack_num -- ||num == FOREVER){
		int conn_status = connect(socket_fd,(struct sockaddr*) &srv,sizeof(srv));
		if(conn_status < 0 && errno!= EISCONN){
			printf("connect timeout when connect to %s,seq = %d\n",addr_n_port,now_pack);
			now_pack ++;
			nanosleep(&tv,NULL);
			continue;
		}
		char buf[512];
		char buf_read[512];
		int nbytes;
		sprintf(buf,"%d",now_pack);
		struct timeval start,end;
		double elapsed;
		int readable = 1;
		gettimeofday(&start,NULL);
		if( write(socket_fd,buf,sizeof(buf)) < 0){
			printf("timeout when send to %s,seq=%s\n",addr_n_port,buf);
			nanosleep(&tv,NULL);
			now_pack ++;
			
			continue;
		}
		if( read(socket_fd,buf_read,sizeof(buf_read)) < 0){
			printf("timeout when recv from %s,seq=%s\n",addr_n_port,buf);
			now_pack ++;
			readable = 0;
			//		break;
			continue;
		}
		
		gettimeofday(&end,NULL);

		elapsed = (double)(end.tv_sec - start.tv_sec)*1000 + (double)(end.tv_usec - start.tv_usec)/1000000.0;

		printf("recv form server:%s,seq=%s,RTT=%d msec\n",addr_n_port,buf_read,(int)elapsed);

		bzero(buf,sizeof(buf));
		bzero(buf_read,sizeof(buf_read));
		now_pack ++;
	}
//	scanf("%d");
//		close(socket_fd);

	return NULL;
}
