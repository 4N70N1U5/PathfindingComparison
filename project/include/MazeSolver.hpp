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
    static void breadthFirstSearch(Maze *);
    static void depthFirstSearch(Maze *);
    static void dijkstra(Maze *);
    static void bestFirstSearch(Maze *);
    static void aStar(Maze *);

    static void printResults();
};

#endif
