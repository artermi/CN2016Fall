#include "read_input_file.h"

void read_input_file(string file_name,string &id,string &pass, vector<article> &post, bool *exit){
	ifstream file(file_name.c_str(),ifstream::binary);
	
	if(!file){
		return;
	}
	file.seekg(0,file.end);
	int length = file.tellg();
	file.seekg(0,file.beg);

	char *input_tmp = new char [length];
	file.read(input,length);

}
