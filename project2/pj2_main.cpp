#include "small_functions.h"
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <iconv.h>
using namespace std;

int socket_fd;
bool chinese_mode = true;
bool P_dollar_mode = false;

void create_connection();
void send_enter();// press enter
void send_arbit();//send any key
void login_ptt(string id,string pass);
void process_middle();
void post_article(class article the_art);
void exit_ptt();
void write_chinese(string content,bool is_content);

int main(int argc, char **argv){
	string ID,PASS;
	vector<article> POST;
	bool exit;

	string file_name = "P_input.txt";
	if(argc > 1){
		for(int i = 1; i < argc; i ++){
			if(string(argv[i]) == "DOLLAR")
				P_dollar_mode = true;
			else
				file_name = string(argv[1]);
		}
	}
	cout << file_name <<endl;
	read_input_file(file_name,ID,PASS,POST,exit);

	
	//create socket
	create_connection();
	
	//login
	login_ptt(ID,PASS);
	
	process_middle();
	//goto board
	for(int i = 0; i < POST.size(); i++){
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
		cout << "Connection succesfull." << endl;
	}
}

void send_enter(){
	cout << "sending enter" <<endl;
	if(write(socket_fd,"\r",sizeof(char)) < 0){
		perror("send enter fail.");
		exit(1);
	}
	sleep(1);
}
void send_arbit(){
	cout << "sending space" <<endl;
	if(write(socket_fd," ",sizeof(char)) < 0){
		perror("send arbit fail.");
		exit(1);
	}
	sleep(1);
}


void login_ptt(string id,string pass){
	cout << "sending ID" <<endl;
	if(write(socket_fd,id.c_str(), sizeof(char)*(id.length() + 1)) < 0){
		perror("cannot login");
		exit(1);
	}
	send_enter();
	cout << "senging pass" <<endl;
	if(write(socket_fd,pass.c_str(), sizeof(char)*(pass.length() + 1)) < 0){
		perror("cannot login");
		exit(1);
	}
	send_enter();
	send_enter();
	send_arbit();
	send_arbit();
}

void process_middle(){
	send_arbit();
	send_arbit();
}

void post_article(class article the_art){
	cout << "press s" <<endl;
	if(write(socket_fd, "s",sizeof(char)) < 0){
		perror("search fail");
		exit(1);
	}
	sleep(1);
	cout << "write board name" <<endl;
	if(write(socket_fd, the_art.board.c_str(),(the_art.board.length() + 1) *sizeof(char)) < 0){
		perror("enter board fail");
		exit(1);
	}
	send_enter();
	send_arbit();

	char crtl_p = 16;
	cout << "crtl + p" << endl;
	if(write(socket_fd,&crtl_p,sizeof(char)) < 0){
		perror("send crtl+p error.");
		exit(1);
	}
	send_enter();// don't choose type
	
	cout << "write title" <<endl;
	if(chinese_mode)
		write_chinese(the_art.title,false);
	else{
		if(write(socket_fd,the_art.title.c_str(),(the_art.title.length() + 1)*sizeof(char)) < 0){
			perror("write title error.");
			exit(1);
		}
	}
	send_enter();

	cout << "write content" <<endl;
	if(chinese_mode){
		write_chinese(the_art.content,true);
	}
	else{
		if(write(socket_fd,the_art.content.c_str(),(the_art.content.length()+1)*sizeof(char)) < 0){
			perror("write content error.");
			exit(1);
		}
	}

	cout << "crtl + x" <<endl;
	char crtl_x = 24;
	if (write(socket_fd, &crtl_x, sizeof(char)) < 0) {
		perror("crtl+x error.");
		exit(1);
	}
	sleep(1);
	
	cout << "save" <<endl;
	if (write(socket_fd, "s", sizeof(char)) < 0) {
		perror("save error.");
		exit(1);
	}
	send_enter();
	send_arbit();
	send_arbit();
}

void exit_ptt(){
	cout <<"leaving" <<endl;
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

void write_chinese(string content,bool is_content){
	int total_dollar = 4000;
	for(int i = 0; i < content.length(); i++){
		cout << "writing: ";
		if(content[i] >= 0){//anscii
			char tmp[1];
			memset(tmp,0,1);
			tmp[0] = content[i];
//			cout << string(tmp) <<endl;
			if(tmp[0] == '\n' && is_content)
				tmp[0] = '\r';

			if (write(socket_fd,tmp, sizeof(char)) < 0) {
				perror("write ascii error.");
				exit(1);
			}
			cout << content[i]<< endl;

		}
		else{
			char p_tmp[3];
			memset(p_tmp,0,3);
			p_tmp[0] = content[i];
			p_tmp[1] = content[++i];
			p_tmp[2] = content[++i];	

			cout <<p_tmp<<endl;

			size_t utf8_len = strlen(p_tmp);
			size_t big5_len = utf8_len/3*2+1;
			char tosend[3];

			memset(tosend,0,2);
			iconv_t cd = iconv_open("big5","UTF-8");

			char *toin = p_tmp;
			char *toout = tosend;
			size_t error = iconv(cd,&toin,&utf8_len,&toout,&big5_len);
			iconv_close(cd);

			if (write(socket_fd,tosend, 2*sizeof(char)) < 0) {
				perror("write big5 error.");
				exit(1);
			}
		
		}
		if(P_dollar_mode && is_content && total_dollar--)
			usleep(500000);
	}

}
