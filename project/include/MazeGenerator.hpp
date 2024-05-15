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

    static pair<int, int> getRandomUnvisited(Maze *);
    static void randomWalk(Maze *, int);

public:
    static void generate(Maze *, bool, bool, long = time(0));
};

#endif
