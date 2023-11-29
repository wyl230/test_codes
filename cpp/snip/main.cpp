#include <iostream>
#include <unordered_map>
#include <vector>

// Define node_id_t if not already defined
using node_id_t = int;

// Define RouteTable and RouteTableRes
using RouteTable =
    std::unordered_map<node_id_t, std::unordered_map<node_id_t, node_id_t>>;
using RouteTableRes =
    std::unordered_map<node_id_t,
                       std::unordered_map<node_id_t, std::vector<node_id_t>>>;

// Function to convert RouteTable to RouteTableRes
RouteTableRes convertRouteTable(const RouteTable &routeTable) {
  RouteTableRes route_table_res;
  for (const auto &[src, dst2next_hop] : routeTable) {
    for (const auto &[dst, next_hop] : dst2next_hop) {
      route_table_res[src][next_hop].push_back(dst);
    }
  }

  return route_table_res;
}

void printRouteTableRes(const RouteTableRes &route_table_res) {
  for (const auto &[sourceNode, innerMap] : route_table_res) {
    for (const auto &[destinationNode, nextHops] : innerMap) {
      std::cout << "route_table_res[" << sourceNode << "][" << destinationNode
                << "] = [";
      for (node_id_t nextHop : nextHops) {
        std::cout << nextHop << ", ";
      }
      std::cout << "]\n";
    }
  }
}

int main() {
  // Sample RouteTable
  // m[1][2] = 3
  // m[1][3] = 4
  // m[2][1] = 5
  // m[2][3] = 6
  // m[3][1] = 7
  // m[3][2] = 8
  // RouteTable routeTable = {
  //     {1, {{2, 3}, {3, 4}}}, {2, {{1, 5}, {3, 6}}}, {3, {{1, 7}, {2, 8}}}};

  RouteTable route_table = {
      {1, {{3, 2}, {2, 2}}}, {2, {{1, 1}, {3, 3}}}, {3, {{1, 2}, {2, 2}}}};
  // m[1][2] = 3

  for (const auto &[src, dst2next_hop] : route_table) {
    for (const auto &[dst, next_hop] : dst2next_hop) {
      std::cout << "route_table[" << src << "][" << dst << "] = " << next_hop
                << "\n";
    }
  }

  std::cout << "\n";

  // Convert RouteTable to RouteTableRes
  RouteTableRes route_table_res = convertRouteTable(route_table);
  printRouteTableRes(route_table_res);

  return 0;
}
