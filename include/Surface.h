#ifndef SURFACE_H
#define SURFACE_H

#include <CoordinateTransformation.h>
#include <SurfaceObject.h>

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace ExomoMarsLander
{
    /**
     * Graphical representation of the space ship
     * */
    class Surface
    {
        public:
            Surface();

            /** Zeichne das Raumschiff auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);
            
            /** Initialisiere mit generierter Landschaft */
            void Initialize(const std::vector<std::unique_ptr<SurfaceObject>>& surfaceObjects, CoordinateTransformation transformation);

            /** Zeige das Kollisionsmodell an */
            void showCollisionModel(bool show); 
            
        private:
            std::vector<std::unique_ptr<sf::Shape>> shapes;
            std::vector<std::unique_ptr<sf::Shape>> collisionShapes;
            bool collisionModelVisible;

            void drawCollisionModelTo(sf::RenderTarget& target);
    };
}

#endif //SURFACE_H