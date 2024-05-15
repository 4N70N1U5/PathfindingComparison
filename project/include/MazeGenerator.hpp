#ifndef MazeGenerator_HPP
#define MazeGenerator_HPP

#include "Maze.hpp"

#include <ctime>
#include <unordered_set>
#include <boost/functional/hash.hpp>

using namespace std;

class MazeGenerator
{
private:
    static unordered_set<pair<int, int>, boost::hash<pair<int, int>>> included;

    // int getDirectionBetween(pair<int, int>, pair<int, int>);
    // pair<int, int> getNeighbor(pair<int, int>, int);
    // vector<pair<int, int>> getAllNeighbors(Maze *, pair<int, int>);
    static pair<int, int> getRandomUnvisited(Maze *);
    static void randomWalk(Maze *, bool);

public:
    static void generate(Maze *, bool, bool, long = time(0));
};

#endif
