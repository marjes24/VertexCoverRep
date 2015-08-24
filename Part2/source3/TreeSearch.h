#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <list>
#include <vector>
#include <utility>

struct TreeNode{
	TreeNode* right_child;
	TreeNode* left_child;

	std::list<std::list<int> > graph;

	std::vector<int> cover_Vertex;

	std::vector<std::pair<int,int> > current_covered_edges;

};


std::vector<int> DFSCover(std::list<std::list<int> > graph, int edge_count, int &leaf_count);

bool inVector(std::vector<int> &v,  int &n);

bool inVector(std::vector<std::pair<int,int> > &v, std::pair<int,int> &p); //overloaded

bool checkVertices(std::list<std::list<int> >&graph, std::vector<int> &cover_Vertex, int edge_count);

void read_graph(std::list<std::list<int> > &graph,int &edge_count,char* argv[]);

std::list<std::list<int> >::iterator largest_vertex(std::list<std::list<int> > &graph, TreeNode *current_node);

void make_child_graph(std::list<std::list<int> > &tmp_graph, TreeNode *right, TreeNode *left, std::list<std::list<int> >::iterator current_largest);

void update_child_covered_edges(std::list<std::list<int> >::iterator &current_largest, TreeNode* right, TreeNode* left, std::list<std::list<int> > &graph );

void degree_one_optimization(std::list<std::list<int> > &graph, std::list<std::list<int> >::iterator V, TreeNode *current_node);


#endif