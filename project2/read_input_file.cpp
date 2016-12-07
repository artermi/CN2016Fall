#include "read_input_file.h"

void read_input_file(string file_name,string &id,string &pass, vector<class article> &post, bool &exit){
	ifstream file(file_name.c_str(),ifstream::binary);
	
	if(!file){
		return;
	}
	file.seekg(0,file.end);
	int length = file.tellg();
	file.seekg(0,file.beg);

	char *input_tmp = new char [length];
	file.read(input_tmp,length);
	string input(input_tmp);
	delete [] input_tmp;

	cout << input << endl;
//	wstring winput(input.begin(),input.end());

	for(int i=0; i < input.size();i++){
		if(input[i] < 0){
			cout <<input[i] << input[i+1] << input[i+2] <<endl;
			char p[3];
			p[0] = input[i];
			p[1] = input[++i];
			p[2] = input[++i];
			cout << p <<endl;
		}
		else
			cout << input[i] << endl;
	}
}
