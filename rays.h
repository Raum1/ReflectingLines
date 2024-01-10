#pragma once
#include <SFML/Graphics.hpp>
#include "wall.h"
#include <vector>

class rays : public sf::Drawable {

public:
	sf::VertexArray raysSource;
	sf::Color color;

	rays(sf::Vector2f pos, int numOfRays, sf::Color colour);

private:
	sf::Vector2f calc_hit(sf::Vector2f& lineBegPos, sf::Vector2f& lineEndPos, wall& wall);
	float get_distance(sf::Vector2f pos1, sf::Vector2f pos2);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	sf::Vector2f closest_hit(std::vector<wall*> walls, sf::Vector2f& lineBegPos, sf::Vector2f& lineEndPos);
	bool is_on_segment(sf::Vector2f& beg, sf::Vector2f& end, sf::Vector2f& point);

};