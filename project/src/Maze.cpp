#include "../include/Maze.hpp"

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Maze::Maze(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
}

int Maze::getRows()
{
    return rows;
}

int Maze::getColumns()
{
    return columns;
}

int Maze::getEdgeWeight(pair<int, int> node1, pair<int, int> node2)
{
    for (int i = 0; i < adjacency[node1].size(); i++)
    {
        if (adjacency[node1][i].first == node2)
        {
            return adjacency[node1][i].second;
        }
    }

    return -1;
}

vector<pair<pair<int, int>, int>> Maze::getAdjacencyList(pair<int, int> node)
{
    return adjacency[node];
}

vector<pair<pair<int, int>, int>> Maze::getAllNeighbors(pair<int, int> node)
{
    vector<pair<pair<int, int>, int>> neighbors;

    if (node.first > 0)
    {
        neighbors.push_back({{node.first - 1, node.second}, NORTH});
    }

    if (node.second < columns - 1)
    {
        neighbors.push_back({{node.first, node.second + 1}, EAST});
    }

    if (node.first < rows - 1)
    {
        neighbors.push_back({{node.first + 1, node.second}, SOUTH});
    }

    if (node.second > 0)
    {
        neighbors.push_back({{node.first, node.second - 1}, WEST});
    }

    return neighbors;
}

bool Maze::areConnected(pair<int, int> node1, pair<int, int> node2)
{
    for (int i = 0; i < adjacency[node1].size(); i++)
    {
        if (adjacency[node1][i].first == node2)
        {
            return true;
        }
    }

    return false;
}

bool Maze::addEdge(pair<int, int> node1, pair<int, int> node2, int weight)
{
    if (areConnected(node1, node2))
    {
        return false;
    }

    adjacency[node1].push_back({node2, weight});
    adjacency[node2].push_back({node1, weight});

    return true;
}

void Maze::print()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << "Node (" << i << ", " << j << "): ";

            for (auto neighbor : adjacency[{i, j}])
            {
                cout << "{(" << neighbor.first.first << ", " << neighbor.first.second << "), " << neighbor.second << "} ";
            }

            cout << "\n";
        }
    }
}

void Maze::drawWall(sf::RenderWindow *window, pair<int, int> wallLocation, int wallPosition)
{
    wallLocation.first++;
    wallLocation.second++;

    pair<int, int> cellSize = {window->getSize().x / (columns + 2), window->getSize().y / (rows + 2)}; // {horizontal, vertical}

    sf::RectangleShape wall;
    wall.setFillColor(sf::Color::Black);

    if (wallPosition == NORTH || wallPosition == SOUTH)
    {
        wall.setSize(sf::Vector2f(cellSize.first, cellSize.second * 0.1));

        if (wallPosition == NORTH)
        {
            wall.setPosition(wallLocation.second * cellSize.first, wallLocation.first * cellSize.second);
        }
        else
        {
            wall.setPosition(wallLocation.second * cellSize.first, (wallLocation.first + 1) * cellSize.second - cellSize.second * 0.1);
        }
    }
    else
    {
        wall.setSize(sf::Vector2f(cellSize.first * 0.1, cellSize.second));

        if (wallPosition == WEST)
        {
            wall.setPosition(wallLocation.second * cellSize.first, wallLocation.first * cellSize.second);
        }
        else
        {
            wall.setPosition((wallLocation.second + 1) * cellSize.first - cellSize.first * 0.1, wallLocation.first * cellSize.second);
        }
    }

    window->draw(wall);
}

void Maze::drawPath(sf::RenderWindow *window, pair<int, int> nodeLocation, int direction, int weight, int maxWeight)
{
    nodeLocation.first++;
    nodeLocation.second++;

    pair<int, int> cellSize = {window->getSize().x / (columns + 2), window->getSize().y / (rows + 2)}; // {horizontal, vertical}

    sf::RectangleShape path;

    double colorOffset = 255.0 - (((double)weight / (double)maxWeight) * 255.0);
    int redValue = min((int)colorOffset + 150, 255);
    int greenValue = max(0, (int)colorOffset - 105);
    path.setFillColor(sf::Color(redValue, greenValue, 0, 255));

    if (direction == NORTH || direction == SOUTH)
    {
        path.setSize(sf::Vector2f(cellSize.first * 0.2, cellSize.second * 0.6));

        if (direction == NORTH)
        {
            path.setPosition(nodeLocation.second * cellSize.first + cellSize.first * 0.4, nodeLocation.first * cellSize.second);
        }
        else
        {
            path.setPosition(nodeLocation.second * cellSize.first + cellSize.first * 0.4, nodeLocation.first * cellSize.second + cellSize.second * 0.4);
        }
    }
    else
    {
        path.setSize(sf::Vector2f(cellSize.first * 0.6, cellSize.second * 0.2));

        if (direction == WEST)
        {
            path.setPosition(nodeLocation.second * cellSize.first, nodeLocation.first * cellSize.second + cellSize.second * 0.4);
        }
        else
        {
            path.setPosition(nodeLocation.second * cellSize.first + cellSize.first * 0.4, nodeLocation.first * cellSize.second + cellSize.second * 0.4);
        }
    }

    window->draw(path);
}

void Maze::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (auto neighbor : getAllNeighbors({i, j}))
            {
                if (!areConnected({i, j}, neighbor.first))
                {
                    drawWall(window, {i, j}, neighbor.second);
                }
                else
                {
                    drawPath(window, {i, j}, neighbor.second, getEdgeWeight({i, j}, neighbor.first), rows * columns);
                }
            }

            if (i == 0)
            {
                drawWall(window, {i, j}, NORTH);
                drawWall(window, {i - 1, j}, SOUTH);
            }

            if (j == 0)
            {
                if (i != 0)
                {
                    drawWall(window, {i, j}, WEST);
                    drawWall(window, {i, j - 1}, EAST);
                }
                else
                {
                    drawPath(window, {i, j}, WEST, 0, rows * columns);
                    drawPath(window, {i, j - 1}, EAST, 0, rows * columns);
                }
            }

            if (i == rows - 1)
            {
                drawWall(window, {i, j}, SOUTH);
                drawWall(window, {i + 1, j}, NORTH);
            }

            if (j == columns - 1)
            {
                if (i != rows - 1)
                {
                    drawWall(window, {i, j}, EAST);
                    drawWall(window, {i, j + 1}, WEST);
                }
                else
                {
                    drawPath(window, {i, j}, EAST, 0, rows * columns);
                    drawPath(window, {i, j + 1}, WEST, 0, rows * columns);
                }
            }
        }
    }
}
