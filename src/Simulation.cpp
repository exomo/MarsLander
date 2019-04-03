#include <Simulation.h>

#include <cmath>

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
    /* Neue Positionen berechnen */
    posX = posX + (velocityX * elapsedTime);
    posY = posY + (velocityY * elapsedTime);

    /* Neue Geschwindigkeiten berechnen */
    if(posY > 0) 
    {
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
        velocityY = velocityY - (gravity * elapsedTime) - (air * elapsedTime);

        if(thrustActive)
        {
            velocityY = velocityY + thrust * elapsedTime * cos(rotation);
            velocityX = velocityX + thrust * elapsedTime * sin(rotation);
        }
    }
    else
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

SpaceSimulation::ShipState SpaceSimulation::GetShipState()
{
    return ShipState {posY, posX, rotation, !hasCrashed, hasLanded};
}

