#include "graph.h"
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;

enum {
  OUTPUT_NODE_ID = 0,
  OUTPUT_NODE_NAME,
  OUTPUT_NODE_ID_NAME
};

int Graph_t::findNode(string &Name) {
  for (size_t i = 0; i < Nodes.size(); i++) {
    if (Nodes[i].Name == Name) {
      return (int)i;
    }
  }
  return -1;
}

void  Graph_t::writeGVFile(string &FileName, int Fmt) {
  ofstream os;
  os.open(FileName);
  string name1 = std::regex_replace(FileName, std::regex(".gv"), ".png");
  string name2 = std::regex_replace(FileName, std::regex(".gv"), ".json");
  os << "// dot -Tpng " << FileName << " -o " << name1 << "\n";
  os << "// dot -Tjson " << FileName << " -o " << name2 << "\n";
  os << "digraph G {\n";
  os << "  rankdir=TB;\n\n";
  if (Fmt == OUTPUT_NODE_ID_NAME) {
    for (size_t i = 0; i < Nodes.size(); i++) {
      os << "  " << Nodes[i].Id << " [label=\"" << Nodes[i].Id << " " << Nodes[i].Name << "\"];\n";
    }
    os << "\n";
  }
  for (size_t i = 0; i < Edges.size(); i++) {
    int From = Edges[i].From;
    int To = Edges[i].To;
    if (Fmt == OUTPUT_NODE_NAME) {
      os << "  " << Nodes[From].Name << " -> " << Nodes[To].Name << ";\n";
    }
    else if (Fmt == OUTPUT_NODE_ID || Fmt == OUTPUT_NODE_ID_NAME) {
      os << "  " << From << " -> " << To << ";\n";
    }
  }
  os << "}";
  os.close();
}

void Graph_t::createNode(string &NodeName) {
  for (size_t i = 0; i < Nodes.size(); i++) {
    if (Nodes[i].Name == NodeName) {
      return;
    }
  }
  Node_t Node;
  Node.Name = NodeName;
  Node.Id = Nodes.size();
  Nodes.push_back(Node);
}

void Graph_t::createEdge(string &ToNode,
                         vector<string> &FromNodes) {
  for (size_t i = 0; i < FromNodes.size(); i++) {
    Edge_t Edge;
    int idx = findNode(FromNodes[i]);
    if (idx == 1) std::cout << "Fail to find FromNodes\n";
    assert(idx != -1);
    Edge.From = idx;
    idx = findNode(ToNode);
    if (idx == 1) std::cout << "Fail to find ToNode\n";
    assert(idx != -1);
    Edge.To = idx;
    Edges.push_back(Edge);
  }
}

int main() {
  Graph_t Graph;

  string A = "A", B = "B", C = "C", D = "D";
  vector<string> From0;
  From0.push_back("A");
  vector<string> From1;
  From1.push_back("B");
  From1.push_back("C");
  
  Graph.createNode(A);
  Graph.createNode(B);
  Graph.createNode(C);
  Graph.createNode(D);

  Graph.createEdge(B, From0);
  Graph.createEdge(C, From0);
  Graph.createEdge(D, From1);

  std::string outFileName = "output1.gv";
  std::cout << "output file: " << outFileName << "\n";
  Graph.writeGVFile(outFileName, OUTPUT_NODE_ID);

  outFileName = "output2.gv";
  std::cout << "output file: " << outFileName << "\n";
  Graph.writeGVFile(outFileName, OUTPUT_NODE_NAME);

  outFileName = "output3.gv";
  std::cout << "output file: " << outFileName << "\n";
  Graph.writeGVFile(outFileName, OUTPUT_NODE_ID_NAME);
}
