#include <SFML/Graphics.hpp>
#include "rays.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "rando.h"

// Pi * 2
const float TAU = 6.2831f;

float rays::get_distance(sf::Vector2f pos1, sf::Vector2f pos2)
{
    return std::sqrt(std::pow((pos2.y - pos1.y), 2) + std::pow((pos2.x - pos1.x), 2));
}

bool rays::is_on_segment(sf::Vector2f &p, sf::Vector2f &q, sf::Vector2f &r)
{
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

rays::rays(sf::Vector2f pos, int numOfRays, sf::Color color)
{
    rays::color = color;

    float *initX = &pos.x;
    float *initY = &pos.y;

    float magnitute = std::numeric_limits<float>::max();

    float angleStep = TAU / numOfRays;
    float currentAngle = 0.f;
    sf::Vector2f endPos = sf::Vector2f(*initX + 20000, *initY);
    float xPrime = get_distance(pos, closest_hit(wall::get_all_objects(), pos, endPos));
    ;
    float yPrime = 0;

    sf::VertexArray lines(sf::LinesStrip, numOfRays * 2);

    for (int i = 0; i < numOfRays * 2; i += 2)
    {
        endPos = sf::Vector2f(
            *initX + std::cos(currentAngle + TAU / numOfRays) * 20000,
            *initY + std::sin(currentAngle + TAU / numOfRays) * 20000);
        magnitute = get_distance(pos, closest_hit(wall::get_all_objects(), pos, endPos));
        currentAngle += angleStep;

        xPrime = magnitute * std::cos(currentAngle);
        yPrime = magnitute * std::sin(currentAngle);

        lines[i].position = pos;
        lines[i].color = color;
        lines[i + 1].position = sf::Vector2f(*initX + xPrime, *initY + yPrime);
        lines[i + 1].color = color;
    }

    rays::raysSource = lines;
}

void rays::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rays::raysSource, states);
}

sf::Vector2f rays::calc_hit(sf::Vector2f &lineBegPos, sf::Vector2f &lineEndPos, wall &wall)
{
    float lineM = 10000;
    if (lineEndPos.x - lineBegPos.x != 0)
    {
        lineM = (lineEndPos.y - lineBegPos.y) / (lineEndPos.x - lineBegPos.x);
    }
    float lineB = (lineBegPos.y) - (lineM * lineBegPos.x);

    float x = (lineB - wall.b) / (wall.m - lineM);
    float y = x * wall.m + wall.b;
    sf::Vector2f hitPoint = sf::Vector2f(x, y);

    if ((std::roundf(x) >= std::min(wall.begPos.x, wall.endPos.x) && std::roundf(x) <= std::max(wall.begPos.x, wall.endPos.x)) &&
        (y >= std::min(wall.begPos.y, wall.endPos.y) && y <= std::max(wall.begPos.y, wall.endPos.y)))
    {
        if (is_on_segment(lineBegPos, hitPoint, lineEndPos))
        {
            return hitPoint;
        }
        else
        {
            return sf::Vector2f(50000, 50000);
        }
    }
    else
    {
        return sf::Vector2f(50000, 50000);
    }
}

sf::Vector2f rays::closest_hit(std::vector<wall *> walls, sf::Vector2f &lineBegPos, sf::Vector2f &lineEndPos)
{
    sf::Vector2f hit;
    float distance = std::numeric_limits<float>::max();
    float tempD = 0;
    for (int i = 0; i < walls.size(); i++)
    {
        sf::Vector2f currentHit =
            rays::calc_hit(lineBegPos, lineEndPos, *walls[i]);
        tempD = get_distance(lineBegPos, currentHit);
        if (distance > tempD)
        {
            distance = tempD;
            hit = currentHit;
        }
    }
    return hit;
}
