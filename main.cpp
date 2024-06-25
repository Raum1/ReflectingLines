#include <iostream>
#include <SFML/Graphics.hpp>
#include "rays.h"
#include "wall.h"
#include <vector>
#include "rando.h"
#include <ctime>

/// @brief Generate lines that act like walls
/// @param isRandom Is walls positions should be random
wall *generateWalls(bool isRandom)
{
    wall *arr = new wall[7];

    if (isRandom)
    {
        for (int i = 0; i < 7; i++)
        {
            arr[i] = wall(sf::Vector2f(rando::getRandomNumber(300, 1500), rando::getRandomNumber(300, 900)),
                          sf::Vector2f(rando::getRandomNumber(300, 1500), rando::getRandomNumber(300, 900)));
        }
    }
    else
    {
        arr[0] = wall(sf::Vector2f(800, 500),
                      sf::Vector2f(900, 700));
        arr[1] = wall(sf::Vector2f(500, 500),
                      sf::Vector2f(300, 600));
        arr[2] = wall(sf::Vector2f(1000, 900),
                      sf::Vector2f(500, 600));
        arr[3] = wall(sf::Vector2f(200, 650),
                      sf::Vector2f(450, 300));
        arr[4] = wall(sf::Vector2f(1000, 650),
                      sf::Vector2f(1500, 350));
        arr[5] = wall(sf::Vector2f(1600, 200),
                      sf::Vector2f(1700, 650));
        arr[6] = wall(sf::Vector2f(1300, 750),
                      sf::Vector2f(1500, 850));
    }
    return arr;
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    auto walls = generateWalls(true);

    sf::Color raysColor = sf::Color(255, 255, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        rays lines(pos, 256, raysColor);
        window.clear();
        window.draw(lines);
        for (int i = 0; i < 7; i++)
        {
            window.draw(walls[i]);
        }
        window.display();
    }

    return 0;
}
