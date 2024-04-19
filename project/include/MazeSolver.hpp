#ifndef MazeSolver_HPP
#define MazeSolver_HPP

#include "Maze.hpp"

class MazeSolver
{
public:
    void breadthFirstSearch(Maze *);
    void depthFirstSearch(Maze *);
    void dijkstra(Maze *);
    void bestFirstSearch(Maze *);
    void aStar(Maze *);
};

#endif
