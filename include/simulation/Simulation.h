#ifndef SIMULATION_H
#define SIMULATION_H

#include <simulation/ShipCollisionModel.h>
#include <simulation/SurfaceObject.h>

#include <memory>
#include <vector>

/**
 * The main game logic is within the simulation of the space ship
 *
 */

namespace ExomoMarsLander
{
    class SpaceSimulation
    {
        public:
            /** Mögliche Drehrichtungen des Raumschiffs
             * */
            enum Rotation
            {
                None,
                Clockwise,
                CounterClockwise
            };

            /** Position des Raumschiffs in der simulierten Welt
             * */
            struct ShipState
            {
                /** Hohe (in m) über dem Nullpunkt des Bodens
                 * */
                double altitude;

                /** Horizontale Position (in m) ausgehend vom Nullpunkt in der Mitte
                 * */
                double horizontalPosition;

                /** Lage/Drehung (in Bogenmaß, 0 = aufrecht)
                 * */
                double rotation;

                /** Übriger Treibstoff im Tank 
                 *  Werte 0 (leer) bis 100 (voll)
                 * */
                double fuel;

                /** Gibt an ob das Raumschiff noch ganz ist
                 * */
                bool isAlive;

                /** Gibt an ob das Raumschiff gelandet ist
                 * */
                bool hasLanded;
            };

            /** Initialisiert die Simulation, erzeugt eine neue Landschaft mit den eingestellten Parametern und
             *  setzt das Raumschiff auf die Startposition
             * */
            void Initialize();

            /** Schub des Haupttriebwerks ein- oder ausschalten
             * */
            void EnableThrust(bool enable);

            /** Drehung festlegen
             * */
            void Rotate(Rotation rot);

            /** Mache einen Schritt in der Simulation
             *
             *  Ein Zeitschritt berechnet die Bewegung aller Objekte in der vergangenen Zeit
             * */
            void SimulationStep(double elapsedMilliseconds);

            /** Gibt die Position des Raumschiffs zurück
             * */
            ShipState GetShipState();

            /** Gibt die Landschaftsbeschreibung zurück
             * */
            const std::vector<std::unique_ptr<SurfaceObject>>& getSurface() const;

            const sf::Drawable& getCollisionOverlay() const;

        private:
            /* Einige Konstanten für die Simulation */
            const double gravity = 1.81; // gravity constant
            const double thrust  = 3;   // thrust constant
            //const double airResistance = 0.0000001; // air resistance constant
            const double airResistance = 0; // air resistance constant
            const double rotationSpeed = 0.005; // Drehgeschwindigkeit
            const double fuelConsumption = 0.003; // Treibstoffverbrauch
            const double rotationFuelConsumption = 0.001; // Treibstoffverbrauch
            const double fuelTankSize = 10; // Größe des Treibstofftanks

            /* Bewegungsstatus des Schiffs */

            /** Position rechts/links in m */
            double posX = 0;

            /** Höhe in m */
            double posY = 0;

            /** Drehung */
            double rotation = 0;

            /** Geschwindigkeit rechts/links (> 0 = nach rechts) */
            double velocityX = 0;

            /** Fallgeschwindigkeit (< 0 = nach unten) */
            double velocityY = 0;

            /** Drehgeschwindigkeit (> 0 = im Uhrzeigersinn) */
            double velocityRot = 0;

            bool hasCrashed = false;
            bool hasLanded = false;

            /** Treibstoffreserven */
            double fuel;

            /** Landschaft,  */
            std::vector<std::unique_ptr<SurfaceObject>> planetSurface;

            ShipCollisionModel shipCollisionModel;

            sf::RenderTexture collisionRenderTexture;
            sf::RectangleShape collisionOverlay;

            /* Eingaben aus dem Spiel */

            /** Triebwerk ist an */
            bool thrustActive = false;

            /** Aktuelle Drehvorgabe */
            Rotation rotationMode;

            /** Position des Raumschiffs aktualisieren (Physik)  * */
            void updateShip(double elapsedTime);

            /** Kollisionserkennung für Raumschiff und Welt */
            bool hasCollision();

            /** Generiert eine zufällige Landschaft */
            void generateSurface();
    };
}

#endif //SIMULATION_H
