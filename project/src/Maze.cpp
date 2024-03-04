#include "../include/Maze.hpp"

#include <iostream>
#include <random>

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
