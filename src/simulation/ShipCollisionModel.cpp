#include <simulation/ShipCollisionModel.h>
#include <simulation/SurfaceObject.h>

#include <memory>

using namespace ExomoMarsLander;

ShipCollisionModel::ShipCollisionModel()
{
    //collisionRects.push_back(sf::FloatRect(-100000, -100000, 200000, 100000));
    //collisionRects.push_back(sf::FloatRect(100000, 100000, 100000, 200000));

    collisionRects.push_back(sf::FloatRect(-50000, 50000, 100000, 100000));

    collisionRects.push_back(sf::FloatRect(-150000, 150000, 100000, 100000));
    collisionRects.push_back(sf::FloatRect(50000, 150000, 100000, 100000));
    collisionRects.push_back(sf::FloatRect(200000, 200000, 100000, 100000));
    collisionRects.push_back(sf::FloatRect(300000, 300000, 100000, 100000));
}

bool ShipCollisionModel::collidesWith(const SurfaceObject& surfaceObject, double posX, double posY, double rot) const
{
    for(const auto& rect : collisionRects)
    {
        
    }
    
    return false;
}


std::vector<std::unique_ptr<sf::Shape>> ShipCollisionModel::getDisplayShapes(CoordinateTransformation transformation) const
{
    std::vector<std::unique_ptr<sf::Shape>> displayShapes;

    for(const auto& rect : collisionRects)
    {
        auto displayRect = std::make_unique<sf::RectangleShape>();
        displayRect->setSize(sf::Vector2f(transformation.ScaleToDisplayX(rect.width), transformation.ScaleToDisplayY(rect.height)));
        displayRect->setOrigin(sf::Vector2f(transformation.ScaleToDisplayX(-rect.left), transformation.ScaleToDisplayY(-rect.top)));

        displayShapes.push_back(std::move(displayRect));
        // sf::RectangleShape r(transformation.ToDisplayX(0), transformation.ToDisplayY(0) );

    }
    return displayShapes;
}