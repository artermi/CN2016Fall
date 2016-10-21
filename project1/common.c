#include "common.h"

struct Servers_addr* turn_to_server_struct(char* input){
	struct Servers_addr *toret = (struct Servers_addr*) malloc(sizeof(struct Servers_addr));
	toret -> addr = strtok(input,":");
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
