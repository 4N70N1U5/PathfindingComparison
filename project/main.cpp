#include "include/Maze.hpp"
#include "include/MazeGenerator.hpp"
#include "include/MazeSolver.hpp"
#include "include/SolveVisualizer.hpp"

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

bool validateInput(int argc, char *argv[])
{
    if (argc != 5 && argc != 6)
    {
        cout << "Incorrect argument list!\n";
        return false;
    }

    try
    {
        stoi(argv[1]);
        stoi(argv[2]);
        stoi(argv[3]);
        stoi(argv[4]);
        if (argc == 6)
        {
            stol(argv[5]);
        }
    }
    catch (const exception &e)
    {
        cout << "Incorrect argument types!\n";
        return false;
    }

    if (stoi(argv[1]) < 10 || stoi(argv[2]) < 10)
    {
        cout << "Minimum maze size is 10x10!\n";
        return false;
    }

    if (stoi(argv[3]) != 0 && stoi(argv[3]) != 1)
    {
        cout << "The value for weighted graph must be either 0 (unweighted graph) or 1 (weighted graph)!\n";
        return false;
    }

    if (stoi(argv[4]) != 0 && stoi(argv[4]) != 1)
    {
        cout << "The value for multiple paths must be either 0 (do not create multiple paths) or 1 (create multiple paths)!\n";
        return false;
    }

    return true;
}

void generateMaze(Maze *maze, int argc, char *argv[])
{
    switch (argc)
    {
    case 5:
    {
        MazeGenerator::generate(maze, stoi(argv[3]), stoi(argv[4]));
        break;
    }

    case 6:
    {
        MazeGenerator::generate(maze, stoi(argv[3]), stoi(argv[4]), stol(argv[5]));
        break;
    }
    }

    cout << "\n";
}

void clearConsole()
{
#if defined _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printMenuOptions()
{
    cout << "1: Print solve results\n";
    cout << "2: Draw maze in new window\n";
    cout << "3: Visualize BFS solve in new window\n";
    cout << "4: Visualize DFS solve in new window\n";
    cout << "5: Visualize Dijkstra solve in new window\n";
    cout << "6: Visualize BeFS solve in new window\n";
    cout << "7: Visualize A* solve in new window\n";
    cout << "0: Exit\n";

    cout << "\nChoose an option: ";
}

int main(int argc, char *argv[])
{
    if (!validateInput(argc, argv))
    {
        return 0;
    }

    Maze *maze = new Maze(stoi(argv[1]), stoi(argv[2]));

    generateMaze(maze, argc, argv);

    MazeSolver::breadthFirstSearch(maze);
    MazeSolver::depthFirstSearch(maze);
    MazeSolver::dijkstra(maze);
    MazeSolver::bestFirstSearch(maze);
    MazeSolver::aStarAll(maze);

    cout << "\nPress enter to continue...";
    cin.get();

    bool exitProgram = false;
    string input;

    sf::RenderWindow window;
    window.setKeyRepeatEnabled(false);

    while (!exitProgram)
    {
        clearConsole();
        printMenuOptions();

        cin >> input;
        cin.get();

        clearConsole();

        if (input == "1")
        {
            MazeSolver::printResults();

            cout << "\nPress enter to continue...";
            cin.get();
        }
        else if (input == "2")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {
                cout << "Close window to continue...\n";

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "Maze", sf::Style::Titlebar | sf::Style::Close);

                while (window.isOpen())
                {
                    sf::Event event;

                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                    }

                    window.clear(sf::Color::White);

                    maze->draw(&window);

                    window.display();
                }
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "3")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "BFS Solve", sf::Style::Titlebar | sf::Style::Close);

                SolveVisualizer::visualizeBFS(maze, &window);
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "4")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "DFS Solve", sf::Style::Titlebar | sf::Style::Close);

                SolveVisualizer::visualizeDFS(maze, &window);
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "5")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "Dijkstra Solve", sf::Style::Titlebar | sf::Style::Close);

                SolveVisualizer::visualizeDijkstra(maze, &window);
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "6")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "BeFS Solve", sf::Style::Titlebar | sf::Style::Close);

                SolveVisualizer::visualizeBeFS(maze, &window);
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "7")
        {
            if (stoi(argv[1]) <= 100 && stoi(argv[2]) <= 100)
            {
                cout << "Enter heuristic weight: ";

                string heuristicWeightInput;
                cin >> heuristicWeightInput;
                cin.get();

                try
                {
                    stoi(heuristicWeightInput);
                }
                catch (const exception &e)
                {
                    cout << "Invalid heuristic weight! Try again.\n";

                    cout << "\nPress enter to continue...";
                    cin.get();

                    continue;
                }

                if (stoi(heuristicWeightInput) < 0)
                {
                    cout << "Heuristic weight must be non-negative! Try again.\n";

                    cout << "\nPress enter to continue...";
                    cin.get();

                    continue;
                }

                window.create(sf::VideoMode((stoi(argv[2]) + 2) * 10, (stoi(argv[1]) + 2) * 10), "A* Solve", sf::Style::Titlebar | sf::Style::Close);

                SolveVisualizer::visualizeAStar(maze, stoi(heuristicWeightInput), &window);
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";

                cout << "\nPress enter to continue...";
                cin.get();
            }
        }
        else if (input == "0")
        {
            exitProgram = true;
        }
        else
        {
            cout << "Invalid option! Try again.\n";

            cout << "\nPress enter to continue...";
            cin.get();
        }
    }

    clearConsole();
    return 0;
}
