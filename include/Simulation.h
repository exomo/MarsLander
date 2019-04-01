#ifndef SIMULATION_H
#define SIMULATION_H

/** 
 * The main game logic is within the simulation of the space ship
 *  
 */

namespace ExomoMarsLander
{
    class SpaceSimulation
    {
        public:
            void Initialize();

            void EnableThrust(bool enable);
            void SimulationStep(double elapsedMilliseconds);

            int GetShipX();
            int GetShipY();

        private:
            /* Einige Konstanten für die Simulation */
            const double gravity = 9.81; // gravity constant
            const double thrust  = 15;   // thrust constant
            const double airResistance = 0.0000001; // air resistance constant

            /* Bewegungsstatus des Schiffs */
            double posX = 0;
            double posY = 0;
            double rotation = 0;
            double velocityX = 0;
            double velocityY = 0;
            double velocityRot = 0;

            bool thrustActive = false;
    };
}

#endif //SIMULATION_H
