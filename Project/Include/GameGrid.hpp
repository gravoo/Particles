#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iostream>
#include <iomanip>

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

  GameGrid() = default;
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

struct GridWithWeights: GameGrid {
  std::unordered_set<Location> forests;
  GridWithWeights(int w, int h): GameGrid(w, h) {}
  GridWithWeights() = default;
  double cost(Location from_node, Location to_node) const {
    return forests.count(to_node) ? 5 : 1;
  }
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

inline double heuristic(GameGrid::Location a, GameGrid::Location b) {
  int x1, y1, x2, y2;
  std::tie (x1, y1) = a;
  std::tie (x2, y2) = b;
  return abs(x1 - x2) + abs(y1 - y2);
}

template<typename Graph>
void a_star_search
  (const Graph& graph,
   typename Graph::Location start,
   typename Graph::Location goal,
   std::unordered_map<typename Graph::Location, typename Graph::Location>& came_from,
   std::unordered_map<typename Graph::Location, double>& cost_so_far)
{
  typedef typename Graph::Location Location;
  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;

  while (!frontier.empty()) {
    auto current = frontier.get();

    if (current == goal) {
      break;
    }

    for (auto& next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
}

template<typename Location>
std::vector<Location> reconstruct_path( Location start, Location goal, std::unordered_map<Location, Location>& came_from )
{
  std::vector<Location> path;
  Location current = goal;
  path.push_back(current);
  while (current != start) {
    current = came_from[current];
    path.push_back(current);
  }
  path.push_back(start); // optional
//   std::reverse(path.begin(), path.end());
  return path;
}
