#include "graph.h"

int main() {
  // create 10 vertices directed graph

  int n = 10;
  Graph graph(n);

  graph.insert(0,1);
  graph.insert(0,2);
  graph.insert(0,3);
  graph.insert(0,6);
  graph.insert(1,2);
  graph.insert(1,3);
  graph.insert(1,4);
  graph.insert(2,3);
  graph.insert(2,4);
  graph.insert(2,5);
  graph.insert(3,4);
  graph.insert(3,6);
  graph.insert(6,7);
  graph.insert(8,9);

  cout << "dfs traverse" << endl;
  graph.dfsAll();
  cout << endl;

  cout << "bfs traverse" << endl;
  vector<int> bfs_traverse = graph.bfs();
  for (int v : bfs_traverse)
    cout << v << " ";
  cout << endl;

  cout << "test if connected" << endl;
  int test[2] = {1, 8};
  cout << test[0] << " is connected to "<< test[1] << " ? " << (graph.isConnected(test[0], test[1]) ? "true":"false") << endl;

  cout << "find shorted path of 7" <<endl;
  vector<int> path = graph.findShortestPath(7);
  for (int v : path) {
    cout << v << " ";
  }
  cout << endl;
}
