#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

class wall : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    float m, b;
    static std::vector<wall*> objList;
    sf::Vector2f begPos;
    sf::Vector2f endPos;
    wall(sf::Vector2f begPos, sf::Vector2f endPos);
    static std::vector<wall*> get_all_objects();
};