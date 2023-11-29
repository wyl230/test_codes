#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 定义地图类
class GridMap {
public:
  GridMap(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows,
                vector<int>(cols, 1)); // 初始化地图，1表示可通行，0表示障碍物
  }

  void setObstacle(int row, int col) {
    grid[row][col] = 0; // 设置障碍物
  }

  void printMap() const {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cout << grid[i][j] << " ";
      }
      cout << endl;
    }
  }
  [[nodiscard]] int getGridValue(int row, int col) const {
    return grid[row][col];
  }

  [[nodiscard]] int getRows() const { return rows; }
  [[nodiscard]] int getCols() const { return cols; }

private:
  int rows;
  int cols;
  vector<vector<int>> grid;
};

// 定义 D* 算法类
class DStar {
public:
  explicit DStar(const GridMap &map)
      : map(map), rows(map.getRows()), cols(map.getCols()), km(0) {

    s_start = make_pair(0, 0);
    s_goal = make_pair(rows - 1, cols - 1);
    initialize();
  }

  void updateCell(int row, int col, int val) {
    U.insert(make_pair(row, col), val + km);
  }

  void replan() {
    while (true) {
      pair<int, int> u = U.topKey();
      if (U[u] >= V[u]) {
        break;
      }

      int k_old = V[u];
      int k_new = U[u];

      U.erase(u);
      V[u] = k_new;

      for (int i = 0; i < 8; ++i) {
        pair<int, int> v =
            make_pair(u.first + delta[i][0], u.second + delta[i][1]);
        if (isValid(v)) {
          int cost = map.getRows() * map.getCols(); // 初始值设置为一个大的数
          if (map.getGridValue(v.first, v.second) == 1) {
            cost = V[v];
          }
          updateVertex(v, cost);
        }
      }
    }
  }

  void updateVertex(const pair<int, int> &v, int cost) {
    if (V[v] > cost) {
      V[v] = cost;
      U.insert(v, cost + km);
    } else if (V[v] < cost && k_old[v] == k_m) {
      U.insert(v, cost + km);
    } else if (V[v] < cost && k_old[v] < k_m) {
      U.insert(v, cost + km + h(s_start, v));
    } else if (V[v] < cost && k_old[v] > k_m) {
      U.insert(v, cost + km + h(s_start, v));
    }
  }

  void initialize() {
    U.makeHeap();
    V.makeHeap();

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        V[make_pair(i, j)] = map.getRows() * map.getCols();
      }
    }

    V[s_goal] = 0;
    U.insert(s_goal, h(s_goal, s_start));
    k_m = 0;
  }

  int h(const pair<int, int> &a, const pair<int, int> &b) const {
    // 启发式函数，这里简化为曼哈顿距离
    return abs(a.first - b.first) + abs(a.second - b.second);
  }

  bool isValid(const pair<int, int> &cell) const {
    return (cell.first >= 0 && cell.first < rows && cell.second >= 0 &&
            cell.second < cols);
  }

  void printPath() const {
    pair<int, int> current = s_start;
    while (current != s_goal) {
      cout << "(" << current.first << ", " << current.second << ") ";
      int minCost = INT_MAX;
      pair<int, int> next;

      for (int i = 0; i < 8; ++i) {
        pair<int, int> neighbor = make_pair(current.first + delta[i][0],
                                            current.second + delta[i][1]);
        if (isValid(neighbor) && V[neighbor] < minCost) {
          minCost = V[neighbor];
          next = neighbor;
        }
      }

      current = next;
    }
    cout << "(" << s_goal.first << ", " << s_goal.second << ")" << endl;
  }

  void run() {
    replan();
    printPath();
  }

private:
  const GridMap &map;
  int rows;
  int cols;
  int km; // 修正因子
  pair<int, int> s_start;
  pair<int, int> s_goal;
  int k_m{}; // 当前最小代价值
  vector<vector<int>> k_old;
  int delta[8][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                     {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
  DStarLitePriorityQueue U{};
  DStarLitePriorityQueue V{};
};

// 定义优先队列类
class DStarLitePriorityQueue {
public:
  void insert(const pair<int, int> &key, int val) {
    pq.push(make_pair(key, val));
  }

  pair<int, int> topKey() const { return pq.top().first; }

  int operator[](const pair<int, int> &key) const {
    auto it = keyToVal.find(key);
    if (it != keyToVal.end()) {
      return it->second;
    } else {
      return INT_MAX;
    }
  }

  void erase(const pair<int, int> &key) { keyToVal.erase(key); }

  void makeHeap() {
    while (!pq.empty()) {
      pq.pop();
    }
    keyToVal.clear();
  }

private:
  priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>,
                 DStarLiteCompare>
      pq;
  unordered_map<pair<int, int>, int, pair_hash> keyToVal;
};

// 定义比较函数
struct DStarLiteCompare {
  bool operator()(const pair<pair<int, int>, int> &a,
                  const pair<pair<int, int>, int> &b) const {
    return a.second > b.second;
  }
};

// 定义哈希函数
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // 使用混合哈希函数
    return h1 ^ h2;
  }
};

int main() {
  // 创建地图
  GridMap map(5, 5);
  map.setObstacle(1, 1);
  map.setObstacle(2, 2);
  map.setObstacle(3, 3);

  // 创建 D* 算法对象并运行
  DStar dStar(map);
  dStar.run();

  return 0;
}

