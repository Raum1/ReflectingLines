#include "wall.h"

std::vector<wall*> wall::objList;

wall::wall(sf::Vector2f begPos1, sf::Vector2f endPos1){
    objList.push_back(this);
    begPos = begPos1;
    endPos = endPos1;
}

void wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = begPos;
    lines[1].position = endPos;
    target.draw(lines, states);
}

std::vector<wall*> wall::get_all_objects() { return wall::objList; }