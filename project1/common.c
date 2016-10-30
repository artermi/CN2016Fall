#include "common.h"

struct Servers_addr* turn_to_server_struct(char* input){
	char *hahaha = (char*)malloc(sizeof(char) * 50);
	strcpy(hahaha,input);
	struct Servers_addr *toret = (struct Servers_addr*) malloc(sizeof(struct Servers_addr));
	toret -> addr = strtok(hahaha,":");
	char *tmp = strtok(NULL,":");
	toret -> port = atoi(tmp);

	return toret;
}

int is_addr(char *input){
	int to_ret = 1;
	for(int i = 0; i < strlen(input); i ++){
		if(isalpha(input[i]))
			to_ret=0;
	}
	return to_ret;
}

int show_my_IP_address(int sock_fd,int port){
	struct ifreq ifr;
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name,"net0",IFNAMSIZ-1);

	ioctl(sock_fd,SIOCGIFADDR,&ifr);
	return(printf("%s:%d\n",inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr) -> sin_addr),port));
	//Refered from  geekpage.jp/en/programming/linux-network/get-i[addr.php	
}
