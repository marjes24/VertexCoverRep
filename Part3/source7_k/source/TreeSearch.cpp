#include "TreeSearch.h"
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <time.h>
#include <limits>

using namespace std;
int node_count = 0;
int k;
vector<int> DFSCover(list<list<int> > graph,int edge_count, long int &leaf_count){
	//Initial vertex cover of size max, filled with zeroes. Only for first comparison. 
	int max_int = 10000;
	vector<int> curr_min_cover(max_int);			//holds smallest cover currently found. To be returned. 
	
	//Begin Depth First Search Vertex Cover Algorithm
	stack<TreeNode*> node_stack;				//stack filled with pointers to tree nodes. Used for DFS.
	TreeNode* root = new TreeNode;				//First tree node containing original graph. 
	root->graph = graph;					//Instead of reading graph before function, read here. Take away one less copy?????
	node_stack.push(root);
	
	//Initialize Variables
	TreeNode* tmp; 						//tmp is current node being visited in search tree
	list<list<int> >::iterator V;				// current largest is V. Graph node with highest degree
	TreeNode *right_child;					//right and left child used when branching. 
	TreeNode *left_child;
	list<int>::iterator V_adjacency_list_it; 		//to be used to iterate through the adjacency list of individual vertex

	while(!node_stack.empty()){		
		tmp =  node_stack.top();
		//node_stack.pop();
		degree_one_optimization(tmp->graph, tmp, tmp->cover_Vertex, graph, edge_count);  //run degreee one optimization function
		V = largest_vertex(tmp->graph);

		if(degree(V, tmp->graph) == 0){									
			if(tmp->cover_Vertex.size()<=curr_min_cover.size())	//don't branch
				curr_min_cover = tmp->cover_Vertex;
			++leaf_count;
			node_stack.pop();
			delete tmp;
			if(curr_min_cover.size() <= k)
				return curr_min_cover;
		} else if(degree(V, tmp->graph) == 2){
			clean_degree_zero(tmp->graph);	
			degree_two_optimization(tmp->graph, V, tmp->cover_Vertex);
			if(tmp->cover_Vertex.size()<=curr_min_cover.size())
				curr_min_cover = tmp->cover_Vertex;
			++leaf_count;
			node_stack.pop();	
			delete tmp;

		} else if(tmp->cover_Vertex.size()<=curr_min_cover.size()){	//branch. No need if the current cover is already bigger than the min cover.
			node_stack.pop();
			right_child = new TreeNode;
			left_child = new TreeNode;
			right_child->cover_Vertex = tmp->cover_Vertex;
			left_child->cover_Vertex = tmp->cover_Vertex;

			V_adjacency_list_it = (*V).begin();
			//v is in cover
			left_child->cover_Vertex.push_back((*V_adjacency_list_it));	//remember, may have to check if V is in vector...
			//neighbors are in cover
			V_adjacency_list_it++;
			for(V_adjacency_list_it; V_adjacency_list_it!=(*V).end(); V_adjacency_list_it++){
				right_child->cover_Vertex.push_back((*V_adjacency_list_it));
			}
			
			make_child_graph(tmp->graph, right_child, left_child, V);		//make graph for both right and left child
 			node_stack.push(right_child);
			node_stack.push(left_child);

			delete tmp;
			} else{
				node_stack.pop();
				delete tmp;
				++leaf_count;
			}
	}
	return curr_min_cover;
}

//check if int is in vector
bool inVector(vector<int> &v,  int &n){
	for(int i=0; i<v.size(); ++i){
		if(v[i]==n)
			return true;
	}
	return false;
}
//overload inVector function. 
bool inVector(vector<pair<int,int> > &v, pair<int,int> &p){
	for(int i=0; i<v.size(); ++i){
		if(v[i]==p)
			return true;
	}
	return false;
}

