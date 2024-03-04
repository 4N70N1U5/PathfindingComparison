#ifndef Maze_HPP
#define Maze_HPP

#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Maze
{
private:
    int rows, columns;
    unordered_map<pair<int, int>, vector<pair<int, int>>, boost::hash<pair<int, int>>> adjacency;

    vector<pair<pair<int, int>, int>> getAllNeighbors(pair<int, int>);
    void drawWall(sf::RenderWindow *, pair<int, int>, int);

public:
    Maze(int, int);

    int getRows();
    int getColumns();

    bool addEdge(pair<int, int>, pair<int, int>);

    void print();
    void draw(sf::RenderWindow *);
};

#endif
