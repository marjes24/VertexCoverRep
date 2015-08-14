#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Tree.h"
#include <vector>
#include <list>
#include <stack> 
#include <utility>

using namespace std;


vector<int> DFSCover(list<list<int> > graph, int edge_count, int &leaf_count);
bool inVector(vector<int> &v,  int &n);
bool checkVertices(list<list<int> >&graph, vector<int> &cover_Vertex, int edge_count);
void read_graph(list<list<int> > &graph,int &edge_count,char* argv[]);
list<list<int> >::iterator largest_vertex(list<list<int> > &graph);
void make_child_graph(list<list<int> > &tmp_graph, TreeNode *right, TreeNode *left, list<list<int> >::iterator current_largest);

     
#endif