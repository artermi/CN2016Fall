#include "common.h"

int main(int argc, char* argv[]){
//./client [-n number] [-t time] host_1:IP host_2:IP 
	int num = 0,tout = 1000;//int number and timeout
	int host_num = 0;
	char* host[argc];
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i],"-n") == 0)
			num = atoi(argv[++i]);

		else if(strcmp(argv[i],"-t") == 0)
			tout = atoi(argv[++i]);

		else if(strncmp(argv[i],"host",4) == 0){
			host[host_num] = argv[i];
			host_num ++;
		}
	}
	printf("%d %d\n",num,tout);


	
	return 0;
}
