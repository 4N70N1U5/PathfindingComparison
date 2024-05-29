#include "include/Maze.hpp"
#include "include/MazeGenerator.hpp"
#include "include/MazeSolver.hpp"
#include "include/SolveVisualizer.hpp"
#include "include/Button.hpp"

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#define ROWS stoi(argv[1])
#define COLUMNS stoi(argv[2])
#define WEIGHTED stoi(argv[3])
#define MULTIPLE_PATHS stoi(argv[4])
#define SEED stol(argv[5])

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

    if (ROWS < 10 || COLUMNS < 10)
    {
        cout << "Minimum maze size is 10x10!\n";
        return false;
    }

    if (WEIGHTED != 0 && WEIGHTED != 1)
    {
        cout << "The value for weighted graph must be either 0 (unweighted graph) or 1 (weighted graph)!\n";
        return false;
    }

    if (MULTIPLE_PATHS != 0 && MULTIPLE_PATHS != 1)
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
        MazeGenerator::generate(maze, WEIGHTED, MULTIPLE_PATHS);
        break;
    }

    case 6:
    {
        MazeGenerator::generate(maze, WEIGHTED, MULTIPLE_PATHS, SEED);
        break;
    }
    }

    cout << "\n\n";
}

int main(int argc, char *argv[])
{
    if (!validateInput(argc, argv))
    {
        return 0;
    }

    Maze *maze = new Maze(ROWS, COLUMNS);
    vector<pair<pair<int, int>, sf::Color>> bfsNodeColors, dfsNodeColors, dijkstraNodeColors, befsNodeColors, aStarNodeColors;

    generateMaze(maze, argc, argv);

    if (ROWS <= 50 && COLUMNS <= 50)
    {
        MazeSolver::breadthFirstSearch(maze, &bfsNodeColors);
        MazeSolver::depthFirstSearch(maze, &dfsNodeColors);
        MazeSolver::dijkstra(maze, &dijkstraNodeColors);
        MazeSolver::bestFirstSearch(maze, &befsNodeColors);
        MazeSolver::aStarAll(maze, &aStarNodeColors);

        cout << "\n\n\nWindow will now open. Close window to exit program...\n";

        int windowWidth, windowHeight;

        if (640 * (stod(argv[2]) / stod(argv[1])) >= 640)
        {
            windowWidth = 640 * (stod(argv[2]) / stod(argv[1]));
            windowHeight = 640;
        }
        else
        {
            windowWidth = 640;
            windowHeight = 640 * (stod(argv[1]) / stod(argv[2]));
        }

        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "PathfindingComparison", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
        window.setKeyRepeatEnabled(false);
        window.setActive(true);

        enum WindowStates
        {
            MENU,
            MAZE,
            BFS,
            DFS,
            DIJKSTRA,
            BEFS,
            ASTAR
        } windowState = MENU;

        sf::Font font;
        font.loadFromFile("../fonts/NotoSansDisplay-Medium.ttf");

        sf::Clock clock;
        int steps = 0, delay = 250;

        bool showWeights = false;

        while (window.isOpen())
        {
            Button mazeButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 15), "Visualize Maze Layout (1)");
            Button bfsButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 80), "Visualize BFS Solution (2)");
            Button dfsButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 145), "Visualize DFS Solution (3)");
            Button dijkstraButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 210), "Visualize Dijkstra Solution (4)");
            Button befsButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 275), "Visualize Best-First Search Solution (5)");
            Button aStarButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 340), "Visualize A* Solution (6)");
            Button quitButton(sf::Vector2f(window.getSize().x - 30, 45), sf::Vector2f(15, 405), "Quit", sf::Color(225, 0, 0));
            Button backButton(sf::Vector2f(70, 30), sf::Vector2f(10, 10), "Back", sf::Color(225, 0, 0));
            Button weightsButton(sf::Vector2f(70, 30), sf::Vector2f(window.getSize().x - 80, 10), "Weights", showWeights ? sf::Color(0, 200, 0) : sf::Color(225, 225, 225));

            Button menuButtons[] = {mazeButton, bfsButton, dfsButton, dijkstraButton, befsButton, aStarButton, quitButton};
            Button visualizerButtons[] = {backButton, weightsButton};

            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::Resized)
                {
                    if (event.size.width < 640)
                    {
                        window.setSize(sf::Vector2u(640, window.getSize().y));
                    }

                    if (event.size.height < 640)
                    {
                        window.setSize(sf::Vector2u(window.getSize().x, 640));
                    }

                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        if (windowState == MENU)
                        {
                            window.close();
                        }
                        else
                        {
                            windowState = MENU;
                        }
                    }

                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        windowState = MAZE;
                    }

                    if (event.key.code == sf::Keyboard::Num2)
                    {
                        windowState = BFS;
                        steps = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num3)
                    {
                        windowState = DFS;
                        steps = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num4)
                    {
                        windowState = DIJKSTRA;
                        steps = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num5)
                    {
                        windowState = BEFS;
                        steps = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num6)
                    {
                        windowState = ASTAR;
                        steps = 0;
                    }

                    if (event.key.code == sf::Keyboard::W)
                    {
                        showWeights = !showWeights;
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (windowState == MENU)
                    {
                        if (mazeButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = MAZE;
                        }

                        if (bfsButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = BFS;
                            steps = 0;
                        }

                        if (dfsButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = DFS;
                            steps = 0;
                        }

                        if (dijkstraButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = DIJKSTRA;
                            steps = 0;
                        }

                        if (befsButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = BEFS;
                            steps = 0;
                        }

                        if (aStarButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = ASTAR;
                            steps = 0;
                        }

                        if (quitButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            window.close();
                        }
                    }
                    else
                    {
                        if (backButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            windowState = MENU;
                        }

                        if (weightsButton.isHovered(sf::Mouse::getPosition(window)))
                        {
                            showWeights = !showWeights;
                        }
                    }
                }
            }

            if (windowState != MENU && windowState != MAZE)
            {
                if (steps < INT_MAX && clock.getElapsedTime().asMilliseconds() >= delay)
                {
                    steps++;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        steps += 5;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        steps += 25;
                    }

                    clock.restart();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    steps = INT_MAX;
                }
            }

            window.clear(sf::Color::White);

            if (windowState == MENU)
            {
                for (Button button : menuButtons)
                {
                    if (button.isHovered(sf::Mouse::getPosition(window)))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            button.draw(&window, sf::Color(70, 70, 70, 0));
                        }
                        else
                        {
                            button.draw(&window, sf::Color(30, 30, 30, 0));
                        }
                    }
                    else
                    {
                        button.draw(&window);
                    }
                }
            }
            else
            {
                sf::RenderTexture mazeRenderArea;
                mazeRenderArea.create(window.getSize().x - 120, window.getSize().y - 120);

                mazeRenderArea.clear(sf::Color::White);

                sf::Text title;
                title.setFont(font);
                title.setCharacterSize(20);
                title.setFillColor(sf::Color::Black);

                switch (windowState)
                {
                case MENU:
                {
                    break;
                }

                case MAZE:
                {
                    maze->draw(&mazeRenderArea, showWeights);
                    title.setString("Maze layout visualization");

                    break;
                }

                case BFS:
                {
                    SolveVisualizer::drawVisualization(&mazeRenderArea, maze, showWeights, &bfsNodeColors, steps);
                    title.setString("BFS solution visualization");

                    break;
                }

                case DFS:
                {
                    SolveVisualizer::drawVisualization(&mazeRenderArea, maze, showWeights, &dfsNodeColors, steps);
                    title.setString("DFS solution visualization");

                    break;
                }

                case DIJKSTRA:
                {
                    SolveVisualizer::drawVisualization(&mazeRenderArea, maze, showWeights, &dijkstraNodeColors, steps);
                    title.setString("Dijkstra solution visualization");

                    break;
                }

                case BEFS:
                {
                    SolveVisualizer::drawVisualization(&mazeRenderArea, maze, showWeights, &befsNodeColors, steps);
                    title.setString("BeFS solution visualization");

                    break;
                }

                case ASTAR:
                {
                    SolveVisualizer::drawVisualization(&mazeRenderArea, maze, showWeights, &aStarNodeColors, steps);
                    title.setString("A* solution visualization");

                    break;
                }
                }

                mazeRenderArea.display();

                sf::Sprite mazeSprite(mazeRenderArea.getTexture());

                mazeSprite.setPosition(60, 60);

                window.draw(mazeSprite);

                for (Button button : visualizerButtons)
                {
                    if (button.isHovered(sf::Mouse::getPosition(window)))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            button.draw(&window, sf::Color(70, 70, 70, 0));
                        }
                        else
                        {
                            button.draw(&window, sf::Color(30, 30, 30, 0));
                        }
                    }
                    else
                    {
                        button.draw(&window);
                    }
                }

                title.setOrigin(sf::Vector2f(title.getLocalBounds().width / 2, 0));
                title.setPosition(sf::Vector2f(window.getSize().x / 2, 15));
                window.draw(title);

                if (windowState != MAZE)
                {
                    sf::Text instructions;
                    instructions.setFont(font);
                    instructions.setCharacterSize(15);
                    instructions.setLineSpacing(0.75);
                    instructions.setFillColor(sf::Color::Black);
                    instructions.setString("Left Control - hold for 5x speed\nLeft Shift - hold for 25x speed\nSpace - skip to end");
                    instructions.setOrigin(sf::Vector2f(instructions.getLocalBounds().width / 2, 0));
                    instructions.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - instructions.getLocalBounds().height - 15));
                    window.draw(instructions);
                }
            }

            window.display();
        }

        cout << "App will now exit...\n";
    }
    else
    {
        MazeSolver::breadthFirstSearch(maze);
        MazeSolver::depthFirstSearch(maze);
        MazeSolver::dijkstra(maze);
        MazeSolver::bestFirstSearch(maze);
        MazeSolver::aStarAll(maze);

        cout << "\n\n\nApp can only run in command-line-only mode because generated maze is too large to be displayed!\n";
        cout << "App will now exit...\n";
    }

    return 0;
}
