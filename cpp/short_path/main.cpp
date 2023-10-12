
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int to;
  int weight;
};

vector<vector<Edge>> adjacency_list; // 邻接表
vector<int> dis;                     // 存储最短距离
vector<int> predecessor;             // 存储前驱节点

void initialize(int num_nodes, int start_node) {
  adjacency_list.resize(num_nodes);
  dis.assign(num_nodes, INT_MAX);
  predecessor.assign(num_nodes, -1);
  dis[start_node] = 0;
}

void relax(int u, int v, int weight) {
  if (dis[u] != INT_MAX && dis[u] + weight < dis[v]) {
    dis[v] = dis[u] + weight;
    predecessor[v] = u;
  }
}

bool bellmanFord(int start_node) {
  initialize(adjacency_list.size(), start_node);

  queue<int> q;
  vector<bool> in_queue(adjacency_list.size(), false);

  q.push(start_node);
  in_queue[start_node] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_queue[u] = false;

    for (const Edge &edge : adjacency_list[u]) {
      int v = edge.to;
      int weight = edge.weight;

      relax(u, v, weight);

      if (!in_queue[v]) {
        q.push(v);
        in_queue[v] = true;
      }
    }
  }

  // 检查负权环路
  for (uint32_t u = 0; u < adjacency_list.size(); ++u) {
    for (const Edge &edge : adjacency_list[u]) {
      int v = edge.to;
      int weight = edge.weight;

      if (dis[u] != INT_MAX && dis[u] + weight < dis[v]) {
        return false; // 存在负权环路
      }
    }
  }

  return true;
}

int main() {
  int num_nodes = 5;
  int start_node = 0;

  // 构建邻接表
  adjacency_list.resize(num_nodes);
  adjacency_list[0].push_back({1, 1234});
  adjacency_list[1].push_back({2, 100});
  // adjacency_list[0].push_back({1, 2});
  // adjacency_list[0].push_back({2, 4});
  // adjacency_list[1].push_back({2, 1});
  // adjacency_list[1].push_back({3, 7});
  // adjacency_list[2].push_back({3, 3});
  // adjacency_list[2].push_back({4, 5});
  // adjacency_list[4].push_back({3, -6});

  if (bellmanFord(start_node)) {
    cout << "Shortest diss from node " << start_node << ":" << endl;
    for (int i = 0; i < num_nodes; ++i) {
      cout << "Node " << i << ": " << dis[i] << endl;
    }
  } else {
    cout << "Graph contains a negative-weight cycle." << endl;
  }

  return 0;
}
