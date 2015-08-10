//Degree One optimization while searching for highest degree


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

vector<int> DFSCover(list<list<int> > graph, int edge_count);
bool inVector(vector<int> &v,  int &n);
bool inVector(vector<pair<int,int> > &v, pair<int,int> &p);
bool checkVertices(list<list<int> >&graph, vector<int> &cover_Vertex, int edge_count);

int main(int argc, char* argv[]){

	list<list<int> > graph;
	int edge_count = 0;
	string first_arg = argv[1];

	if(first_arg == "-a"){
		//read from file
		string file_name;
		file_name = argv[2];//not nedded
		
		string line;
		
		ifstream ifs;
		
		ifs.open(argv[2]);
		stringstream ss;

		//read first line to get number of edges
		getline(ifs, line);
		ss<<line;
		ss>>edge_count;
		ss.clear();

		int vertical_number = 1;
		int horizontal_number = 1;
		edge_count = 0;//discard the number that was read at top of file
		while(ifs){
			ifs>>ws;
			getline(ifs,line);
			if(ifs.eof()) break;
			ss<<line;

			list<int> vertex;
			vertex.push_back(vertical_number);

			int x;
			while(ss>>x){
				//ss>>ws;
				//ss>>x;
				if(x == 1){
					vertex.push_back(horizontal_number);
					++edge_count;
				}
				++horizontal_number;

			}

			graph.push_back(vertex);
			
			
			++vertical_number;
			horizontal_number = 1;
			
			ss.clear();

		}

		ifs.close();

		edge_count = edge_count/2;//edges are count twice in adjacency matrix
	}
	else if(first_arg == "-e"){
		string file_name;
		file_name = argv[2];//not needed
		
		string line;
		
		ifstream ifs;
		
		ifs.open(argv[2]);
		stringstream ss;

		//read first line to get number of edges
		getline(ifs, line);
		ss<<line;
		ss>>edge_count;
		ss.clear();
		//read in graph
		while(!ifs.eof()){
			getline(ifs,line);

			ss<<line;

			list<int> vertex;
			int x;
			
			while(ss>>x){		
				vertex.push_back(x);		
			}
			ss.clear();
			graph.push_back(vertex);
		}
	}
	else if(first_arg == "-l"){
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

	/*cout<<"total edges "<<edge_count<<endl;

	for(list<list<int> >::iterator it = graph.begin(); it!=graph.end(); it++){cout<<endl;
		for(list<int>::iterator it1 = (*it).begin(); it1 != (*it).end(); it1++){
			cout<<(*it1)<< " ";
		}
		
	}*/
	cout<<"Done reading in graph";
	cout<<endl;
	vector<int> answer = DFSCover(graph, edge_count);

	cout<<"vector cover answer"<<endl;
	for(int i = 0; i<answer.size(); ++i){
		cout<< answer[i]<< " ";
	}

	cout<<"cover size: "<<answer.size();
	cout<<endl;

	return 0;
}


vector<int> DFSCover(list<list<int> > graph,int edge_count){
	int max = std::numeric_limits<int>::max();
	vector<int> curr_min_cover(max);//initiliaze for initial comparison //maybe fill it to max_int value?
	
	stack<TreeNode*> node_stack;
	
	TreeNode* root = new TreeNode;
	root->graph = graph;

	node_stack.push(root);

	while(!node_stack.empty()){
		
		TreeNode* tmp =  node_stack.top();
		node_stack.pop();

		//check if node has cover, compare to new cover to find min cover
		if(tmp->current_covered_edges.size() == edge_count)
			curr_min_cover = tmp->cover_Vertex; 



		if(tmp->graph.size()!=0 && !(tmp->cover_Vertex.size()>curr_min_cover.size()) ){ //backtrack if no more nodes or if the node cover gest to big

			//make two new tree nodes left and right, push right and then left
			//first search tmp node's graph for highest degree
			list<list<int> > tmp_graph = tmp->graph;

			list<list<int> >::iterator current_largest = tmp_graph.begin();
			list<list<int> >::iterator it = tmp_graph.begin();

				
			int count = 0; //number of edges
			int largest_count=0; // larget number of edges

			for(it; it!=tmp_graph.end(); it++){

				count = 0;
				list<int>::iterator element_iterator = (*it).begin();

				for(element_iterator; element_iterator!=(*it).end(); element_iterator++){
					++count;
				}

				if(count>= largest_count){
					largest_count = count;
					current_largest = it;

				}

			}

		
			TreeNode* right = new TreeNode;
			TreeNode* left = new TreeNode;

			right->cover_Vertex = tmp->cover_Vertex;
			left->cover_Vertex = tmp->cover_Vertex;

			list<int>::iterator vertex_it = (*current_largest).begin();

			//vertex is in
			if(!inVector(left->cover_Vertex, (*vertex_it)))
				left->cover_Vertex.push_back((*vertex_it));

			//neighbors are in	
			vertex_it++;
			for(vertex_it; vertex_it!=(*current_largest).end(); vertex_it++){
				if(!inVector(right->cover_Vertex, (*vertex_it)))
					right->cover_Vertex.push_back((*vertex_it));
			}

			//insert cover edges to current covered edges
			list<int>::iterator horizontal_iterator = (*current_largest).begin();
			int first = (*horizontal_iterator);
			++horizontal_iterator;
			for(horizontal_iterator; horizontal_iterator != (*current_largest).end(); ++horizontal_iterator){

				int second = (*horizontal_iterator);
				int a,b;
				if(second < first){
					a = second;
					b = first;
				}
				else{
					a = first;
					b = second;
				}

				pair<int,int> pair1(a,b);
				if(!inVector(right->current_covered_edges,pair1))
					right->current_covered_edges.push_back(pair1);
				if(!inVector(left->current_covered_edges,pair1))
					left->current_covered_edges.push_back(pair1);
			}
			
			//Make left child graph, delete V
			int deleted_vertex = (*(*current_largest).begin());
			tmp_graph.erase(current_largest);


			
			//delete V from adjacency list for left child graph
			list<list<int> >::iterator it1=tmp_graph.begin(); 
			list<int>::iterator it2;

			for(it1; it1 != tmp_graph.end(); it1++){
				for(it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
					if((*it2) == deleted_vertex){
						list<int>::iterator it3 = it2;
						(*it1).erase(it3); 
						it2--;
					}
				}
			}
			right->graph = tmp_graph;
			left->graph = tmp_graph;

			tmp->right_child = right;
			tmp->left_child = left;

			node_stack.push(right);
			node_stack.push(left);

		
			
		}

		delete tmp;//free memory 
	}
	return curr_min_cover;
}

bool inVector(vector<int> &v,  int &n){
	for(int i=0; i<v.size(); ++i){
		if(v[i]==n)
			return true;
	}
	return false;
}

bool inVector(vector<pair<int,int> > &v, pair<int,int> &p){//overloaded
	for(int i=0; i<v.size(); ++i){
		if(v[i]==p)
			return true;
	}
	return false;
}

