#include "../include/Maze.hpp"
#include "../include/MazeSolver.hpp"
#include "../include/SolveVisualizer.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#define TARGET_NODE make_pair(maze->getRows() - 1, maze->getColumns() - 1)
#define DELAY 25

void drawRect(sf::RenderWindow *window, Maze *maze, pair<int, int> location, sf::Color color)
{
    location.first++;
    location.second++;

    pair<int, int> cellSize = {window->getSize().x / (maze->getColumns() + 2), window->getSize().y / (maze->getRows() + 2)}; // {horizontal, vertical}

    sf::RectangleShape outline(sf::Vector2f(cellSize.first - 4 * (cellSize.first * 0.1), cellSize.second - 4 * (cellSize.second * 0.1))),
        rect(sf::Vector2f(cellSize.first - 6 * (cellSize.first * 0.1), cellSize.second - 6 * (cellSize.second * 0.1)));

    outline.setFillColor(sf::Color::Black);
    outline.setPosition(location.second * cellSize.first + 2 * (cellSize.first * 0.1), location.first * cellSize.second + 2 * (cellSize.second * 0.1));

    rect.setFillColor(color);
    rect.setPosition(location.second * cellSize.first + 3 * (cellSize.first * 0.1), location.first * cellSize.second + 3 * (cellSize.second * 0.1));

    window->draw(outline);
    window->draw(rect);
}

void drawVisualization(sf::RenderWindow *window, Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "Close window to continue...\n";

    sf::Clock clock;
    int steps = 0;

    while (window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
            }
        }

        if (steps < nodeColors->size() && clock.getElapsedTime().asMilliseconds() >= DELAY)
        {
            steps++;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                steps = min(steps + 5, (int)nodeColors->size());
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                steps = nodeColors->size();
            }

            clock.restart();
        }

        window->clear(sf::Color::White);

        maze->draw(window);

        for (int i = 0; i < steps; i++)
        {
            drawRect(window, maze, nodeColors->at(i).first, nodeColors->at(i).second);
        }

        window->display();
    }
}

void SolveVisualizer::visualizeBFS(sf::RenderWindow *window, Maze *maze)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::breadthFirstSearch(maze, &nodeColors);

    drawVisualization(window, maze, &nodeColors);
}

void SolveVisualizer::visualizeDFS(sf::RenderWindow *window, Maze *maze)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::depthFirstSearch(maze, &nodeColors);

    drawVisualization(window, maze, &nodeColors);
}

void SolveVisualizer::visualizeDijkstra(sf::RenderWindow *window, Maze *maze)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::dijkstra(maze, &nodeColors);

    drawVisualization(window, maze, &nodeColors);
}

void SolveVisualizer::visualizeBeFS(sf::RenderWindow *window, Maze *maze)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::bestFirstSearch(maze, &nodeColors);

    drawVisualization(window, maze, &nodeColors);
}

void SolveVisualizer::visualizeAStar(sf::RenderWindow *window, Maze *maze, int heuristicWeight)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::aStar(maze, heuristicWeight, &nodeColors);

    drawVisualization(window, maze, &nodeColors);
}
