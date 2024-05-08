#include "include/Maze.hpp"
#include "include/MazeGenerator.hpp"
#include "include/MazeSolver.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

bool validateInput(int argc, char *argv[])
{
    if (argc != 4 && argc != 5)
    {
        cout << "Incorrect argument list!\n";
        return false;
    }

    if (stoi(argv[1]) < 10 || stoi(argv[2]) < 10)
    {
        cout << "Minimum maze size is 10x10!\n";
        return false;
    }

    if (stoi(argv[3]) != 0 && stoi(argv[3]) != 1)
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
    case 4:
    {
        MazeGenerator generator(time(0));
        generator.generate(maze, stoi(argv[3]));

        // this_thread::sleep_for(chrono::seconds(2));

        break;
    }

    case 5:
    {
        MazeGenerator generator(stol(argv[4]));
        generator.generate(maze, stoi(argv[3]));

        // this_thread::sleep_for(chrono::seconds(2));

        break;
    }
    }
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
    MazeSolver::aStar(maze);

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
            if (stoi(argv[1]) <= 50 && stoi(argv[2]) <= 50)
            {
                cout << "Close window to continue...\n";

                window.create(sf::VideoMode(stoi(argv[1]) * 10, stoi(argv[2]) * 10), "Maze", sf::Style::Titlebar | sf::Style::Close);

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

                    maze->draw(&window);
                }
            }
            else
            {
                cout << "Maze is too large to be displayed!\n";
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        else if (input == "0")
        {
            exitProgram = true;

            cout << "Program will exit...\n";
            this_thread::sleep_for(chrono::seconds(2));
        }
        else
        {
            cout << "Invalid option! Try again.\n";
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    clearConsole();
    return 0;
}
