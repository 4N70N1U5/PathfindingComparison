#ifndef MazeSolver_HPP
#define MazeSolver_HPP

#include "Maze.hpp"

class MazeSolver
{
private:
    static int heuristicWeights[];
    static long long bfsTime, dfsTime, dijkstraTime, befsTime;
    static long long bfsCost, dfsCost, dijkstraCost, befsCost;
    static unordered_map<int, int> aStarTime, aStarCost;

public:
    static void breadthFirstSearch(Maze *, vector<pair<pair<int, int>, sf::Color>> * = nullptr);
    static void depthFirstSearch(Maze *, vector<pair<pair<int, int>, sf::Color>> * = nullptr);
    static void dijkstra(Maze *, vector<pair<pair<int, int>, sf::Color>> * = nullptr);
    static void bestFirstSearch(Maze *, vector<pair<pair<int, int>, sf::Color>> * = nullptr);
    static void aStar(Maze *, int, vector<pair<pair<int, int>, sf::Color>> * = nullptr);
    static void aStarAll(Maze *);

    static void printResults();
};

#endif
