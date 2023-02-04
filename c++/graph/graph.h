#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>

using namespace std;

struct Node_t {
  int Id;
  string Name;
};

struct Edge_t {
  int From;
  int To;
};

struct Graph_t {
  vector<Node_t> Nodes;
  vector<Edge_t> Edges;
  int findNode(string &Name);
  void createNode(string &NodeName);
  void createEdge(string &ToNode, vector<string> &FromNodes);
  void writeGVFile(string &FileName, int Fmt);
};
#endif
