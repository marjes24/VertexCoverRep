#ifndef TREE_H
#define TREE_H

#include <list>
#include <vector>

struct TreeNode{
	TreeNode* right_child;
	TreeNode* left_child;

	std::list<std::list<int> > graph;

	std::vector<int> cover_Vertex;

};


#endif