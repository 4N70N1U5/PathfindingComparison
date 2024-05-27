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
    unordered_map<pair<int, int>, vector<pair<pair<int, int>, int>>, boost::hash<pair<int, int>>> adjacency;

public:
    Maze(int, int);

    int getRows();
    int getColumns();

    int getEdgeWeight(pair<int, int>, pair<int, int>);
    vector<pair<pair<int, int>, int>> getAdjacencyList(pair<int, int>);
    vector<pair<pair<int, int>, int>> getAllNeighbors(pair<int, int>);

    bool areConnected(pair<int, int>, pair<int, int>);
    bool addEdge(pair<int, int>, pair<int, int>, int);

    void print();
    void drawWall(sf::RenderWindow *window, pair<int, int> wallLocation, int wallPosition);
    void drawPath(sf::RenderWindow *window, pair<int, int> nodeLocation, int direction, int weight, int maxWeight);
    void draw(sf::RenderWindow *);
};

#endif
