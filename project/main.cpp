#include "include/Maze.hpp"
#include "include/MazeGenerator.hpp"

#include <iostream>
#include <string>
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

int main(int argc, char *argv[])
{
    if (!validateInput(argc, argv))
    {
        return 0;
    }

    Maze *maze;

    switch (argc)
    {
    case 4:
    {
        maze = new Maze(stoi(argv[1]), stoi(argv[2]));
        MazeGenerator generator(time(0));

        generator.generate(maze, stoi(argv[3]));

        cout << "Will generate maze with " << argv[1] << " rows and " << argv[2] << " columns with random seed\n";
        break;
    }

    case 5:
    {
        maze = new Maze(stoi(argv[1]), stoi(argv[2]));
        MazeGenerator generator(stol(argv[4]));

        generator.generate(maze, stoi(argv[3]));

        cout << "Will generate maze with " << argv[1] << " rows and " << argv[2] << " columns with seed " << argv[4] << "\n";
        break;
    }
    }

    maze->print();

    sf::RenderWindow window(sf::VideoMode(stoi(argv[1]) * 10, stoi(argv[2]) * 10), "Maze", sf::Style::Titlebar | sf::Style::Close);

    bool exitProgram = false;

    while (!exitProgram && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        maze->draw(&window);
    }

    return 0;
}
