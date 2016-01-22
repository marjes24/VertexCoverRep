#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <vector>

using namespace std;
double average(string filename);
double convert_time_to_double(string time_string);
string seconds_to_string_format(double time);

void output(string filename);
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

	/*double average_time;
	string filename = "infoutput45.txt";
	average_time = average(filename);
	cout<<"average_time: " << average_time << endl;
	string in_string = seconds_to_string_format(average_time);
	cout << in_string << endl;
*/
	cout<<"inf45"<<endl;
	output("infoutput45.txt");
	cout<<endl;
	cout<<"inf40"<<endl;
	output("infoutput40.txt");
	cout<<endl;
	cout<<"inf35"<<endl;
	output("infoutput35.txt");
	cout<<endl;
	cout<<"inf30"<<endl;
	output("infoutput30.txt");
	cout<<endl;

	cout<<"folic45"<<endl;
	output("folicoutput45.txt");
	cout<<endl;
	cout<<"folic40"<<endl;
	output("folicoutput40.txt");
	cout<<endl;
	cout<<"folic35"<<endl;
	output("folicoutput35.txt");
	cout<<endl;
	cout<<"folic30"<<endl;
	output("folicoutput30.txt");
	cout<<endl;

	cout<<"estra45"<<endl;
	output("estraoutput45.txt");
	cout<<endl;
	cout<<"estra40"<<endl;
	output("estraoutput40.txt");
	cout<<endl;
	cout<<"estra35"<<endl;
	output("estraoutput35.txt");
	cout<<endl;
	cout<<"estra30"<<endl;
	output("estraoutput30.txt");
	cout<<endl;

	system("rm ./*output* ");
	return 0;
}

double average(string filename){
	vector<double>time_vector;
	double time_insert; 		//insert double into time vector
	double average_time;

	ifstream ifs;
	ifs.open(filename);
	stringstream ss;
	string line;
	string first_word;
	string second_word;

	while(true){
		ifs>>ws;
		getline(ifs,line);
		if(ifs.eof()) break;
		ss<<line;
		ss>>first_word;
		ss>>second_word;
		//cout<<second_word<<endl;
		ss.clear();
		time_insert = convert_time_to_double(second_word);
		//cout<<"time as double" << time_insert << endl;
		time_vector.push_back(time_insert);
		
		//cout<<line<<endl;;
	}

	double total_time = 0;
	for(int i = 0; i < time_vector.size(); ++i){

		total_time = total_time + time_vector[i];
	}

	average_time = total_time/time_vector.size();
	ifs.close();
	return average_time;
}

double convert_time_to_double(string time_string){ //format 234m1.35s
	int position_m = time_string.find("m");
	int position_s = time_string.find("s");
	string minutes = time_string.substr(0,position_m);
	//cout<<"minutes " << minutes<<endl;
	string seconds = time_string.substr(position_m + 1, position_s - position_m - 1);
	//cout<< "seconds "<<seconds<<endl;
	double minutes_double = stod(minutes);
	double seconds_double = stod(seconds);

	double total_time = minutes_double * 60 + seconds_double;
	return total_time;
}

string seconds_to_string_format(double time){
	int minutes = (int) time;
	minutes = minutes / 60;
	double seconds = time - minutes;
	string minute_string = to_string(minutes);
	string seconds_string = to_string(seconds);

	return minute_string + "m" + seconds_string + "s";
}

void output(string filename){
	double average_time;
	average_time = average(filename);
	cout<< average_time << endl;
	string in_string = seconds_to_string_format(average_time);
	cout << in_string << endl;
}