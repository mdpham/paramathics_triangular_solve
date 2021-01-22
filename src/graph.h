#ifndef GRAPH_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "ccs_matrix.h"

using namespace std;

// Modified DFS implementation from https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/ 
// 
class DependencyGraph {
  int V; // No. of vertices

  list<int>* adj;

  // A function used by DFS
  void DFSUtil(int v, bool visited[], DenseVector vector);

  public:
    DependencyGraph(CCSMatrix matrix); // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    vector<int> ReachSet(DenseVector vector); // prints DFS traversal of the complete graph
};
 
DependencyGraph::DependencyGraph(CCSMatrix matrix)
{
  int V = matrix.n;
  this->V = V;
  adj = new list<int>[V];

  // Add edges by looping over CCS matrix
  int i;
  for (int j = 0; j < matrix.n; j++)
  {
    for (int p = matrix.Lp[j]; p < matrix.Lp[j+1] ; p++) { 
      i = matrix.Li[p];
      adj[j].push_back(i); // Add i to j’s list.    
    }
  }

}
 
void DependencyGraph::DFSUtil(int v, bool visited[], DenseVector vector)
{
  visited[v] = true; // Mark the current node as visited

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    if (!visited[*i]) { DFSUtil(*i, visited, vector); }
  }
}
 
// The function to do DFS traversal. It uses recursive DFSUtil()
std::vector<int> DependencyGraph::ReachSet(DenseVector vector)
{
  // Mark all the vertices as not visited
  bool* visited = new bool[V];
  for (int i = 0; i < V; i++) {visited[i] = false;}

  // Call recursive helper starting from B of vector
  for (int i = 0; i < int(vector.B.size()); i++)
  {
    if (visited[vector.B[i]] == false) { DFSUtil(vector.B[i], visited, vector); }
  };

  std::vector<int> reach_set;
  for (int i = 0; i < V; i++) {if (visited[i]) { reach_set.push_back(i); }}

  printf("reach set of size %i \n", int(reach_set.size()));
  // for (int i = 0; i < reach_set.size(); i++) {printf("%i ", reach_set[i]);}
  // printf("\n");


  return reach_set;
};


#endif