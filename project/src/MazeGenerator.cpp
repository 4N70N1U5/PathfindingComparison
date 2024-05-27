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

void MazeGenerator::randomWalk(Maze *maze, int maxWeight)
{
    pair<int, int> startNode = getRandomUnvisited(maze);

    unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> directionTaken;
    pair<int, int> currentNode = startNode, neighbor;

    while (included.find(currentNode) == included.end())
    {
        vector<pair<pair<int, int>, int>> neighbors = maze->getAllNeighbors(currentNode);
        int neighborIndex = rand() % neighbors.size();

        neighbor = neighbors[neighborIndex].first;
        directionTaken[currentNode] = neighbors[neighborIndex].second;

        currentNode = neighbor;
    }

    currentNode = startNode;

    while (included.find(currentNode) == included.end())
    {
        included.insert(currentNode);

        neighbor = getNeighbor(currentNode, directionTaken[currentNode]);

        maze->addEdge(currentNode, neighbor, rand() % maxWeight + 1);

        currentNode = neighbor;
    }
}

void MazeGenerator::generate(Maze *maze, bool weighted, bool multiplePaths, long seed)
{
    srand(seed);

    cout << "Will generate maze with " << maze->getRows() << " rows and " << maze->getColumns() << " columns with seed " << seed << ".\n";

    int maxWeight;

    if (weighted)
    {
        cout << "Maze will be a weighted graph.\n";

        maxWeight = maze->getRows() * maze->getColumns();

        cout << "Maximum weight will be " << maxWeight << ".\n";
    }
    else
    {
        cout << "Maze will be an unweighted graph.\n";

        maxWeight = 1;
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

    included.clear();

    included.insert({0, 0});

    while (included.size() < maze->getRows() * maze->getColumns())
    {
        randomWalk(maze, maxWeight);
    }

    if (multiplePaths)
    {
        int additionalPaths = (maze->getRows() * maze->getColumns()) * ((double)(rand() % 26 + 25) / 100.0);

        for (int i = 0; i < additionalPaths;)
        {
            pair<int, int> node;

            node.first = rand() % maze->getRows();
            node.second = rand() % maze->getColumns();

            vector<pair<pair<int, int>, int>> neighbors = maze->getAllNeighbors(node);
            pair<int, int> neighbor = neighbors[rand() % neighbors.size()].first;

            if (maze->addEdge(node, neighbor, rand() % maxWeight + 1))
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
