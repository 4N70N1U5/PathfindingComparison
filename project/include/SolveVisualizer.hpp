#ifndef SolveVisualizer_HPP
#define SolveVisualizer_HPP

#include "Maze.hpp"

class SolveVisualizer
{
public:
    static void visualizeBFS(sf::RenderWindow *, Maze *);
    static void visualizeDFS(sf::RenderWindow *, Maze *);
    static void visualizeDijkstra(sf::RenderWindow *, Maze *);
    static void visualizeBeFS(sf::RenderWindow *, Maze *);
    static void visualizeAStar(sf::RenderWindow *, Maze *, int);
};

#endif
