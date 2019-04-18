#include <Surface.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace ExomoMarsLander;

Surface::Surface()
    : collisionModelVisible(false)
{
    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(800,50));
    shape->setFillColor(sf::Color(100, 250, 250));
    shape->setOutlineColor(sf::Color(200, 150, 50));
    shape->setOutlineThickness(3);
    
    shape->setPosition(0,550);

    shapes.push_back(std::move(shape));
}

void Surface::drawTo(sf::RenderTarget& target)
{
    for(const auto& shape : shapes)
    {
        target.draw(*shape);
    }

    if(collisionModelVisible)
    {
        drawCollisionModelTo(target);
    }
}

void Surface::drawCollisionModelTo(sf::RenderTarget& target)
{
    for(const auto& shape : collisionShapes)
    {
        target.draw(*shape);
    }
}

/** Initialisiere mit generierter Landschaft */
void Surface::Initialize(const std::vector<std::unique_ptr<SurfaceObject>>& surfaceObjects, CoordinateTransformation transformation)
{
    for(const auto& obj : surfaceObjects)
    {
        auto collisionRect = obj->getCollisionRect();
        auto collisionShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(transformation.ScaleToDisplayX(collisionRect.width), transformation.ScaleToDisplayY(collisionRect.height)));
        // auto shape = obj->getDisplayShape(transformation);
        collisionShape->setPosition(transformation.ToDisplayX(collisionRect.left), transformation.ToDisplayY(collisionRect.top));
        // collisionShape->setRotation(transformation.ToDisplayAngle(collisionRect))
        collisionShape->setFillColor(sf::Color(255,0,0,170));
        collisionShapes.push_back(std::move(collisionShape));

        auto shape = obj->getDisplayShape(transformation);
        shape->setFillColor(sf::Color(100, 250, 250));
        shape->setOutlineColor(sf::Color(200, 150, 50));
        shape->setOutlineThickness(3);
        shapes.push_back(std::move(shape));
    }
}

void Surface::showCollisionModel(bool show)
{
    collisionModelVisible = show;
}

