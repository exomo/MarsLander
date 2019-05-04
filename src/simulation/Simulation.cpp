#include <graphics/CoordinateTransformation.h>
#include <simulation/Simulation.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>

using namespace ExomoMarsLander;

void SpaceSimulation::Initialize()
{
    posX = -500000;
    posY = 2000000;
    rotation = 0;

    // velocityX = 0;
    velocityX = 500;
    velocityY = 0;
    velocityRot = 0;

    thrustActive = false;
    rotationMode = Rotation::None;
    fuel = fuelTankSize;
    hasCrashed = false;
    hasLanded = false;

    collisionRenderTexture.create(400, 300);
    collisionRenderTexture.clear(sf::Color::Magenta);
    collisionRenderTexture.display();
    collisionOverlay = sf::RectangleShape(sf::Vector2f(400, 300));
    collisionOverlay.setScale(2.0, 2.0);
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
    switch (checkCollision())
    {
    case CollisionState::None:
        break;

    case CollisionState::Surface:
        hasCrashed = true;
        break;

    case CollisionState::LandingZone:
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
        break;

    case CollisionState::Outside:
        hasCrashed = true;
        break;
    
    default:
        break;
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

    if(thrustActive && fuel > 0)
    {
        velocityY = velocityY + thrust * elapsedTime * cos(rotation);
        velocityX = velocityX + thrust * elapsedTime * sin(rotation);

        fuel = std::max(fuel - (fuelConsumption * elapsedTime), 0.0);
    }

    /* Neue Drehungen berechnen */
    if(fuel > 0)
    {
        if(rotationMode == Rotation::CounterClockwise)
        {
            rotation -= rotationSpeed * elapsedTime;
            fuel = std::max(fuel - (rotationFuelConsumption * elapsedTime), 0.0);
        }
        else if(rotationMode == Rotation::Clockwise)
        {
            rotation += rotationSpeed * elapsedTime;
            fuel = std::max(fuel - (rotationFuelConsumption * elapsedTime), 0.0);
        }
    }
}

SpaceSimulation::CollisionState SpaceSimulation::checkCollision()
{
    auto boundingRect = shipCollisionModel.getBoundingRect(posX, posY, rotation);

    // Seitlich aus dem Bildschirm gilt als Kollision
    if(boundingRect.left + boundingRect.width < -2000000 || boundingRect.left > 2000000)
    {
        return CollisionState::Outside;
    }

    // suche Kollisionsobjekte die in Frage kommen
    std::vector<const SurfaceObject*> objectsInRange;

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
        if(surfaceObject->allowLanding)
        {
            shape->setFillColor(sf::Color::Green);
        }
        else
        {
            shape->setFillColor(sf::Color::Red);
        }
        
        collisionRenderTexture.draw(*shape);
    }

    const auto& shipObject = shipCollisionModel.getCollisionSprite(posX, posY, rotation, transformation);
    collisionRenderTexture.draw(shipObject);

    collisionRenderTexture.display();

    auto img = collisionRenderTexture.getTexture().copyToImage();

    bool landing = false;
    for(int x=0;x<400;++x)
    for(int y=0;y<300;++y)
    {
        auto p = img.getPixel(x,y);
        if(p.a != 0 && p.b > 0 && p.r > 0)
        {
            return CollisionState::Surface;
        }
        if(p.a != 0 && p.b > 0 && p.g > 0)
        {
            landing = true;
        }
    }

    if(landing)
    {
        return CollisionState::LandingZone;
    }

    if(posY < 0)
    {
        return CollisionState::Surface;
    }

    return CollisionState::None;
}

SpaceSimulation::ShipState SpaceSimulation::GetShipState()
{
    return ShipState {posY, posX, rotation, (fuel * 100 / fuelTankSize), !hasCrashed, hasLanded};
}

void SpaceSimulation::generateSurface()
{
    const int maxAltitude = 1000000;
    const int minLandingAltitude = 10000;
    const int maxLandingAltitude = 500000;
    const int landingZoneWidth = 600000;
    const double leftBorder = -2000000;
    const double rightBorder = 2000000;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);

    // Generiere zufällige Landefläche
    std::uniform_real_distribution<double> landingAltitudeDist(minLandingAltitude, maxLandingAltitude);
    std::uniform_real_distribution<double> landingPositionDist(leftBorder + landingZoneWidth, rightBorder - landingZoneWidth - landingZoneWidth);
    auto landingZone = std::make_unique<SurfaceFlat>();
    landingZone->leftSide = landingPositionDist(mt);
    landingZone->rightSide = landingZone->leftSide + landingZoneWidth;
    landingZone->altitude = landingAltitudeDist(mt);
    landingZone->allowLanding = true;

    auto leftPosition = landingZone->leftSide;
    auto leftPositionAltitude = landingZone->altitude;
    auto rightPosition = landingZone->rightSide;
    auto rightPositionAltitude = landingZone->altitude;

    planetSurface.push_back(std::move(landingZone));

    std::uniform_real_distribution<double> widthDist(landingZoneWidth / 4, landingZoneWidth * 1.5);
    std::uniform_real_distribution<double> altitudeDist(minLandingAltitude, maxAltitude);

    // Generiere Landschaft links der Landezone
    while(leftPosition > leftBorder)
    {
        auto leftSlope = std::make_unique<SurfaceSlope>();

        leftSlope->leftSide = leftPosition - widthDist(mt);
        leftSlope->rightSide = leftPosition;
        leftSlope->leftAltitude = altitudeDist(mt);
        leftSlope->rightAltitude = leftPositionAltitude;
        leftSlope->allowLanding = false;
        leftPosition = leftSlope->leftSide;
        leftPositionAltitude = leftSlope->leftAltitude;
        planetSurface.push_back(std::move(leftSlope));
    }

    // Generiere Landschaft rechts der Landezone
    while(rightPosition < rightBorder)
    {
        auto rightSlope = std::make_unique<SurfaceSlope>();
        rightSlope->leftSide = rightPosition; leftPosition;
        rightSlope->rightSide = rightPosition + widthDist(mt);
        rightSlope->leftAltitude = rightPositionAltitude;;
        rightSlope->rightAltitude = altitudeDist(mt);
        rightSlope->allowLanding = false;
        rightPosition = rightSlope->rightSide;
        rightPositionAltitude = rightSlope->rightAltitude;
        planetSurface.push_back(std::move(rightSlope));
    }
}

const sf::Drawable& SpaceSimulation::getCollisionOverlay() const
{
    return collisionOverlay;
}

const std::vector<std::unique_ptr<SurfaceObject>>& SpaceSimulation::getSurface() const
{
    return planetSurface;
}