#ifndef Maze_HPP
#define Maze_HPP

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <boost/functional/hash.hpp>

using namespace std;

class Maze
{
private:
    int rows, columns;
    unordered_map<pair<int, int>, vector<pair<int, int>>, boost::hash<pair<int, int>>> adjacency;

public:
    Maze(int, int);

    int getRows();
    int getColumns();

    void addEdge(pair<int, int>, pair<int, int>);

    void print();
};

#endif