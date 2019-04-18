#include <Simulation.h>

#include <cmath>
#include <memory>

using namespace ExomoMarsLander;

void SpaceSimulation::Initialize()
{
    posX = 0;
    posY = 2000000;
    rotation = 0;

    velocityX = 0;
    velocityY = 0;
    velocityRot = 0;

    thrustActive = false;
    rotationMode = Rotation::None;
    hasCrashed = false;
    hasLanded = false;

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
    // TODO: implement real collision detection with generated surface

    // auto boundingRext = shipCollisionModel.getBoundingRect();
    // shipCollisionModel.collidesWith()

    // for(const auto& surfaceObject : planetSurface)
    // {
    //     if(shipCollisionModel.collidesWith(*surfaceObject, posX, posY, rotation))
    //     {
    //         return true;
    //     }
    // }

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

const std::vector<std::unique_ptr<SurfaceObject>>& SpaceSimulation::GetSurface()
{
    return planetSurface;
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

const ShipCollisionModel& SpaceSimulation::GetShipCollisionModel()
{
    return shipCollisionModel;
}