#include "../include/Maze.hpp"
#include "../include/MazeSolver.hpp"
#include "../include/SolveVisualizer.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

void drawRect(sf::RenderTarget *target, Maze *maze, pair<int, int> location, sf::Color color)
{
    location.first++;
    location.second++;

    pair<int, int> cellSize = {target->getSize().x / (maze->getColumns() + 2), target->getSize().y / (maze->getRows() + 2)}; // {horizontal, vertical}
    // pair<int, int> cellSize = {target->getSize().x / (maze->getColumns()), target->getSize().y / (maze->getRows())}; // {horizontal, vertical}

    sf::RectangleShape outline(sf::Vector2f(cellSize.first - 4 * (cellSize.first * 0.1), cellSize.second - 4 * (cellSize.second * 0.1))),
        rect(sf::Vector2f(cellSize.first - 6 * (cellSize.first * 0.1), cellSize.second - 6 * (cellSize.second * 0.1)));

    // sf::CircleShape outline(min(cellSize.first, cellSize.second) - 4 * (min(cellSize.first, cellSize.second) * 0.1));
    // sf::CircleShape rect(min(cellSize.first, cellSize.second) - 6 * (min(cellSize.first, cellSize.second) * 0.1));

    // outline.setOrigin(outline.getRadius(), outline.getRadius());
    // rect.setOrigin(rect.getRadius(), rect.getRadius());

    outline.setFillColor(sf::Color::Black);
    outline.setPosition(location.second * cellSize.first + 2 * (cellSize.first * 0.1), location.first * cellSize.second + 2 * (cellSize.second * 0.1));
    // outline.setPosition(location.second * cellSize.first + 2 * (cellSize.first * 0.1), location.first * cellSize.second + 2 * (cellSize.second * 0.1));
    // NOT USED - outline.setPosition(location.second * cellSize.first * (cellSize.first * 0.1), location.first * cellSize.second * (cellSize.second * 0.1));

    rect.setFillColor(color);
    rect.setPosition(location.second * cellSize.first + 3 * (cellSize.first * 0.1), location.first * cellSize.second + 3 * (cellSize.second * 0.1));
    // rect.setPosition(location.second * cellSize.first + 3 * (cellSize.first * 0.1), location.first * cellSize.second + 3 * (cellSize.second * 0.1));
    // NOT USED - rect.setPosition(location.second * cellSize.first + 1 * (cellSize.first * 0.1), location.first * cellSize.second + 1 * (cellSize.second * 0.1));

    target->draw(outline);
    target->draw(rect);
}

void SolveVisualizer::drawVisualization(sf::RenderTarget *target, Maze *maze, bool showWeights, vector<pair<pair<int, int>, sf::Color>> *nodeColors, int steps)
{
    maze->draw(target, showWeights);

    for (int i = 0; i < min(steps, (int)nodeColors->size()); i++)
    {
        drawRect(target, maze, nodeColors->at(i).first, nodeColors->at(i).second);
    }
}

// void SolveVisualizer::visualizeBFS(sf::RenderTarget *target, Maze *maze)
// {
//     vector<pair<pair<int, int>, sf::Color>> nodeColors;

//     MazeSolver::breadthFirstSearch(maze, &nodeColors);

//     drawVisualization(target, maze, &nodeColors);
// }

// void SolveVisualizer::visualizeDFS(sf::RenderTarget *target, Maze *maze)
// {
//     vector<pair<pair<int, int>, sf::Color>> nodeColors;

//     MazeSolver::depthFirstSearch(maze, &nodeColors);

//     drawVisualization(target, maze, &nodeColors);
// }

// void SolveVisualizer::visualizeDijkstra(sf::RenderTarget *target, Maze *maze)
// {
//     vector<pair<pair<int, int>, sf::Color>> nodeColors;

//     MazeSolver::dijkstra(maze, &nodeColors);

//     drawVisualization(target, maze, &nodeColors);
// }

// void SolveVisualizer::visualizeBeFS(sf::RenderTarget *target, Maze *maze)
// {
//     vector<pair<pair<int, int>, sf::Color>> nodeColors;

//     MazeSolver::bestFirstSearch(maze, &nodeColors);

//     drawVisualization(target, maze, &nodeColors);
// }

// void SolveVisualizer::visualizeAStar(sf::RenderTarget *target, Maze *maze, int heuristicWeight)
// {
//     vector<pair<pair<int, int>, sf::Color>> nodeColors;

//     MazeSolver::aStar(maze, heuristicWeight, &nodeColors);

//     drawVisualization(target, maze, &nodeColors);
// }
