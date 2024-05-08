#ifndef MazeSolver_HPP
#define MazeSolver_HPP

#include "Maze.hpp"

class MazeSolver
{
private:
    static long long bfsTime, dfsTime, dijkstraTime, befsTime, aStarTime;
    static long long bfsCost, dfsCost, dijkstraCost, befsCost, aStarCost;

public:
    static void breadthFirstSearch(Maze *);
    static void depthFirstSearch(Maze *);
    static void dijkstra(Maze *);
    static void bestFirstSearch(Maze *);
    static void aStar(Maze *);

    static void printResults();
};

#endif
