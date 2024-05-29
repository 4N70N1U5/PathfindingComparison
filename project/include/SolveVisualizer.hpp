#ifndef SolveVisualizer_HPP
#define SolveVisualizer_HPP

#include "Maze.hpp"

class SolveVisualizer
{
public:
    static void drawVisualization(sf::RenderTarget *, Maze *, bool, vector<pair<pair<int, int>, sf::Color>> *, int);
    // static void visualizeBFS(sf::RenderTarget *, Maze *);
    // static void visualizeDFS(sf::RenderTarget *, Maze *);
    // static void visualizeDijkstra(sf::RenderTarget *, Maze *);
    // static void visualizeBeFS(sf::RenderTarget *, Maze *);
    // static void visualizeAStar(sf::RenderTarget *, Maze *, int);
};

#endif
