#include "include/Maze.hpp"
#include "include/MazeGenerator.hpp"

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    Maze *maze;

    switch (argc)
    {
    case 3:
    {
        maze = new Maze(stoi(argv[1]), stoi(argv[2]));
        MazeGenerator generator(time(0));

        generator.generate(maze);

        cout << "Will generate maze with " << argv[1] << " rows and " << argv[2] << " columns with random seed\n";
        break;
    }

    case 4:
    {
        maze = new Maze(stoi(argv[1]), stoi(argv[2]));
        MazeGenerator generator(stol(argv[3]));

        generator.generate(maze);

        cout << "Will generate maze with " << argv[1] << " rows and " << argv[2] << " columns with seed " << argv[3] << "\n";
        break;
    }

    default:
        cout << "Incorrect argument list!\n";
        return 0;
    }

    maze->print();

    return 0;
}
