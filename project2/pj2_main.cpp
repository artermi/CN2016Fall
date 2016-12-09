#include "small_functions.h"
#include <unistd.h>
#include <sys/socket.h>
#include <vector>
using namespace std;

int socket_fd;

void create_connection();
void send_enter();// press enter
void send_arbit();//send any key
void login_ptt(string id,string,pass);
void process_middle();
void post_article(class article the_art);
void exit_ptt();

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
	close(socket_fd);
	return 0;
}
void create_connection(){
	if ((socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("socket creake fail.");
		exit(1);
	}
	struct sockaddr_in srv;
	srv.sin_family = AF_INET; // use the internet addr family
	srv.sin_port = htons(23); // dedicated telnet port = 23
	srv.sin_addr.s_addr = inet_addr("140.112.172.11"); // ptt.cc IP address
	
	/* connect to the server */
	cout <<"Connecting to 140.112.172.11 [ptt.cc]...\n" <<endl;
	
	if (connect(socket_fd, (struct sockaddr*) &srv, sizeof(srv)) < 0) {
		perror("connect");
		exit(1);
	} else {
		printf("Connection succesfull.\n\n");
	}
}

void send_enter(){
	if(write(socket_fd,"\r",sizeof(char)) < 0){
		perror("send enter fail.");
		exit(1);
	}
	sleep(1);
}
void send_arbit(){
	if(write(socket_fd," ",sizeof(char)) < 0){
		perror("send arbit fail.");
		exit(1);
	}
	sleep(1);
}


void login_ptt(string id,string pass){
	if(write(socket_fd,id.c_str(), sizeof(char)*(id.length() + 1)) < 0){
		perror("cannot login");
		exit(1);
	}
	send_enter();
	if(write(socket_fd,pass.c_str(), sizeof(char)*(pass.length() + 1)) < 0){
		perror("cannot login");
		exit(1);
	}
	send_enter();
	send_arbit();
	send_arbit();
}

void process_middle(){
	send_arbit();
	send_arbit();
}

void post_article(class article the_art){
	if(write(socket_fd, "s",sizeof(char)) < 0){
		perror("search fail");
		exit(1);
	}
	sleep(1);
	if(write(socket_fd, the_art.board.c_str(),(the_art.board.length() + 1) *sizeof(char)) < 0){
		perror("enter board fail");
		exit(1);
	}
	send_enter();
	send_arbit();
	//char crtl_p = 16;
	
	if(write(socket_fd,16,sizeof(char)) < 0){
		perror("send crtl+p error.");
		exit(1);
	}
	send_enter();// don't choose type
	
	if(write(socket_fd,the_art.title.c_str(),(the_art.title.length() + 1)*sizeof(char)) < 0){
		perror("write title error.");
		exit(1);
	}
	send_enter();
	
	if(write(socket_fd,the_art.content.c_str(),(the_art.content.length()+1)*sizeof(char)) < 0){
		perror("write content error.");
		exit(1);
	}
	if (write(socket_fd, 24, sizeof(char)) < 0) {
		perror("crt+x error.");
		exit(1);
	}
	sleep(1);
	
	if (write(socket_fd, "s", sizeof(char)) < 0) {
		perror("save error.");
		exit(1);
	}
	send_enter();
	send_arbit();
	send_arbit();
}

void exit_ptt(){
	char left[3] = {0x1b,0x5b,0x44};
	for(int i = 0; i < 15; i++){
		if (write(socket_fd, &left, 4 * sizeof(char)) < 0) {
			perror("send left");
			exit(1);
		}
	}
	char right[3] = {0x1b,0x5b,0x43};
	if (write(socket_fd, &right, 4 * sizeof(char)) < 0) {
			perror("send right");
			exit(1);
	}
	if (write(socket_fd, "y", sizeof(char)) < 0) {
			perror("send y");
			exit(1);
	}
	send_enter();
}