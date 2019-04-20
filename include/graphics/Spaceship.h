#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <graphics/CoordinateTransformation.h>
#include <simulation/ShipCollisionModel.h>

#include <SFML/Graphics.hpp>

namespace ExomoMarsLander
{
    /**
     * Graphical representation of the space ship
     * */
    class Spaceship
    {
        public:
            Spaceship();

            /** Initialisiere das Raumschiff mit Kollisionsmodell und Transformation */
            void initialize(const ShipCollisionModel& collisionModel, CoordinateTransformation transformation);

            /** Setze Position des Raumschiffs */
            void setPosition(double x, double y);

            /** Setze aktuelle Drehung des Raumschiffs */
            void setRotation(double r);

            /** Aktiviert die Darstellung der Triebwerke */
            void enableFlame(bool enable);

            /** Zeichne das Raumschiff auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);

            /** Zeige das Kollisionsmodell an */
            void showCollisionModel(bool show); 
            
        private:
            sf::CircleShape nose;
            sf::CircleShape body;
            sf::CircleShape flame;
            std::vector<std::unique_ptr<sf::Shape>> collisionShapes;


            bool flameOn;

            float posX;
            float posY;
            float rot;

            bool collisionModelVisible;
            
            void drawCollisionModelTo(sf::RenderTarget& target);
    };
}

#endif //SPACESHIP_H