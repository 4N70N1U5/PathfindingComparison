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

// int MazeSolver::heuristicWeights[] = {1, 5, 10, 25, 50, 75, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000};
// long long MazeSolver::bfsTime, MazeSolver::dfsTime, MazeSolver::dijkstraTime, MazeSolver::befsTime;
// long long MazeSolver::bfsCost, MazeSolver::dfsCost, MazeSolver::dijkstraCost, MazeSolver::befsCost;
// long long MazeSolver::bfsLength, MazeSolver::dfsLength, MazeSolver::dijkstraLength, MazeSolver::befsLength;
// unordered_map<int, int> MazeSolver::aStarTime, MazeSolver::aStarCost, MazeSolver::aStarLength;

int heuristic(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void MazeSolver::breadthFirstSearch(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "\nSolving maze using Breadth-First Search algorithm... " << flush;

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

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color::Cyan});
        }

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

                if (nodeColors != nullptr)
                {
                    nodeColors->push_back({neighbor.first, sf::Color::Blue});
                }
            }
        }

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(225, 225, 225)});
        }
    }

    list<pair<int, int>> path;
    long long totalCost = 0, pathLength = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        totalCost += maze->getEdgeWeight(parent[current], current);
        pathLength++;

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(0, 200, 0)});
        }

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    if (nodeColors != nullptr)
    {
        nodeColors->push_back({make_pair(0, 0), sf::Color(0, 200, 0)});
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    // bfsTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    // bfsCost = totalCost;
    // bfsLength = pathLength;

    // cout << "Done! (elapsed time: " << bfsTime / 1000000.0 << "s)\n";

    cout << "Done!\n";

    cout << "Breadth-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Breadth-First Search solve cost: " << totalCost << "\n";

    cout << "Breadth-First Search solve path length: " << pathLength << "\n";
}

void MazeSolver::depthFirstSearch(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "\nSolving maze using Depth-First Search algorithm... " << flush;

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

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color::Cyan});
        }

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

                if (nodeColors != nullptr)
                {
                    nodeColors->push_back({neighbor.first, sf::Color::Blue});
                }
            }
        }

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(225, 225, 225)});
        }
    }

    list<pair<int, int>> path;
    long long totalCost = 0, pathLength = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        totalCost += maze->getEdgeWeight(parent[current], current);
        pathLength++;

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(0, 200, 0)});
        }

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    if (nodeColors != nullptr)
    {
        nodeColors->push_back({make_pair(0, 0), sf::Color(0, 200, 0)});
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    // dfsTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    // dfsCost = totalCost;
    // dfsLength = pathLength;

    // cout << "Done! (elapsed time: " << dfsTime / 1000000.0 << "s)\n";

    cout << "Done!\n";

    cout << "Depth-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Depth-First Search solve cost: " << totalCost << "\n";

    cout << "Depth-First Search solve path length: " << pathLength << "\n";
}

void MazeSolver::dijkstra(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "\nSolving maze using Dijkstra's algorithm... " << flush;

    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> queue;
    unordered_map<pair<int, int>, long long, boost::hash<pair<int, int>>> costs;
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            costs[{i, j}] = INT_MAX;
        }
    }

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    costs[{0, 0}] = 0;
    queue.push({costs[{0, 0}], {0, 0}});

    while (!queue.empty())
    {
        pair<int, int> current = queue.top().second;
        queue.pop();

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color::Cyan});
        }

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            int weight = neighbor.second;

            if (costs[current] + weight < costs[neighbor.first])
            {
                costs[neighbor.first] = costs[current] + weight;
                parent[neighbor.first] = current;
                queue.push({costs[neighbor.first], neighbor.first});

                if (nodeColors != nullptr)
                {
                    nodeColors->push_back({neighbor.first, sf::Color::Blue});
                }
            }
        }

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(225, 225, 225)});
        }
    }

    list<pair<int, int>> path;
    long long pathLength = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        pathLength++;

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(0, 200, 0)});
        }

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    if (nodeColors != nullptr)
    {
        nodeColors->push_back({make_pair(0, 0), sf::Color(0, 200, 0)});
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    // dijkstraTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    // dijkstraCost = costs[TARGET_NODE];
    // dijkstraLength = pathLength;

    // cout << "Done! (elapsed time: " << dijkstraTime / 1000000.0 << "s)\n";

    cout << "Done!\n";

    cout << "Dijkstra's solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Dijkstra's solve cost: " << costs[TARGET_NODE] << "\n";

    cout << "Dijkstra's solve path length: " << pathLength << "\n";
}

void MazeSolver::bestFirstSearch(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "\nSolving maze using Best-First Search algorithm... " << flush;

    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> queue;
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

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color::Cyan});
        }

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

                if (nodeColors != nullptr)
                {
                    nodeColors->push_back({neighbor.first, sf::Color::Blue});
                }
            }
        }

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(225, 225, 225)});
        }
    }

    list<pair<int, int>> path;
    long long totalCost = 0, pathLength = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        totalCost += maze->getEdgeWeight(parent[current], current);
        pathLength++;

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(0, 200, 0)});
        }

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    if (nodeColors != nullptr)
    {
        nodeColors->push_back({make_pair(0, 0), sf::Color(0, 200, 0)});
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    // befsTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    // befsCost = totalCost;
    // befsLength = pathLength;

    // cout << "Done! (elapsed time: " << befsTime / 1000000.0 << "s)\n";

    cout << "Done!\n";

    cout << "Best-First Search solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "Best-First Search solve cost: " << totalCost << "\n";

    cout << "Best-First Search solve path length: " << pathLength << "\n";
}

