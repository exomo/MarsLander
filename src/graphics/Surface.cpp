#include <GlobalResources.h>
#include <graphics/Surface.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace ExomoMarsLander;

Surface::Surface()
{
}

void Surface::drawTo(sf::RenderTarget& target)
{
    for(const auto& shape : shapes)
    {
        target.draw(*shape);
    }
}

/** Initialisiere mit generierter Landschaft */
void Surface::Initialize(const std::vector<std::unique_ptr<SurfaceObject>>& surfaceObjects, CoordinateTransformation transformation)
{

    std::cout << "Surface objects:\n";
    const auto& res = GlobalResources::GetInstance();

    for(const auto& obj : surfaceObjects)
    {
        // auto collisionRect = obj->getCollisionRect();
        // // auto collisionShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(transformation.ScaleToDisplayX(collisionRect.width), transformation.ScaleToDisplayY(collisionRect.height)));
        // auto collisionShape = obj->getDisplayShape(transformation);
        // collisionShape->setPosition(transformation.ToDisplayX(collisionRect.left), transformation.ToDisplayY(collisionRect.top));
        // // collisionShape->setRotation(transformation.ToDisplayAngle(collisionRect))
        // collisionShape->setFillColor(sf::Color(0,0,0,170));
        // collisionShapes.push_back(std::move(collisionShape));

        auto shape = obj->getDisplayShape(transformation);
        shape->setFillColor(sf::Color(100, 250, 250, 255));
        // shape->setOutlineColor(sf::Color(200, 150, 50));
        // shape->setOutlineThickness(0);
        shape->setTexture(&res.GetSurface());

        auto border = std::make_unique<sf::ConvexShape>(4);



        shapes.push_back(std::move(shape));

    }
}
