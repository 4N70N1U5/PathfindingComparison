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

void Maze::drawWall(sf::RenderWindow *window, pair<int, int> wallLocation, int wallPosition)
{
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

bool Maze::addEdge(pair<int, int> node1, pair<int, int> node2)
{
    if (find(adjacency[node1].begin(), adjacency[node1].end(), node2) != adjacency[node1].end())
    {
        return false;
    }

    adjacency[node1].push_back(node2);
    adjacency[node2].push_back(node1);

    return true;
}

void Maze::print()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << "Node (" << i << ", " << j << "): ";

            for (pair<int, int> neighbor : adjacency[{i, j}])
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }

            cout << endl;
        }
    }
}

void Maze::draw(sf::RenderWindow *window)
{
    window->clear(sf::Color::White);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (auto neighbor : getAllNeighbors({i, j}))
            {
                if (find(adjacency[{i, j}].begin(), adjacency[{i, j}].end(), neighbor.first) == adjacency[{i, j}].end())
                {
                    drawWall(window, {i, j}, neighbor.second);
                }
            }
        }
    }

    window->display();
}
