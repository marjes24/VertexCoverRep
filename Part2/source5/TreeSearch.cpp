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
int node_count = 0;

vector<int> DFSCover(list<list<int> > graph,int edge_count, int &leaf_count){
	vector<int> curr_min_cover(1000);//initiliaze for initial comparison //maybe fill it to max_int value?
	
	stack<TreeNode*> node_stack;
	TreeNode* root = new TreeNode;
	root->graph = graph;
	node_stack.push(root);

	while(!node_stack.empty()){		
		TreeNode* tmp =  node_stack.top();
		node_stack.pop();

		degree_one_optimization(tmp->graph, tmp, curr_min_cover, graph, edge_count);

		list<list<int> >::iterator current_largest = largest_vertex(tmp->graph);

		if(degree(current_largest, tmp->graph) == 0){
			if(tmp->cover_Vertex.size()<=curr_min_cover.size())
				curr_min_cover = tmp->cover_Vertex;
			++leaf_count;
			delete tmp;
			continue;
		} else if(tmp->cover_Vertex.size()<=curr_min_cover.size()){
			TreeNode* right = new TreeNode;
			TreeNode* left = new TreeNode;

			right->cover_Vertex = tmp->cover_Vertex;
			left->cover_Vertex = tmp->cover_Vertex;

			list<int>::iterator vertex_it = (*current_largest).begin();
			
			//v is in
			if(!inVector(left->cover_Vertex, (*vertex_it)))
				left->cover_Vertex.push_back((*vertex_it));
			//neighbors are in	
			vertex_it++;
			for(vertex_it; vertex_it!=(*current_largest).end(); vertex_it++){
				right->cover_Vertex.push_back((*vertex_it));
			}
			
			make_child_graph(tmp->graph, right, left, current_largest);//make graph for both right and left chld
 
			node_stack.push(right);
			node_stack.push(left);

			node_count += 2;

			} else
				++leaf_count;
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

bool isCover(list<list<int> >&graph, vector<int> &cover_Vertex, int edge_count){
	vector<pair<int,int> > covered_Edges;

	for(list<list<int> >::iterator it = graph.begin(); it != graph.end(); it++){

		list<int>::iterator it1 = (*it).begin();
		int first = (*it1);

		if(inVector(cover_Vertex,(*it1))){
			it1++;
			for(it1; it1 != (*it).end(); it1++){

				int second = (*it1);
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
				if(!inVector(covered_Edges,pair1))
					covered_Edges.push_back(pair1);
			}
		}
	}

	return covered_Edges.size() == edge_count;

}

list<list<int> >::iterator largest_vertex(list<list<int> > &graph){

	list<list<int> >::iterator current_largest = graph.begin();
	list<list<int> >::iterator it = graph.begin();	
	int count = 0;
	int largest_count=0;

	for(it; it!=graph.end(); it++){

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
	return current_largest;
}

void make_child_graph(list<list<int> > &tmp_graph, TreeNode *right, TreeNode *left, list<list<int> >::iterator current_largest){
	//right graph and delete v and v's neighbors
	list<list<int> > right_graph = tmp_graph;

	vector<int> right_graph_to_delete;
	for(list<int>::iterator i = (*current_largest).begin(); i != (*current_largest).end(); ++i){
		int v_to_delete = (*i);
		right_graph_to_delete.push_back(v_to_delete);
	}

	for(list<list<int> >::iterator i = right_graph.begin(); i != right_graph.end(); ++i){
		int front_vertex = (*(*i).begin());
		if(inVector(right_graph_to_delete, front_vertex)){//can speed this up
			list<list<int> >::iterator tmp_delete_it = i;
			right_graph.erase(tmp_delete_it);
			--i;
		}
		else{
			for(list<int>::iterator i1 = (*i).begin(); i1!=(*i).end(); ++i1){
				if(inVector(right_graph_to_delete, (*i1))){
					list<int>::iterator tmp_delete_it2 = i1;
					(*i).erase(tmp_delete_it2);
					--i1;
				}
			}
		}
	}


	//delete V

	int deleted_vertex = (*(*current_largest).begin());

	tmp_graph.erase(current_largest);

	//delete V from adjacency list
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

	right->graph = right_graph;
	left->graph = tmp_graph;
}

void read_graph(list<list<int> > &graph,int &edge_count,char* argv[]){
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

		//while(!ifs.eof()){
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

}

int degree(list<list<int> >::iterator V, list<list<int> > &Graph){
	if(Graph.size() == 0)
		return 0;
	else
		return (*V).size() - 1;
}

void degree_one_optimization(list<list<int> > &Graph, TreeNode* node, vector<int> &curr_min_cover, list<list<int> > &Original_Graph, int edge_count){
	vector<int> vertices_to_delete;
	bool degree_one_found = false;
	
	while(Graph.size()>0){
		degree_one_found = false;
	 	list<list<int> >::iterator V = Graph.begin();	
	 	for(V; V != Graph.end(); ++V){
	 		if(degree(V, Graph) == 1){ //degree 1, insert its neighbor to delete vector
	 			degree_one_found = true;
	 			list<int>::iterator it = (*V).begin();
	 			vertices_to_delete.push_back((*it));
	 			++it;
	 			if(!inVector(node->cover_Vertex, (*it)) && !inVector(vertices_to_delete, (*it))) {
			 		vertices_to_delete.push_back((*it));
			 		node->cover_Vertex.push_back((*it));
			 	}
		 	}
	 	}
	 	
	 	if(degree_one_found == false)
	 		break;
	 	//delete degree 1 neighbors from graph
	 	for(list<list<int> >::iterator i = Graph.begin(); i != Graph.end(); ++i){
			int front_vertex = (*(*i).begin());
			if(inVector(vertices_to_delete, front_vertex)){
				list<list<int> >::iterator tmp_delete_it = i;
				Graph.erase(tmp_delete_it);
				--i;
			}
			else{
				for(list<int>::iterator i1 = (*i).begin(); i1!=(*i).end(); ++i1){
					if(inVector(vertices_to_delete, (*i1))){
						list<int>::iterator tmp_delete_it2 = i1;
						(*i).erase(tmp_delete_it2);
						--i1;
					}
				}
			}
		}
		vertices_to_delete.clear();
	}

 }   

void print_graph(std::list<std::list<int> > &graph){
 	for(list<list<int> >::iterator it = graph.begin(); it!= graph.end(); ++it){
 		for(list<int>::iterator it_2= (*it).begin(); it_2 != (*it).end(); ++it_2 ){
 			cout<<(*it_2)<<" ";
 		}
 		cout<<endl;
 	}
 }

void print_cover(std::vector<int> &cover){
	for(int i =0; i<cover.size(); ++i){
		cout<<cover[i]<<" ";
	}
	cout<<endl;
}