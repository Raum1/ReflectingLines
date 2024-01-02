#include <iostream>
#include <SFML/Graphics.hpp>
#include "wall.h"
#include "rays.h"
#include <vector>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    wall wall1(sf::Vector2f(800, 500), sf::Vector2f(900, 700));
    wall wall2(sf::Vector2f(500, 500), sf::Vector2f(300, 600));
    wall wall3(sf::Vector2f(1000, 900), sf::Vector2f(500, 600));
    wall wall4(sf::Vector2f(200, 650), sf::Vector2f(450, 300));
    wall wall5(sf::Vector2f(1000, 650), sf::Vector2f(1500, 350));
    wall wall6(sf::Vector2f(1600, 200), sf::Vector2f(1700, 650));
    wall wall7(sf::Vector2f(1300, 750), sf::Vector2f(1500, 850));

    sf::Color raysColor = sf::Color(255, 255, 0);

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
        rays lines(pos, 256, raysColor);
        window.clear();
        window.draw(lines);
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);
        window.draw(wall5);
        window.draw(wall6);
        window.draw(wall7);
        window.display();
    }

    return 0;
}


