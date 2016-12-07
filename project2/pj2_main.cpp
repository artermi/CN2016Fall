#include "small_functions.h"
#include <vector>
using namespace std;

int main(int argc, char **argv){
	string ID,PASS;
	vector<article> POST;
	bool exit;

	string file_name = "P_input.txt";
	if(argc > 1)
		file_name = string(argv[1]);
	read_input_file(file_name,ID,PASS,POST,exit);
	
	//create socket
	//login
	//while still article
	//goto board
	//post article
	//end
	//if need exit 
	//exit

}
