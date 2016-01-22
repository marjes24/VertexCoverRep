#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
int main(int argc, char* argv[]){

	system("grep \"real\" ./*");
	return 0;
}

double average(string filename){
	/*ifstream ifs;
	ifs.open(argv[1]);
	stringstream ss;
	string line;
	string first_word;
	string second_word;
	while(ifs){
		ifs>>ws;
		getline(ifs,line);
		ss<<line;
		while(ss){
			ss>>first_word;
			if(first_word == "real" || first_word == "cover" || first_word == "leaf")
				cout<<line<<endl;
		}
		ss.clear();
		//cout<<line<<endl;;
	}

	ifs.close();*/
	return 0;
}