#ifndef TREE_H
#define TREE_H

#include <list>
#include <vector>
#include <utility>

struct TreeNode{
	TreeNode* right_child;
	TreeNode* left_child;

	int* graph;
	int graph_size;

	std::vector<int> cover_vertex;
	std::vector<std::pair<int,int> > covered_edges;

};

#endif       
