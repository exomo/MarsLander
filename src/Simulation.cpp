#include <Simulation.h>

using namespace ExomoMarsLander;

void SpaceSimulation::Initialize()
{
    posX = 2000000;
    posY = 2000000;
    rotation = 0;

    velocityX = 0;
    velocityY = 0;
    velocityRot = 0;

    thrustActive = false;
}

void SpaceSimulation::EnableThrust(bool enable)
{
    thrustActive = enable;
}

void SpaceSimulation::SimulationStep(double elapsedTime)
{
    posY = posY + (velocityY * elapsedTime);

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
        
        velocityY = velocityY - (gravity * elapsedTime) - (air * elapsedTime);

        if(thrustActive)
            velocityY = velocityY + thrust * elapsedTime;
    }
    else
    {
        posY = 0;
        if(velocityY < 0)
        {
            velocityY = -velocityY; // bounce
        }
    }
    
}

int SpaceSimulation::GetShipX()
{
    return posX;
}

int SpaceSimulation::GetShipY()
{
    return posY;
}
