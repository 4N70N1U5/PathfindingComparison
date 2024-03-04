#include "../include/Maze.hpp"
#include "../include/MazeGenerator.hpp"

#include <random>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

MazeGenerator::MazeGenerator(long seed)
{
    srand(seed);
}

int MazeGenerator::getDirectionBetween(pair<int, int> node1, pair<int, int> node2)
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

pair<int, int> MazeGenerator::getNeighbor(pair<int, int> node, int direction)
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

vector<pair<int, int>> MazeGenerator::getAllNeighbors(Maze *maze, pair<int, int> node)
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

void MazeGenerator::randomWalk(Maze *maze)
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
        // path.push_back({currentNode, directionTaken[currentNode]});
        included.insert(currentNode);

        neighbor = getNeighbor(currentNode, directionTaken[currentNode]);
        maze->addEdge(currentNode, neighbor);

        currentNode = neighbor;
    }

    // return path;
}

void MazeGenerator::generate(Maze *maze)
{
    included.erase(included.begin(), included.end());

    included.insert({0, 0});

    while (included.size() < maze->getRows() * maze->getColumns())
    {
        randomWalk(maze);
    }
}