#include "../include/Maze.hpp"
#include "../include/MazeSolver.hpp"
#include "../include/SolveVisualizer.hpp"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#define TARGET_NODE make_pair(maze->getRows() - 1, maze->getColumns() - 1)
#define DELAY 25

void drawCircle(sf::RenderWindow *window, pair<int, int> location, sf::Color color)
{
    location.first++;
    location.second++;

    sf::CircleShape circle(3);
    circle.setFillColor(color);
    circle.setPosition(location.second * 10 + 2, location.first * 10 + 2);

    window->draw(circle);
}

void drawVisualization(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors, sf::RenderWindow *window)
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
        }

        if (steps < nodeColors->size() && clock.getElapsedTime().asMilliseconds() >= DELAY)
        {
            steps++;
            clock.restart();
        }

        window->clear(sf::Color::White);

        maze->draw(window);

        for (int i = 0; i < steps; i++)
        {
            drawCircle(window, nodeColors->at(i).first, nodeColors->at(i).second);
        }

        window->display();
    }
}

void SolveVisualizer::visualizeBFS(Maze *maze, sf::RenderWindow *window)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::breadthFirstSearch(maze, &nodeColors);

    drawVisualization(maze, &nodeColors, window);
}

void SolveVisualizer::visualizeDFS(Maze *maze, sf::RenderWindow *window)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::depthFirstSearch(maze, &nodeColors);

    drawVisualization(maze, &nodeColors, window);
}

void SolveVisualizer::visualizeDijkstra(Maze *maze, sf::RenderWindow *window)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::dijkstra(maze, &nodeColors);

    drawVisualization(maze, &nodeColors, window);
}

void SolveVisualizer::visualizeBeFS(Maze *maze, sf::RenderWindow *window)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::bestFirstSearch(maze, &nodeColors);

    drawVisualization(maze, &nodeColors, window);
}

void SolveVisualizer::visualizeAStar(Maze *maze, int heuristicWeight, sf::RenderWindow *window)
{
    vector<pair<pair<int, int>, sf::Color>> nodeColors;

    MazeSolver::aStar(maze, heuristicWeight, &nodeColors);

    drawVisualization(maze, &nodeColors, window);
}
