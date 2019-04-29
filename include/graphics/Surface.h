#ifndef SURFACE_H
#define SURFACE_H

#include <graphics/CoordinateTransformation.h>
#include <simulation/SurfaceObject.h>

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
            
        private:
            std::vector<std::unique_ptr<sf::Shape>> shapes;

            const sf::Texture& surfaceTexture;
    };
}

#endif //SURFACE_H