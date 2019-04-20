#include <simulation/SurfaceObject.h>

using namespace ExomoMarsLander;


std::unique_ptr<sf::Shape> SurfaceFlat::getDisplayShape(CoordinateTransformation transformation) const
{
    auto shape = std::make_unique<sf::ConvexShape>(4);
    shape->setPoint(0, transformation.transformPoint2(sf::Vector2f(leftSide, 0)));
    shape->setPoint(1, transformation.transformPoint2(sf::Vector2f(leftSide, altitude)));
    shape->setPoint(2, transformation.transformPoint2(sf::Vector2f(rightSide, altitude)));
    shape->setPoint(3, transformation.transformPoint2(sf::Vector2f(rightSide, 0)));
    return shape;
}

std::unique_ptr<sf::Shape> SurfaceSlope::getDisplayShape(CoordinateTransformation transformation) const
{
    auto shape = std::make_unique<sf::ConvexShape>(4);
    shape->setPoint(0, transformation.transformPoint2(sf::Vector2f(leftSide, 0)));
    shape->setPoint(1, transformation.transformPoint2(sf::Vector2f(leftSide, leftAltitude)));
    shape->setPoint(2, transformation.transformPoint2(sf::Vector2f(rightSide, rightAltitude)));
    shape->setPoint(3, transformation.transformPoint2(sf::Vector2f(rightSide, 0)));
    return shape;
}
