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

GameGrid::GameGrid(int width_, int height_) : width(width_), height(height_) {}




