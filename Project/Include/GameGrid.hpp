#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <queue>

namespace std {
  template <>
  struct hash<tuple<int,int> > {
    inline size_t operator()(const tuple<int,int>& location) const {
      int x, y;
      tie (x, y) = location;
      return x * 1812433253 + y;
    }
  };
}

class GameGrid {
public:
  using Location = std::tuple<int,int>;
  static std::array<Location, 4> DIRS;

  int width, height;
  std::unordered_set<Location> walls;

  GameGrid(int width_, int height_);

  inline bool in_bounds(Location id) const {
    int x, y;
    std::tie (x, y) = id;
    return 0 <= x && x < width && 0 <= y && y < height;
  }

  inline bool passable(Location id) const {
    return !walls.count(id);
  }
  std::vector<Location> neighbors(Location id) const;
};

template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  inline T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

