#include "wall.h"

std::vector<wall *> wall::objList;

wall::wall()
{
    objList.push_back(this);
}

wall::wall(sf::Vector2f begPos, sf::Vector2f endPos)
{
    if (count(objList.begin(), objList.end(), this) == 0)
        objList.push_back(this);
    m = (endPos.y - begPos.y) / (endPos.x - begPos.x);
    b = begPos.y - m * begPos.x;
    this->begPos = begPos;
    this->endPos = endPos;
}

void wall::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = begPos;
    lines[1].position = endPos;
    target.draw(lines, states);
}

std::vector<wall *> wall::get_all_objects() { return wall::objList; }