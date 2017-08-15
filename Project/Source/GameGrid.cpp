#include <GameGrid.hpp>
std::array<GameGrid::Location, 4> GameGrid::DIRS {Location{1, 0}, Location{0, -1}, Location{-1, 0}, Location{0, 1}};

std::vector<GameGrid::Location> GameGrid::neighbors(Location id) const {
    int x, y, dx, dy;
    std::tie (x, y) = id;
    std::vector<Location> results;

    for (auto dir : DIRS) {
        std::tie (dx, dy) = dir;
        Location next(x + dx, y + dy);
        if (in_bounds(next) && passable(next)) {
            results.push_back(next);
        }
    }

    if ((x + y) % 2 == 0) {
        std::reverse(results.begin(), results.end());
    }

    return results;
}

inline double heuristic(GameGrid::Location a, GameGrid::Location b) {
  int x1, y1, x2, y2;
  std::tie (x1, y1) = a;
  std::tie (x2, y2) = b;
  return abs(x1 - x2) + abs(y1 - y2);
}


GameGrid::GameGrid(int width_, int height_) : width(width_), height(height_) {}


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
