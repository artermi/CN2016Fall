#include "common.h"

int main(int argc, char* argv[]){
//./client [-n number] [-t time] host_1:IP host_2:IP 
	int num = 0,tout = 1000;//int number and timeout
	int host_num = 0;
	char* host[argc];
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i],"-n") == 0)
			num = atoi(argv[i+1]);

		else if(strcmp(argv[i],"-t") == 0)
			tout = atoi(argv[i+1]);

		else if(strncmp(argv[i],"host",4) == 0){
			int stlength = strlen(argv[i]);
			for(int k = 1; k < stlength; k++){
				if(*argv[i] != ':'){
//					printf("%d %d %c\n",argv[i],&(argv[i][0]),argv[i][0]);
					argv[i] ++;
				}
				else{
					argv[i] ++;
					break;
				}
			}
			host[host_num] = argv[i];
			host_num ++;
		}
	}


	
	return 0;
}
