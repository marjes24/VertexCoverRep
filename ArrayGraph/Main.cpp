#include "Tree.h"
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <limits>

using namespace std;
bool isCover(vector<pair<int,int> > &edges, int &edge_count);

int getLargestVertex(int* &graph);//seperate function to return neighbors?



int main(int argc, char* argv[]){

	int *graphArray;
	int edge_count = 0;
	int total_vertices = 0;

	string first_arg = argv[1];

	if(first_arg == "-a"){
		//read from file		
		string line;
		
		ifstream ifs;
		
		ifs.open(argv[2]);
		stringstream ss;

		//read first line to get number of edges
		getline(ifs, line);
		ss<<line;
		ss>>total_vertices;
		ss.clear();

		graphArray = new int[total_vertices*total_vertices];
		int i = 0;
		int j = 0;

		while(ifs){
			ifs>>ws;
			getline(ifs,line);
			if(ifs.eof()) break;
			ss<<line;

			int x;
			while(ss>>x){
				if(x == 1){
					//graphArray [i][j] = 1;
					graphArray[i*total_vertices+j] = 1;
					
					++j;
					++edge_count;
				}
				else if(x == 0){
					//graphArray[i][j] = 0;
					graphArray[i*total_vertices+j] = 0;
					++j;
				}
			}			
			++i;
			j = 0;
			
			ss.clear();

		}

		ifs.close();

		edge_count = edge_count/2;//edges are count twice in adjacency matrix
	}
/*	else if(first_arg == "-l"){
		string line;
		int vertices_count;//needed?

		ifstream ifs;
		ifs.open(argv[2]);
		stringstream ss;

		//read first line
		getline(ifs,line);
		ss<<line;
		ss>>vertices_count>>edge_count;
		ss.clear();
		
		int current_vertex = 0;
		for(int i = 0; i<vertices_count; ++i){
			list<int> vertex_list;
			vertex_list.push_back(current_vertex);

			
			while(ifs){
				int a;
				int b;
				getline(ifs,line);

				if(ifs.eof()) break;
				
				ss<<line;
				ss>>a>>b;
				ss.str(string());
				ss.clear();

				if(a == current_vertex)
					vertex_list.push_back(b);
				else if(b == current_vertex)
					vertex_list.push_back(a);

			}

			ifs.clear();
			ifs.seekg(0, ios::beg);//go to beginning of file
			getline(ifs,line);//skip first line

			graph.push_back(vertex_list);
			++current_vertex;
		}
		
	}	
*/


	//print out graph
	for(int i =0; i<total_vertices; ++i){
		for(int j = 0; j<total_vertices; ++j){
			cout<<graphArray[i*total_vertices+j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
  



void DFSCover(int* array_graph, int &edge_count){
	int max = std::numeric_limits<int>::max();
	vector<int> curr_min_cover(max);//initiliaze for initial comparison

	stack<TreeNode*> node_stack;
	TreeNode* root = new TreeNode;

	root->graph = array_graph;//learn how to copy arrays

	node_stack.push(root);

	while(!node_stack.empty()){
		TreeNode *tmp = node_stack.top();
		node_stack.pop();

		//check if node has cover
		if(isCover(tmp->covered_edges,edge_count) && tmp->cover_vertex.size() <= curr_min_cover.size())//may cause errors? return to check
			curr_min_cover = tmp->cover_vertex;

		if(tmp->graph_size != 0 && !(tmp->cover_vertex.size()>curr_min_cover.size())){

			//int* tmp_graph = tmp->graph;
		}
	
	}

}  



bool isCover(vector<pair<int,int> > &edges, int &edge_count){
	return edges.size() == edge_count;
}    
