#ifndef MazeSolver_HPP
#define MazeSolver_HPP

#include "Maze.hpp"

class MazeSolver
{
public:
    void bfsSolve(Maze *);
    void dfsSolve(Maze *);
    void dijkstraSolve(Maze *);
};

#endif
