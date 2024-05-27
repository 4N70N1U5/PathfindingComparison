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
    cout << "1: Print results\n";
    cout << "2: Visualize maze in new window\n";
    cout << "3: Visualize BFS solution in new window\n";
    cout << "4: Visualize DFS solution in new window\n";
    cout << "5: Visualize Dijkstra solution in new window\n";
    cout << "6: Visualize BeFS solution in new window\n";
    cout << "7: Visualize A* solution in new window\n";
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                cout << "Close window to continue...\n";

                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "Maze", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                while (window.isOpen())
                {
                    sf::Event event;

                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                        }

                        if (event.type == sf::Event::Resized)
                        {
                            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                            window.setView(sf::View(visibleArea));
                        }

                        if (event.type == sf::Event::KeyPressed)
                        {
                            if (event.key.code == sf::Keyboard::Escape)
                            {
                                window.close();
                            }
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "BFS Solution", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                SolveVisualizer::visualizeBFS(&window, maze);
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "DFS Solution", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                SolveVisualizer::visualizeDFS(&window, maze);
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "Dijkstra Solution", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                SolveVisualizer::visualizeDijkstra(&window, maze);
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "BeFS Solution", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                SolveVisualizer::visualizeBeFS(&window, maze);
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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
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

                sf::RenderWindow window(sf::VideoMode(480 * (stod(argv[2]) / stod(argv[1])), 480), "A* Solution", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
                window.setActive(true);
                window.setKeyRepeatEnabled(false);

                SolveVisualizer::visualizeAStar(&window, maze, stoi(heuristicWeightInput));
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
