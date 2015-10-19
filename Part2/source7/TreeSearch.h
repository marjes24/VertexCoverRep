#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <list>
#include <vector>
#include <utility>
extern int node_count;//global variable to count nodes
struct TreeNode{
	std::list<std::list<int> > graph;
	std::vector<int> cover_Vertex;
};


std::vector<int> DFSCover(std::list<std::list<int> > graph, int edge_count, int &leaf_count);

bool inVector(std::vector<int> &v,  int &n);

bool inVector(std::vector<std::pair<int,int> > &v, std::pair<int,int> &p); //overloaded

bool isCover(std::list<std::list<int> >&graph, std::vector<int> &cover_Vertex, int edge_count);

void read_graph(std::list<std::list<int> > &graph,int &edge_count,char* argv[]);

std::list<std::list<int> >::iterator largest_vertex(std::list<std::list<int> > &graph);

void make_child_graph(std::list<std::list<int> > &tmp_graph, TreeNode *right, TreeNode *left, std::list<std::list<int> >::iterator current_largest);

int degree(std::list<std::list<int> >::iterator V, std::list<std::list<int> > &Graph);

void degree_one_optimization(std::list<std::list<int> > &Graph, TreeNode* Node, std::vector<int> &curr_min_cover, std::list<std::list<int> > &Original_Graph, int edge_count);

void print_graph(std::list<std::list<int> > &graph);

void print_cover(std::vector<int> &cover);

void degree_two_optimization(std::list<std::list<int> > &Graph, std::list<std::list<int> >::iterator current_largest, std::vector<int> &curr_min_cover);

#endif