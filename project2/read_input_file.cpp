#include "read_input_file.h"

void read_input_file(vector<user> &user_list,string file_name){
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

//	cout << input << endl;
//	wstring winput(input.begin(),input.end());
	for(int i = 0; i < input.size(); i ++){
		user auser;
		auser.exit = false;
		for(;i < input.size();i++){
			if(input.compare(i,4,"<ID>") == 0){
				i += 4;
				while(input.compare(i,5,"</ID>")){
					auser.ID += input[i];
					i++;
				}
			}
			if(input.compare(i,6,"<PASS>") == 0){
				i += 6;
				while(input.compare(i,7,"</PASS>")){
					auser.PASS += input[i];
					i++;
				}
			}
			if(input.compare(i,7,"<BOARD>") == 0){
				i += 7;
				class  article new_article;
				while(input.compare(i,8,"</BOARD>")){
					new_article.board += input[i];
					i++;
				}
				while(input.compare(i,3,"<P>"))
					i++;
				i+=3;
				while(input.compare(i,4,"</P>")){
					new_article.title += input[i];
					i++;
				}
				while(input.compare(i,9,"<CONTENT>"))
					i++;
				i+=9;
				while(input.compare(i,10,"</CONTENT>")){
					new_article.content += input[i];
					i++;
				}
				auser.ART_list.push_back(new_article);

			}
			if(input.compare(i,6,"<EXIT>") == 0){
				i += 6;
				auser.exit = true;
				break;
			}
		}
		if(auser.ID.size() > 0)
			user_list.push_back(auser);

	}
	cout << "plantext" <<endl;
	for(int i = 0; i < user_list.size(); i++){
		cout <<"ID: "<< user_list[i].ID <<" no password"<<endl;
		//	cout << pass <<endl;
		for(int k = 0; k < user_list[i].ART_list.size(); k++){
			cout << "*******" << endl;
			cout << "board: " << user_list[i].ART_list[k].board << endl;
			cout << "title: " << user_list[i].ART_list[k].title << endl;
			cout << "content:" <<endl;
			cout << user_list[i].ART_list[k].content << endl;
			cout << "*******" <<endl;
		}
		cout << user_list[i].exit <<endl;
		cout << "==============="<<endl;
	}

/*
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
	*/
}
