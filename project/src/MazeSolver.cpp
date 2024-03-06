#include "../include/Maze.hpp"
#include "../include/MazeSolver.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <list>
#include <boost/functional/hash.hpp>

#define TARGET_NODE make_pair(maze->getRows() - 1, maze->getColumns() - 1)

void MazeSolver::bfsSolve(Maze *maze)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    cout << "Solving maze using BFS...\n";

    queue<pair<int, int>> queue;
    unordered_map<pair<int, int>, bool, boost::hash<pair<int, int>>> visited;
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    queue.push({0, 0});
    visited[{0, 0}] = true;

    while (!queue.empty())
    {
        pair<int, int> current = queue.front();
        queue.pop();

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            if (!visited[neighbor.first])
            {
                queue.push(neighbor.first);
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
            }
        }
    }

    list<pair<int, int>> path;
    int total_cost = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        total_cost += maze->getEdgeWeight(parent[current], current);

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    cout << "BFS solve duration: "
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    // cout << "BFS solve path: ";
    // for (auto node : path)
    // {
    //     cout << "(" << node.first << ", " << node.second << ") ";
    // }
    // cout << "\n";

    cout << "BFS solve cost: " << total_cost << "\n";
}

void MazeSolver::dfsSolve(Maze *maze)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    cout << "Solving maze using DFS...\n";

    stack<pair<int, int>> stack;
    unordered_map<pair<int, int>, bool, boost::hash<pair<int, int>>> visited;
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    stack.push({0, 0});
    visited[{0, 0}] = true;

    while (!stack.empty())
    {
        pair<int, int> current = stack.top();
        stack.pop();

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            if (!visited[neighbor.first])
            {
                stack.push(neighbor.first);
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
            }
        }
    }

    list<pair<int, int>> path;
    int total_cost = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        total_cost += maze->getEdgeWeight(parent[current], current);

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    cout << "DFS solve duration: "
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    // cout << "DFS solve path: ";
    // for (auto node : path)
    // {
    //     cout << "(" << node.first << ", " << node.second << ") ";
    // }
    // cout << "\n";

    cout << "DFS solve cost: " << total_cost << "\n";
}