void MazeSolver::aStar(Maze *maze, int heuristicWeight, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    cout << "\nSolving maze using A* algorithm with " << heuristicWeight << " heuristic weight... " << flush;

    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> queue;
    unordered_map<pair<int, int>, long long, boost::hash<pair<int, int>>> costs; // g(n)
    unordered_map<pair<int, int>, pair<int, int>, boost::hash<pair<int, int>>> parent;

    for (int i = 0; i < maze->getRows(); i++)
    {
        for (int j = 0; j < maze->getColumns(); j++)
        {
            costs[{i, j}] = INT_MAX;
        }
    }

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    costs[{0, 0}] = 0;
    queue.push({costs[{0, 0}] + heuristic({0, 0}, TARGET_NODE), {0, 0}});

    while (!queue.empty())
    {
        pair<int, int> current = queue.top().second;
        queue.pop();

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color::Cyan});
        }

        if (current == TARGET_NODE)
        {
            break;
        }

        for (auto neighbor : maze->getAdjacencyList(current))
        {
            int weight = neighbor.second;

            if (costs[current] + weight < costs[neighbor.first])
            {
                costs[neighbor.first] = costs[current] + weight;
                parent[neighbor.first] = current;
                queue.push({costs[neighbor.first] + heuristic(neighbor.first, TARGET_NODE) * heuristicWeight, neighbor.first});

                if (nodeColors != nullptr)
                {
                    nodeColors->push_back({neighbor.first, sf::Color::Blue});
                }
            }
        }

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(225, 225, 225)});
        }
    }

    list<pair<int, int>> path;
    long long pathLength = 0;

    pair<int, int> current = TARGET_NODE;

    while (current != make_pair(0, 0))
    {
        path.push_front(current);
        pathLength++;

        if (nodeColors != nullptr)
        {
            nodeColors->push_back({current, sf::Color(0, 200, 0)});
        }

        current = parent[current];
    }

    path.push_front(make_pair(0, 0));

    if (nodeColors != nullptr)
    {
        nodeColors->push_back({make_pair(0, 0), sf::Color(0, 200, 0)});
    }

    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

    // aStarTime[heuristicWeight] = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    // aStarCost[heuristicWeight] = costs[TARGET_NODE];
    // aStarLength[heuristicWeight] = pathLength;

    // cout << "Done! (elapsed time: " << aStarTime[heuristicWeight] / 1000000.0 << "s)\n";

    cout << "Done!\n";

    cout << "A* with " << heuristicWeight << " heuristic weight solve duration: "
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count()
         << " microseconds ("
         << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0
         << " seconds).\n";

    cout << "A* with " << heuristicWeight << " heuristic weight solve cost: " << costs[TARGET_NODE] << "\n";

    cout << "A* with " << heuristicWeight << " heuristic weight solve path length: " << pathLength << "\n";
}

void MazeSolver::aStarAll(Maze *maze, vector<pair<pair<int, int>, sf::Color>> *nodeColors)
{
    // int heuristicWeights[] = {1, 5, 10, 25, 50, 75, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};
    int heuristicWeights[] = {1, 5, 10, 25, 50, 75, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000};

    // unordered_map<int, int> aStarTimes, aStarCosts, aStarLengths;
    // unordered_map<int, vector<pair<pair<int, int>, sf::Color>> *> allNodeColors;

    for (auto heuristicWeight : heuristicWeights)
    {
        if (nodeColors != nullptr && heuristicWeight >= max(maze->getRows(), maze->getColumns()) && nodeColors->size() == 0)
        {
            MazeSolver::aStar(maze, heuristicWeight, nodeColors);
        }
        else
        {
            MazeSolver::aStar(maze, heuristicWeight);
        }
    }

    // if (nodeColors != nullptr)
    // {
    //     *nodeColors = *allNodeColors[heuristicWeights[12]];
    // }
}

// void MazeSolver::printResults()
// {
//     cout << "Breadth-First Search solve duration: "
//          << bfsTime
//          << " microseconds ("
//          << bfsTime / 1000000.0
//          << " seconds).\n";

//     cout << "Breadth-First Search solve cost: " << bfsCost << "\n";

//     cout << "Breadth-First Search solve path length: " << bfsLength << "\n";

//     cout << "\n";

//     cout << "Depth-First Search solve duration: "
//          << dfsTime
//          << " microseconds ("
//          << dfsTime / 1000000.0
//          << " seconds).\n";

//     cout << "Depth-First Search solve cost: " << dfsCost << "\n";

//     cout << "Depth-First Search solve path length: " << dfsLength << "\n";

//     cout << "\n";

//     cout << "Dijkstra's solve duration: "
//          << dijkstraTime
//          << " microseconds ("
//          << dijkstraTime / 1000000.0
//          << " seconds).\n";

//     cout << "Dijkstra's solve cost: " << dijkstraCost << "\n";

//     cout << "Dijkstra's solve path length: " << dijkstraLength << "\n";

//     cout << "\n";

//     cout << "Best-First Search solve duration: "
//          << befsTime
//          << " microseconds ("
//          << befsTime / 1000000.0
//          << " seconds).\n";

//     cout << "Best-First Search solve cost: " << befsCost << "\n";

//     cout << "Best-First Search solve path length: " << befsLength << "\n";

//     for (auto heuristicWeight : heuristicWeights)
//     {
//         cout << "\n";

//         cout << "A* with " << heuristicWeight << " heuristic weight solve duration: "
//              << aStarTime[heuristicWeight]
//              << " microseconds ("
//              << aStarTime[heuristicWeight] / 1000000.0
//              << " seconds).\n";

//         cout << "A* with " << heuristicWeight << " heuristic weight solve cost: " << aStarCost[heuristicWeight] << "\n";

//         cout << "A* with " << heuristicWeight << " heuristic weight solve path length: " << aStarLength[heuristicWeight] << "\n";
//     }
// }
