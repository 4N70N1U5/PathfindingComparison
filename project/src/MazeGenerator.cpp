#include "../include/Maze.hpp"
#include "../include/MazeGenerator.hpp"

#include <iostream>
#include <chrono>
#include <random>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

unordered_set<pair<int, int>, boost::hash<pair<int, int>>> MazeGenerator::included;

int getDirectionBetween(pair<int, int> node1, pair<int, int> node2)
{
    if (node1.first == node2.first)
    {
        if (node1.second < node2.second)
        {
            return EAST;
        }
        else
        {
            return WEST;
        }
    }
    else
    {
        if (node1.first < node2.first)
        {
            return SOUTH;
        }
        else
        {
            return NORTH;
        }
    }
}

pair<int, int> getNeighbor(pair<int, int> node, int direction)
{
    switch (direction)
    {
    case NORTH:
        return {node.first - 1, node.second};

    case EAST:
        return {node.first, node.second + 1};

    case SOUTH:
        return {node.first + 1, node.second};

    case WEST:
        return {node.first, node.second - 1};

    default:
        return {0, 0};
    }
}

vector<pair<int, int>> getAllNeighbors(Maze *maze, pair<int, int> node)
{
    vector<pair<int, int>> neighbors;

    if (node.first > 0)
    {
        neighbors.push_back({node.first - 1, node.second}); // Northern neighbor
    }

    if (node.second < maze->getColumns() - 1)
    {
        neighbors.push_back({node.first, node.second + 1}); // Eastern neighbor
    }

    if (node.first < maze->getRows() - 1)
    {
        neighbors.push_back({node.first + 1, node.second}); // Southern neighbor
    }

    if (node.second > 0)
    {
        neighbors.push_back({node.first, node.second - 1}); // Western neighbor
    }

    return neighbors;
}

pair<int, int> MazeGenerator::getRandomUnvisited(Maze *maze)
{
    pair<int, int> node;

    do
    {
        node.first = rand() % maze->getRows();
        node.second = rand() % maze->getColumns();
    } while (included.find(node) != included.end());

    return node;
}

void MazeGenerator::randomWalk(Maze *maze, bool weighted)
{
    pair<int, int> startNode = getRandomUnvisited(maze);
    unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> directionTaken;

    pair<int, int> currentNode = startNode, neighbor;

    while (included.find(currentNode) == included.end())
    {
        vector<pair<int, int>> neighbors = getAllNeighbors(maze, currentNode);
        neighbor = neighbors[rand() % neighbors.size()];

        directionTaken[currentNode] = getDirectionBetween(currentNode, neighbor);

        currentNode = neighbor;
    }

    vector<pair<pair<int, int>, int>> path;

    currentNode = startNode;

    while (included.find(currentNode) == included.end())
    {
        included.insert(currentNode);

        neighbor = getNeighbor(currentNode, directionTaken[currentNode]);

        if (weighted)
        {
            maze->addEdge(currentNode, neighbor, rand() % 1000 + 1);
        }
        else
        {
            maze->addEdge(currentNode, neighbor, 1);
        }

        currentNode = neighbor;
    }
}

void MazeGenerator::generate(Maze *maze, bool weighted, bool multiplePaths, long seed)
{
    included.clear();

    srand(seed);

    cout << "Will generate maze with " << maze->getRows() << " rows and " << maze->getColumns() << " columns with seed " << seed << ".\n";

    if (weighted)
    {
        cout << "Maze will be a weighted graph.\n";
    }
    else
    {
        cout << "Maze will be an unweighted graph.\n";
    }

    if (multiplePaths)
    {
        cout << "Maze will have multiple possible paths.\n";
    }
    else
    {
        cout << "Maze will have only one possible path.\n";
    }

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    cout << "Generating maze... " << flush;

    // Generate maze using Wilson's algorithm. The resulting maze will only
    // have one path from start to end.

    included.erase(included.begin(), included.end());

    included.insert({0, 0});

    while (included.size() < maze->getRows() * maze->getColumns())
    {
        randomWalk(maze, weighted);
    }

    // Add new edges to the maze to create cycles that will introduce new
    // paths to solve the maze.

    if (multiplePaths)
    {
        int additionalPaths = (maze->getRows() * maze->getColumns()) * ((double)(rand() % 26 + 25) / 100.0);

        for (int i = 0; i < additionalPaths;)
        {
            pair<int, int> node;

            node.first = rand() % maze->getRows();
            node.second = rand() % maze->getColumns();

            vector<pair<int, int>> neighbors = getAllNeighbors(maze, node);
            pair<int, int> neighbor = neighbors[rand() % neighbors.size()];

            if (weighted)
            {
                if (maze->addEdge(node, neighbor, rand() % 1000 + 1))
                {
                    i++;
                }
            }
            else if (maze->addEdge(node, neighbor, 1))
            {
                i++;
            }
        }
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    cout << "Done!\n";

    cout << "Maze successfully generated in "
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds)!\n";
}
