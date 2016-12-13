#include <string>
#include <vector>
using namespace std;

class article{
public:
	string board;
	string title;
	string content;
};

class user{
public:
	string ID;
	string PASS;
	vector<article> ART_list;
	bool exit;
};