//check if cover_vertex is a cover of graph. 
bool isCover(list<list<int> >&graph, vector<int> &cover_Vertex, int edge_count){
	vector<pair<int,int> > covered_Edges;		//vector filled with edges formed by node in cover vertex and adjacent neighbors (a,b) a > b
	list<list<int> >::iterator V;			//current vertex
	list<int>::iterator V_adj_it;			//to iterate adjacency list of V
	int first, second, a, b;			//first
	for( V = graph.begin(); V!= graph.end(); V++){
		V_adj_it = (*V).begin();
		first = (*V_adj_it);
		if(inVector(cover_Vertex,(*V_adj_it))){
			V_adj_it++;
			for(V_adj_it; V_adj_it != (*V).end(); V_adj_it++){
				second = (*V_adj_it);
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
	list<list<int> >::iterator graph_it = graph.begin();	
	int size = 0;
	int largest_size=0;
	for(graph_it; graph_it!=graph.end(); graph_it++){
		size = (*graph_it).size();
		if(size > largest_size){
			largest_size = size;
			current_largest = graph_it;
		}
	}
	return current_largest;
}

void make_child_graph(list<list<int> > &tmp_graph, TreeNode *right, TreeNode *left, list<list<int> >::iterator V){
	
	vector<int> right_graph_to_delete;				//store vertices id's to delete for right graph, V and v's neighbors
	for(list<int>::iterator i = (*V).begin(); i != (*V).end(); ++i){
		int v_to_delete = (*i);
		right_graph_to_delete.push_back(v_to_delete);
	}
	//1st update tmp graph to make left graph
	int deleted_vertex = (*(*V).begin());				//delete V from graph
	tmp_graph.erase(V);
	list<list<int> >::iterator it1=tmp_graph.begin(); 
	list<int>::iterator it2;
	list<int>::iterator it3;
	for(it1; it1 != tmp_graph.end(); it1++){			//delete V from the adjacency list of other vertices
		for(it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
			if((*it2) == deleted_vertex){
				it3 = it2;
				(*it1).erase(it3); 
				it2--;
			}
		}
	}
	left->graph = tmp_graph;

	//make right graph by deleting V's neighbors
	int front_vertex;
	list<list<int> >::iterator i, tmp_delete_it;
	list<int>::iterator i1, tmp_delete_it2;
	for(i = tmp_graph.begin(); i != tmp_graph.end(); ++i){		//delete a neighbor from the graph
		front_vertex = (*(*i).begin());
		if(inVector(right_graph_to_delete, front_vertex)){
			tmp_delete_it = i;
			tmp_graph.erase(tmp_delete_it);
			--i;
		}
		else{
			for(i1 = (*i).begin(); i1!=(*i).end(); ++i1){	//delete neighbor from the adjacency list of other vertices
				if(inVector(right_graph_to_delete, (*i1))){
					tmp_delete_it2 = i1;
					(*i).erase(tmp_delete_it2);
					--i1;
				}
			}
		}
	}
	right->graph = tmp_graph;
}

void read_graph(list<list<int> > &graph,int &edge_count,char* argv[]){
	string first_arg = argv[1];
	k = atoi(argv[3]);
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

//Print Graph
void print_graph(std::list<std::list<int> > &graph){
 	for(list<list<int> >::iterator it = graph.begin(); it!= graph.end(); ++it){
 		for(list<int>::iterator it_2= (*it).begin(); it_2 != (*it).end(); ++it_2 ){
 			cout<<(*it_2)<<" ";
 		}
 		cout<<endl;
 	}
 }

//Print cover
void print_cover(std::vector<int> &cover){
	for(int i =0; i<cover.size(); ++i){
		cout<<cover[i]<<" ";
	}
	cout<<endl;
}

void print_vector(std::vector<int> &cover){
	for(int i =0; i<cover.size(); ++i){
		cout<<i<<":"<<cover[i]<<" ";
	}
	cout<<endl;
}
void degree_two_optimization(list<list<int> > &Graph, list<list<int> >::iterator V, vector<int> &tmp_min_cover){
	//find largest vertex id, make two arrays of that size//can instead just make array size of number of nodes
	int largest_id = 0;
	list<list<int> >::iterator it0 = Graph.begin();
	for(it0; it0 != Graph.end(); ++it0){
		int current_id = *((*it0).begin());
		if(current_id > largest_id)
			largest_id = current_id;
	}

	vector<int> cycle_id(largest_id + 1, -1); //a -1 will represent a vertex that doesn't exit in the graph
	vector<int> in_cover(largest_id + 1, -1);
	
	it0 = Graph.begin();
	for(it0; it0!= Graph.end(); ++it0){
		int current_id = *((*it0).begin());
		cycle_id[current_id] = 0;
		in_cover[current_id] = 0;
	}
	
	int current_cycle_id = 1; 
	bool remaining_cycles  = true;
	list<int>::iterator it_vertex =(*V).begin();
	int vertex_id =( *it_vertex);
	cycle_id[vertex_id] = current_cycle_id;
	++it_vertex;
	int neighbor1_id = (*it_vertex);
	++it_vertex;
	int neighbor2_id = (*it_vertex); 
	while(remaining_cycles){
		//if V in, neighbors not in
		//else neigbors in
		//go to unvisited  neighbor, repeat, if neighbors visited already, then choose new V 
		if(in_cover[vertex_id]){
			in_cover[neighbor1_id] = 0;			
			in_cover[neighbor2_id] = 0;
		} else{
			in_cover[neighbor1_id] = 1;
			in_cover[neighbor2_id] = 1;	
		}
		//pick unvisited neighbor
		if(cycle_id[neighbor1_id] == 0){
			for(list<list<int> >::iterator it = Graph.begin(); it != Graph.end(); ++it){
				int current_id = *((*it).begin());
				if(current_id == neighbor1_id){
					V = it;
					break;
				}
			}
		} else if(cycle_id[neighbor2_id] == 0) {
			for(list<list<int> >::iterator it = Graph.begin(); it != Graph.end(); ++it){
				int current_id = *((*it).begin());
				if(current_id == neighbor2_id){
					V = it;
					break;
				}
			}	
		} else{

			remaining_cycles = false;
			for(list<list<int> >::iterator it = Graph.begin(); it!=Graph.end(); ++it){
				int current_id = *((*it).begin());
				if(cycle_id[current_id] == 0){
					V = it;
					++current_cycle_id;
					remaining_cycles = true;
					break;
				}
			}
		}
		it_vertex = (*V).begin();
		vertex_id = (*it_vertex);
		cycle_id[vertex_id] = current_cycle_id;
		++it_vertex;
		neighbor1_id = (*it_vertex);
		++it_vertex;
		neighbor2_id = (*it_vertex); 
	}	

	for(int i = 0; i < in_cover.size(); ++i){
		if(in_cover[i] == 1)
			tmp_min_cover.push_back(i);
	} 
}

void clean_degree_zero(list<list<int> > &Graph){
	list<list<int> >::iterator V = Graph.begin();
	for(V; V!=Graph.end(); ++V){
		if(degree(V,Graph) == 0){
			list<list<int> >::iterator tmp_delete_V = V;
			Graph.erase(tmp_delete_V);
			--V;
		}
	}
}
