#ifndef SURFACE_H
#define SURFACE_H

#include <SFML/Graphics.hpp>
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

            /* Zeichne das Raumschiff auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);
            
        private:
            std::vector<sf::RectangleShape> shapes;
    };
}

#endif //SURFACE_H