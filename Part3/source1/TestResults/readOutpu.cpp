#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;
double average(string filename);
double convert_time_to_double(string time_string);
int main(int argc, char* argv[]){

	system("grep \"real\" ./inf45.* >> infoutput45.txt");
	system("grep \"real\" ./inf40.* >> infoutput40.txt");
	system("grep \"real\" ./inf35.* >> infoutput35.txt");
	system("grep \"real\" ./inf30.* >> infoutput30.txt");

	system("grep \"real\" ./folic45.* >> folicoutput45.txt");
	system("grep \"real\" ./folic40.* >> folicoutput40.txt");
	system("grep \"real\" ./folic35.* >> folicoutput35.txt");
	system("grep \"real\" ./folic30.* >> folicoutput30.txt");


	system("grep \"real\" ./estra45.* >> estraoutput45.txt");
	system("grep \"real\" ./estra40.* >> estraoutput40.txt");
	system("grep \"real\" ./estra35.* >> estraoutput35.txt");
	system("grep \"real\" ./estra30.* >> estraoutput30.txt");

	string filename = "infoutput45.txt";
	average(filename);


	return 0;
}

double average(string filename){
	ifstream ifs;
	ifs.open(filename);
	stringstream ss;
	string line;
	string first_word;
	string second_word;
	while(ifs){
		ifs>>ws;
		getline(ifs,line);
		ss<<line;
		ss>>first_word;
		ss>>second_word;
		cout<<second_word<<endl;
		convert_time_to_double(second_word);
		ss.clear();
		//cout<<line<<endl;;
	}

	ifs.close();
	return 0;
}

double convert_time_to_double(string time_string){ //format 234m1.35s
	int position_m = time_string.find("m");
	cout<<position_m<<endl;
	return 0;
}