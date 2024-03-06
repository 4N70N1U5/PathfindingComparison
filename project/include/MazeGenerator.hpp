#ifndef MazeGenerator_HPP
#define MazeGenerator_HPP

#include "Maze.hpp"

#include <unordered_set>
#include <boost/functional/hash.hpp>

using namespace std;

class MazeGenerator
{
private:
    long seed;
    unordered_set<pair<int, int>, boost::hash<pair<int, int>>> included;

    int getDirectionBetween(pair<int, int>, pair<int, int>);
    pair<int, int> getRandomUnvisited(Maze *);
    pair<int, int> getNeighbor(pair<int, int>, int);
    vector<pair<int, int>> getAllNeighbors(Maze *, pair<int, int>);
    void randomWalk(Maze *);

public:
    MazeGenerator(long);

    void generate(Maze *, bool);
};

#endif
