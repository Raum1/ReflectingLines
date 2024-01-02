#include <iostream>
#include <SFML/Graphics.hpp>
#include "wall.h"
#include "rays.h"
#include <vector>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    wall:wall wall1(sf::Vector2f(800, 500), sf::Vector2f(900, 700));

    sf::Color raysColor = sf::Color(100, 100, 100);

    //sf::Vector2f pos(sf::Vector2f(window.getSize().x / 2 - 99.5f, window.getSize().y / 2));
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        rays lines(pos, 1600, raysColor);
        window.clear();
        window.draw(lines);
        window.draw(wall1);
        window.display();
    }

    return 0;
}


