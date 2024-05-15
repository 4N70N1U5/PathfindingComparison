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

vector<pair<pair<int, int>, int>> Maze::getAllNeighbors(pair<int, int> node)
{
    vector<pair<pair<int, int>, int>> neighbors;

    if (node.first > 0)
    {
        neighbors.push_back({{node.first - 1, node.second}, NORTH}); // Northern neighbor
    }

    if (node.second < columns - 1)
    {
        neighbors.push_back({{node.first, node.second + 1}, EAST}); // Eastern neighbor
    }

    if (node.first < rows - 1)
    {
        neighbors.push_back({{node.first + 1, node.second}, SOUTH}); // Southern neighbor
    }

    if (node.second > 0)
    {
        neighbors.push_back({{node.first, node.second - 1}, WEST}); // Western neighbor
    }

    return neighbors;
}

bool Maze::areNeighbors(pair<int, int> node1, pair<int, int> node2)
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

void Maze::drawWall(sf::RenderWindow *window, pair<int, int> wallLocation, int wallPosition)
{
    wallLocation.first++;
    wallLocation.second++;

    if (wallPosition == NORTH || wallPosition == SOUTH)
    {
        sf::RectangleShape wall(sf::Vector2f(10, 1));
        wall.setFillColor(sf::Color::Black);

        if (wallPosition == NORTH)
        {
            wall.setPosition(wallLocation.second * 10, wallLocation.first * 10);
        }
        else
        {
            wall.setPosition(wallLocation.second * 10, (wallLocation.first + 1) * 10 - 1);
        }

        window->draw(wall);
    }
    else
    {
        sf::RectangleShape wall(sf::Vector2f(1, 10));
        wall.setFillColor(sf::Color::Black);

        if (wallPosition == WEST)
        {
            wall.setPosition(wallLocation.second * 10, wallLocation.first * 10);
        }
        else
        {
            wall.setPosition((wallLocation.second + 1) * 10 - 1, wallLocation.first * 10);
        }

        window->draw(wall);
    }
}

int Maze::getRows()
{
    return rows;
}

int Maze::getColumns()
{
    return columns;
}

bool Maze::addEdge(pair<int, int> node1, pair<int, int> node2, int weight)
{
    if (areNeighbors(node1, node2))
    {
        return false;
    }

    adjacency[node1].push_back({node2, weight});
    adjacency[node2].push_back({node1, weight});

    return true;
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

void Maze::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (auto neighbor : getAllNeighbors({i, j}))
            {
                if (!areNeighbors({i, j}, neighbor.first))
                {
                    drawWall(window, {i, j}, neighbor.second);
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
            }
        }
    }
}
