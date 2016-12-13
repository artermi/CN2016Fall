#include "read_input_file.h"

int main(int argc,char** argv){
	vector<class user> users;

	string file_name = "P_input.txt";
	read_input_file(users,file_name);
	return 0;
}
