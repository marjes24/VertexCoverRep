#ifndef TREE_H
#define TREE_H

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

#endif   
