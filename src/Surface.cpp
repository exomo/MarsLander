#include <iostream>
#include <sstream>
#include <string>

#include <Surface.h>

using namespace ExomoMarsLander;

Surface::Surface()
{
    sf::RectangleShape shape(sf::Vector2f(800,50));
    shape.setFillColor(sf::Color(100, 250, 250));
    shape.setOutlineColor(sf::Color(200, 150, 50));
    shape.setOutlineThickness(3);
    
    shape.setPosition(0,550);

    shapes.push_back(shape);
}

void Surface::drawTo(sf::RenderTarget& target)
{
    for(const auto& shape : shapes)
        target.draw(shape);
}
