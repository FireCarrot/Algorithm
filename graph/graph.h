#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// adjacency list
class Graph {
public:
  Graph(int v);
  ~Graph();
  void insert(int s, int d);
  vector<int> findShortestPath(int d);
  bool isConnected(int s, int d);
  void dfsAll();
  vector<int> bfs(int source = 0, int destination = -1);

private:
  void dfs(int current, vector<bool>& visited);

  vector<int>* vertices_;
  int v;
};

Graph::Graph(int v) {
  vertices_ = new vector<int>[v];
  this->v = v;
}

Graph::~Graph() {
  delete[] vertices_;
}

void Graph::insert(int s, int d) {
  vertices_[s].push_back(d);
}

void Graph::dfs(int current, vector<bool>& visited) {
  cout << current << " ";
  visited[current] = true;

  for (int i = 0; i < vertices_[current].size(); i++) {
    int index = vertices_[current][i];
    if (visited[index] == false)
      dfs(index, visited);
  }
}

void Graph::dfsAll() {
  if (!vertices_)
    return;

  vector<bool> visited(v, false);

  for (int i = 0; i < v; i++) {
    if (visited[i] == false)
      dfs(i, visited);
  }
}

vector<int> Graph::bfs(int source, int des) {
  if (!vertices_)
    return vector<int>();

  vector<int> path;
  vector<bool> discovered(v, false);

  if (des == -1)
    des = v;

  int index = source;
  queue<int> q;
  q.push(index);
  discovered[index] = true;

  while (!q.empty()) {
    index = q.front();
    q.pop();
    path.push_back(index);

    if (index == des)
      break;

    for (int j = 0; j < vertices_[index].size(); j++) {
      int i = vertices_[index][j];
      if (discovered[i] == false) {
        discovered[i] = true;
        q.push(i);
      }
    }
  }

  return path;
}

vector<int> Graph::findShortestPath(int d) {
  // parent index of current vertex on bfs
  vector<int> parent(v, -1);
  // distance to current vertex from start on bfs
  vector<int> distance(v, -1);

  int start = 0;
  queue<int> q;
  q.push(start);

  parent.push_back(start);
  distance.push_back(start);

  while (!q.empty()) {
    int index = q.front();
    q.pop();

    for (int i = 0; i < vertices_[index].size(); i++) {
      int current = vertices_[index][i];
      if (distance[current] == -1) {
        q.push(current);
        parent[current] = index;
        distance[current] = distance[index] + 1;
      }
    }
  }

  vector<int> shortest_path;
  shortest_path.push_back(d);
  while (parent[d] != start) {
    d = parent[d];
    shortest_path.push_back(d);
  }

  shortest_path.push_back(start);

  std::reverse(shortest_path.begin(), shortest_path.end());

  return shortest_path;
}

bool Graph::isConnected(int s, int d) {
  if (!vertices_)
    return false;

  if (bfs(s, d).empty())
    return false;

  return true;
}

#endif // #define GRAPH_H_
