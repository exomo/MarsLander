#include <GlobalResources.h>
#include <graphics/Surface.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace ExomoMarsLander;

Surface::Surface()
    : surfaceTexture(GlobalResources::GetInstance().GetSurface() )
{
}

void Surface::drawTo(sf::RenderTarget& target)
{
    for(const auto& shape : shapes)
    {
        target.draw(*shape);
    }
}

std::unique_ptr<sf::Shape> copyShape(const sf::Shape& shape)
{
    auto newShape = std::make_unique<sf::ConvexShape>();
    newShape->setPointCount(shape.getPointCount());
    for(size_t i=0; i<shape.getPointCount(); ++i)
    {
        newShape->setPoint(i, shape.getPoint(i));
    }
    return std::move(newShape);
}

/** Initialisiere mit generierter Landschaft */
void Surface::Initialize(const std::vector<std::unique_ptr<SurfaceObject>>& surfaceObjects, CoordinateTransformation transformation)
{
    for(const auto& obj : surfaceObjects)
    {
        auto shape = obj->getDisplayShape(transformation);
        auto shape2 = copyShape(*shape);

        if(obj->allowLanding)
        {
            shape2->setFillColor(sf::Color(150, 250, 50));
        }
        else
        {
            shape2->setFillColor(sf::Color(250, 50, 50));
        }
        
        shapes.push_back(std::move(shape2));
  
        shape->move(sf::Vector2f(0, 3.0));
        shape->setTexture(&surfaceTexture);
        shapes.push_back(std::move(shape));
    }
}
