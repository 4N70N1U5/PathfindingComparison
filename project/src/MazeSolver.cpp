#include "../include/Maze.hpp"
#include "../include/MazeSolver.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <boost/functional/hash.hpp>

#define TARGET_NODE make_pair(maze->getRows() - 1, maze->getColumns() - 1)

int heuristic(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void MazeSolver::breadthFirstSearch(Maze *maze)
{
    cout << "Solving maze using Breadth-First Search algorithm...\n";

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

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    visited[{0, 0}] = true;
    queue.push({0, 0});

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
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
                queue.push(neighbor.first);
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

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    cout << "Breadth-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    // cout << "Breadth-First Search solve path: ";
    // for (auto node : path)
    // {
    //     cout << "(" << node.first << ", " << node.second << ") ";
    // }
    // cout << "\n";

    cout << "Breadth-First Search solve cost: " << total_cost << "\n";
}

void MazeSolver::depthFirstSearch(Maze *maze)
{
    cout << "Solving maze using Depth-First Search algorithm...\n";

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

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    visited[{0, 0}] = true;
    stack.push({0, 0});

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
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
                stack.push(neighbor.first);
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

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    cout << "Depth-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    // cout << "Depth-First Search solve path: ";
    // for (auto node : path)
    // {
    //     cout << "(" << node.first << ", " << node.second << ") ";
    // }
    // cout << "\n";

    cout << "Depth-First Search solve cost: " << total_cost << "\n";
}

void MazeSolver::dijkstra(Maze *maze)
{
    cout << "Solving maze using Dijkstra's algorithm...\n";

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> queue;
    unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> distances;
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            distances[{i, j}] = INT_MAX;
        }
    }

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    distances[{0, 0}] = 0;
    queue.push({0, {0, 0}});

    while (!queue.empty())
    {
        pair<int, int> current = queue.top().second;
        queue.pop();

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            int weight = neighbor.second;

            if (distances[current] + weight < distances[neighbor.first])
            {
                distances[neighbor.first] = distances[current] + weight;
                parent[neighbor.first] = current;
                queue.push({distances[neighbor.first], neighbor.first});
            }
        }
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    cout << "Dijkstra's solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Dijkstra's solve cost: " << distances[TARGET_NODE] << "\n";
}

void MazeSolver::bestFirstSearch(Maze *maze)
{
    cout << "Solving maze using Best-First Search algorithm...\n";

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> queue;
    unordered_map<pair<int, int>, bool, boost::hash<pair<int, int>>> visited;
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    visited[{0, 0}] = true;
    queue.push({heuristic({0, 0}, TARGET_NODE), {0, 0}});

    while (!queue.empty())
    {
        pair<int, int> current = queue.top().second;
        queue.pop();

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            if (!visited[neighbor.first])
            {
                visited[neighbor.first] = true;
                parent[neighbor.first] = current;
                queue.push({heuristic(neighbor.first, TARGET_NODE), neighbor.first});
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

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    cout << "Best-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Best-First Search solve cost: " << total_cost << "\n";
}

void MazeSolver::aStar(Maze *maze)
{
    cout << "Solving maze using A* algorithm...\n";

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> queue;
    unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> distances; // g(n)
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            distances[{i, j}] = INT_MAX;
        }
    }

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    distances[{0, 0}] = 0;
    queue.push({distances[{0, 0}] + heuristic({0, 0}, TARGET_NODE), {0, 0}});

    while (!queue.empty())
    {
        pair<int, int> current = queue.top().second;
        queue.pop();

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            int weight = neighbor.second;

            if (distances[current] + weight < distances[neighbor.first])
            {
                distances[neighbor.first] = distances[current] + weight;
                parent[neighbor.first] = current;
                queue.push({distances[neighbor.first] + heuristic(neighbor.first, TARGET_NODE), neighbor.first});
            }
        }
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    cout << "A* solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "A* solve cost: " << distances[TARGET_NODE] << "\n";
}
