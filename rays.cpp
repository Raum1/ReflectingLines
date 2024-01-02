#include<SFML/Graphics.hpp>
#include"rays.h"
#include<iostream>
#include<algorithm>

const float TAU = 6.2831f;

float rays::get_distance(sf::Vector2f pos1, sf::Vector2f pos2) {
    return std::sqrtf(std::powf((pos2.y - pos1.y), 2) + std::powf((pos2.x - pos1.x), 2));
}

bool rays::is_on_segment(sf::Vector2f& p, sf::Vector2f& q, sf::Vector2f& r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

rays::rays(sf::Vector2f pos1, int numOfRays, sf::Color colour) {

    rays::color = colour;

    float* initX = &pos1.x;
    float* initY = &pos1.y;

    float magnitute = 10000;

    float angleStep = TAU / numOfRays;
    float currentAngle = 0.f;
    sf::Vector2f endPos = sf::Vector2f(*initX + 20000, *initY);
    float xPrime = get_distance(pos1, closest_hit(wall::get_all_objects(), pos1, endPos));;
    float yPrime = 0;

    sf::VertexArray lines(sf::LinesStrip, numOfRays * 2);

    /*calc_hit(sf::Vector2f(300, 520), sf::Vector2f(200, 820),
        pos1, sf::Vector2f(
            *initX + std::cosf(currentAngle + 6.28318f / numOfRays) * 20000,
            *initY + std::sinf(currentAngle + 6.28318f / numOfRays) * 20000));*/


    for (int i = 0; i < numOfRays * 2; i += 2) {
        endPos = sf::Vector2f(
            *initX + std::cosf(currentAngle + TAU / numOfRays) * 20000,
            *initY + std::sinf(currentAngle + TAU / numOfRays) * 20000);
        magnitute = get_distance(pos1, closest_hit(wall::get_all_objects(), pos1, endPos));
        currentAngle += angleStep;

        xPrime = magnitute * std::cosf(currentAngle);
        yPrime = magnitute * std::sinf(currentAngle);

        lines[i].position = pos1;
        lines[i].color = color;
        lines[i + 1].position = sf::Vector2f(*initX + xPrime, *initY + yPrime);
        lines[i + 1].color = color;

    }

    rays::raysSource = lines;
}

void rays::draw(sf::RenderTarget& target, sf::RenderStates states)const {
    target.draw(rays::raysSource, states);
}

sf::Vector2f rays::calc_hit(sf::Vector2f wallBegPos, sf::Vector2f wallEndPos, sf::Vector2f lineBegPos, sf::Vector2f lineEndPos) {
    
    float wallSlope = 2000;
    if (wallEndPos.x - wallBegPos.x != 0) {
        wallSlope = (wallEndPos.y - wallBegPos.y) / (wallEndPos.x - wallBegPos.x);
    }
    float wallB = (wallEndPos.y) - (wallSlope * wallEndPos.x);

    float lineSlope = 10000;
    if (lineEndPos.x - lineBegPos.x != 0) {
        lineSlope = (lineEndPos.y - lineBegPos.y) / (lineEndPos.x - lineBegPos.x);
    }
    float lineB = (lineBegPos.y) - (lineSlope * lineBegPos.x);
    
    float x = (lineB-wallB)/(wallSlope-lineSlope);
    float y = x * wallSlope + wallB;
    sf::Vector2f hitPoint = sf::Vector2f(x, y);

    if (lineSlope < -1000 || lineSlope > 10000) {
        lineSlope = 0;
    }

    if ((std::roundf(x) >= std::min(wallBegPos.x, wallEndPos.x) && std::roundf(x) <= std::max(wallBegPos.x, wallEndPos.x)) &&
        (y >= std::min(wallBegPos.y, wallEndPos.y) && y <= std::max(wallBegPos.y, wallEndPos.y))) {
        if (is_on_segment(lineBegPos, hitPoint, lineEndPos)) {
            return hitPoint;
        }
        else { return sf::Vector2f(50000, 50000); }
    }
    else {
        return sf::Vector2f(50000, 50000);
    }
    
}

sf::Vector2f rays::closest_hit(std::vector<wall*> walls, sf::Vector2f& lineBegPos, sf::Vector2f& lineEndPos) {
    sf::Vector2f hit;
    float distance = std::numeric_limits<float>::max();
    float tempD = 0;
    for (int i = 0; i < walls.size(); i++) {
        sf::Vector2f currentHit =
            rays::calc_hit(walls[i]->begPos, walls[i]->endPos, lineBegPos, lineEndPos);
        tempD = get_distance(lineBegPos, currentHit);
        if (distance > tempD) {
            distance = tempD;
            hit = currentHit;
        }
    }
    return hit;
}

