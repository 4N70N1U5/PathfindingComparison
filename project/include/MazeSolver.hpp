#ifndef MazeSolver_HPP
#define MazeSolver_HPP

#include "Maze.hpp"

class MazeSolver
{
private:
    long long bfsTime, dfsTime, dijkstraTime, befsTime, aStarTime;
    long long bfsCost, dfsCost, dijkstraCost, befsCost, aStarCost;

public:
    void breadthFirstSearch(Maze *);
    void depthFirstSearch(Maze *);
    void dijkstra(Maze *);
    void bestFirstSearch(Maze *);
    void aStar(Maze *);

    void printResults();
};

#endif
