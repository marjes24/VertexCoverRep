//Original Program

#include "TreeSearch.h"
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	list<list<int> > graph;
	int edge_count = 0;
	int leaf_count = 0;
	
	read_graph(graph, edge_count, argv);
	
	vector<int> answer = DFSCover(graph, edge_count, leaf_count);

	if(isCover(graph, answer, edge_count)){
		cout<<"vector cover answer"<<endl;
		for(int i = 0; i<answer.size(); ++i){
			cout<< answer[i]<< " ";
		}

		cout<<"cover size: "<<answer.size()<<endl;
		cout<<"leaf count: "<<leaf_count<<endl;
	} else {
		cout<<"Cover not found"<<endl;
	}
	
	return 0;
}


