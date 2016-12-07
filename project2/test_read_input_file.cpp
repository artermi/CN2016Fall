#include "read_input_file.h"

int main(int argc,char** argv){
	string ID,PASS;
	vector<article> POST;
	bool exit;

	string file_name = "P_input.txt";
	if(argc > 1)
		file_name = string(argv[1]);
	read_input_file(file_name,ID,PASS,POST,exit);
	return 0;
}
