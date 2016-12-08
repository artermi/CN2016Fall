#include "small_functions.h"
#include <sys/socket.h>
#include <vector>
using namespace std;

int socket_fd;



int main(int argc, char **argv){
	string ID,PASS;
	vector<article> POST;
	bool exit;

	string file_name = "P_input.txt";
	if(argc > 1)
		file_name = string(argv[1]);
	read_input_file(file_name,ID,PASS,POST,exit);
	
	//create socket
	create_connection();
	//login
	login_ptt(ID,PASS);
	process_middle();
	//goto board
	for(int i = 0; i < POST.length(), i++){
		post_article(POST[i]);
	}
	//if need exit 
	if(exit)
		exit_ptt();
	//exit
	return 0;
}
