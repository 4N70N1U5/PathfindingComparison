#ifndef SolveVisualizer_HPP
#define SolveVisualizer_HPP

#include "Maze.hpp"

class SolveVisualizer
{
public:
    static void visualizeBFS(Maze *, sf::RenderWindow *);
    static void visualizeDFS(Maze *, sf::RenderWindow *);
    static void visualizeDijkstra(Maze *, sf::RenderWindow *);
    static void visualizeBeFS(Maze *, sf::RenderWindow *);
    static void visualizeAStar(Maze *, int, sf::RenderWindow *);
};

#endif
