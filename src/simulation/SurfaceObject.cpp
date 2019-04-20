#include <simulation/SurfaceObject.h>

using namespace ExomoMarsLander;


std::unique_ptr<sf::Shape> SurfaceFlat::getDisplayShape(CoordinateTransformation transformation) const
{
    auto shape = std::make_unique<sf::ConvexShape>(4);
    shape->setPoint(0, sf::Vector2f(transformation.ToDisplayX(leftSide), transformation.ToDisplayY(0)));
    shape->setPoint(1, sf::Vector2f(transformation.ToDisplayX(leftSide), transformation.ToDisplayY(altitude)));
    shape->setPoint(2, sf::Vector2f(transformation.ToDisplayX(rightSide), transformation.ToDisplayY(altitude)));
    shape->setPoint(3, sf::Vector2f(transformation.ToDisplayX(rightSide), transformation.ToDisplayY(0)));
    return shape;
}

std::unique_ptr<sf::Shape> SurfaceSlope::getDisplayShape(CoordinateTransformation transformation) const
{
    auto shape = std::make_unique<sf::ConvexShape>(4);
    shape->setPoint(0, sf::Vector2f(transformation.ToDisplayX(leftSide), transformation.ToDisplayY(0)));
    shape->setPoint(1, sf::Vector2f(transformation.ToDisplayX(leftSide), transformation.ToDisplayY(leftAltitude)));
    shape->setPoint(2, sf::Vector2f(transformation.ToDisplayX(rightSide), transformation.ToDisplayY(rightAltitude)));
    shape->setPoint(3, sf::Vector2f(transformation.ToDisplayX(rightSide), transformation.ToDisplayY(0)));
    return shape;
}

bool SurfaceFlat::collidesWith(sf::FloatRect& rect) const 
{
    return false;
}

bool SurfaceSlope::collidesWith(sf::FloatRect& rect) const 
{
    return false;
}