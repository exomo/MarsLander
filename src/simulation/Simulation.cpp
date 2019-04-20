#include <graphics/CoordinateTransformation.h>
#include <simulation/Simulation.h>

#include <cmath>
#include <memory>

using namespace ExomoMarsLander;

void SpaceSimulation::Initialize()
{
    posX = -500000;
    posY = 2000000;
    rotation = 0;

    velocityX = 500;
    velocityY = 0;
    velocityRot = 0;

    thrustActive = false;
    rotationMode = Rotation::None;
    hasCrashed = false;
    hasLanded = false;

    
    collisionOverlay = sf::RectangleShape(sf::Vector2f(400, 300));
    collisionOverlay.setScale(2.0, 2.0);
    collisionRenderTexture.create(400, 300);
    collisionRenderTexture.clear(sf::Color::Magenta);
    collisionRenderTexture.display();
    collisionOverlay.setTexture(&collisionRenderTexture.getTexture());

    generateSurface();
}

void SpaceSimulation::EnableThrust(bool enable)
{
    thrustActive = enable;
}

void SpaceSimulation::Rotate(Rotation rot)
{
    rotationMode = rot;
}

void SpaceSimulation::SimulationStep(double elapsedTime)
{
    if(hasLanded || hasCrashed)
    {
        return;
    }
    updateShip(elapsedTime);
    if(hasCollision())
    {
        if(velocityY < -500)
        {
            hasCrashed = true;
        }
        else if(velocityX < -500 || velocityX > 500)
        {
            hasCrashed = true;
        }
        else
        {
            hasLanded = true;
        }
        
        posY = 0;
        velocityY = 0;
    }
}

void SpaceSimulation::updateShip(double elapsedTime)
{
    /* Neue Positionen berechnen */
    posX = posX + (velocityX * elapsedTime);
    posY = posY + (velocityY * elapsedTime);

    /* Neue Geschwindigkeiten berechnen */
    double air = 0;
    if(velocityY > 0)
    {
        air = velocityY * velocityY * airResistance;
    }
    else
    {
        air = -(velocityY * velocityY * airResistance);
    }
    
    velocityX = velocityX - (air * elapsedTime);
    velocityY = velocityY - (gravity * 0.5 * elapsedTime) - (air * elapsedTime);

    if(thrustActive)
    {
        velocityY = velocityY + thrust * elapsedTime * cos(rotation);
        velocityX = velocityX + thrust * elapsedTime * sin(rotation);
    }

    /* Neue Drehungen berechnen */
    if(rotationMode == Rotation::CounterClockwise)
    {
        rotation -= 0.009 * elapsedTime;
    }
    else if(rotationMode == Rotation::Clockwise)
    {
        rotation += 0.009 * elapsedTime;
    }
}

bool SpaceSimulation::hasCollision()
{
    // suche Kollisionsobjekte die in Frage kommen
    std::vector<const SurfaceObject*> objectsInRange;

    auto boundingRect = shipCollisionModel.getBoundingRect(posX, posY, rotation);

    for(auto& surfaceObject : planetSurface)
    {
        if(surfaceObject->rightSide > boundingRect.left 
             && surfaceObject->leftSide < (boundingRect.left + boundingRect.width))
        {
            objectsInRange.push_back(surfaceObject.get());
        }
    }

    collisionRenderTexture.clear(sf::Color::Transparent);

    CoordinateTransformation transformation(400, 300, 4000000, 3000000);

    for(const auto* surfaceObject : objectsInRange)
    {
        auto shape = surfaceObject->getDisplayShape(transformation);
        shape->setFillColor(sf::Color::Red);
        collisionRenderTexture.draw(*shape);
    }

    auto shipObjects = shipCollisionModel.getDisplayShapes(transformation);

    for(const auto& shipObject : shipObjects)
    {
        shipObject->setPosition(transformation.transformPoint2(sf::Vector2f(posX, posY)));
        shipObject->setRotation(transformation.ToDisplayAngle(rotation));
        shipObject->setFillColor(sf::Color(0, 0, 255, 100));
        collisionRenderTexture.draw(*shipObject);
    }

    collisionRenderTexture.display();

    auto img = collisionRenderTexture.getTexture().copyToImage();

    for(int x=0;x<400;++x)
    for(int y=0;y<300;++y)
    {
        auto p = img.getPixel(x,y);
        if(p.a != 0 && p.b > 0 && p.r > 0) 
        {
            return true;
        }
    }


    if(posY < 0)
    {
        return true;
    }
    return false;
}

SpaceSimulation::ShipState SpaceSimulation::GetShipState()
{
    return ShipState {posY, posX, rotation, !hasCrashed, hasLanded};
}

void SpaceSimulation::generateSurface()
{

    auto leftSlope = std::make_unique<SurfaceSlope>();
    leftSlope->leftSide = -2000000;
    leftSlope->rightSide = -1000000;
    leftSlope->leftAltitude = 1000000;
    leftSlope->rightAltitude = 20000;
    leftSlope->allowLanding = true;
    planetSurface.push_back(std::move(leftSlope));

    auto landingZone = std::make_unique<SurfaceFlat>();
    landingZone->leftSide = -1000000;
    landingZone->rightSide = 1000000;
    landingZone->altitude = 20000;
    landingZone->allowLanding = true;
    planetSurface.push_back(std::move(landingZone));

    auto rightSlope = std::make_unique<SurfaceSlope>();
    rightSlope->leftSide = 1000000;
    rightSlope->rightSide = 2000000;
    rightSlope->leftAltitude = 20000;
    rightSlope->rightAltitude = 2000000;
    rightSlope->allowLanding = true;
    planetSurface.push_back(std::move(rightSlope));
}

const sf::Drawable& SpaceSimulation::getCollisionOverlay() const
{
    return collisionOverlay;
}

const std::vector<std::unique_ptr<SurfaceObject>>& SpaceSimulation::getSurface() const
{
    return planetSurface;
}