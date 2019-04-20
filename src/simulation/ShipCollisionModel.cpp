#include <simulation/ShipCollisionModel.h>
#include <simulation/SurfaceObject.h>

#include <iostream>
#include <memory>

using namespace ExomoMarsLander;

ShipCollisionModel::ShipCollisionModel()
{
    auto base = std::make_unique<sf::ConvexShape>();
    base->setPointCount(3);
    base->setPoint(0, sf::Vector2f(-100000, 0));
    base->setPoint(1, sf::Vector2f(0, 200000));
    base->setPoint(2, sf::Vector2f(100000, 0));
    collisionShapes.push_back(std::move(base));
    
    auto base3 = std::make_unique<sf::CircleShape>(100000);
    base3->setOrigin(100000, 100000);
    collisionShapes.push_back(std::move(base3));
}

sf::FloatRect ShipCollisionModel::getBoundingRect(float posX, float posY, float rot) const
{
    sf::FloatRect bounding(0,0,0,0);

    // TODO: do as much as possible in initialization

    // Mit 0 initialisieren ist hier ok weil das Raumschiff immer um den 0-Punkt herumk sein muss
    float leftMost = 0;
    float rightMost = 0;
    float topMost = 0;
    float bottomMost = 0;

    for(const auto& shape : collisionShapes)
    {
        for(int i = 0; i<shape->getPointCount(); ++i)
        {
            auto x = shape->getPoint(i).x;
            auto y = shape->getPoint(i).y;
            if(x < leftMost) leftMost = x;
            if(x > rightMost) rightMost = x;
            if(y > topMost) topMost = y;
            if(y < bottomMost) bottomMost = y;
        }
    }

    return sf::Transform().rotate(rot / 57).translate(posX, posY).transformRect(bounding);
}

std::vector<std::unique_ptr<sf::Shape>> ShipCollisionModel::getDisplayShapes(CoordinateTransformation transformation) const
{
    std::vector<std::unique_ptr<sf::Shape>> displayShapes;

    for(const auto& shape : collisionShapes)
    {
        auto displayShape = std::make_unique<sf::ConvexShape>();
        displayShape->setPointCount(shape->getPointCount());
        for(int i=0; i<shape->getPointCount(); ++i)
        {
            displayShape->setPoint(i, transformation.transformPoint2(shape->getPoint(i)));
        }

        displayShape->setOrigin(transformation.transformPoint2(shape->getOrigin()));
        displayShapes.push_back(std::move(displayShape));
    }
    
    return displayShapes;
}