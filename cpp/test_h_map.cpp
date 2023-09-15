#include <iostream>
#include <map>
#include <string>

// 你的 map_get 函数代码
template <typename Map, typename Key>
typename Map::mapped_type &map_get(Map &map, Key &&key) {
  auto res = map.lower_bound(key);

  if (res == map.end() || key != res->first) {
    res = map.emplace_hint(res, std::piecewise_construct,
                           std::forward_as_tuple(key), std::tuple<>());
  }

  return res->second;
}

int main() {
  std::map<int, std::string> myMap;

  // 添加一些键值对
  myMap[1] = "One";
  myMap[2] = "Two";
  myMap[3] = "Three";

  // 测试 map_get 函数
  myMap[4];
  std::cout << "Value for key 2: " << map_get(myMap, 2) << std::endl;
  std::cout << "Value for key 4: " << map_get(myMap, 4) << std::endl;

  return 0;
}
