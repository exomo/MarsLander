#ifndef SHIPCOLLISIONMODEL_H
#define SHIPCOLLISIONMODEL_H

#include <simulation/SurfaceObject.h>

#include <SFML/Graphics.hpp>

#include <vector>

namespace ExomoMarsLander
{

    class ShipCollisionModel
    {
        public:
            ShipCollisionModel();

            sf::FloatRect getBoundingRect(float posX, float posY, float rot) const;
            std::vector<std::unique_ptr<sf::Shape>> getDisplayShapes(CoordinateTransformation transformation) const;

        private:
            std::vector<std::unique_ptr<sf::Shape>> collisionShapes;
    };

}

#endif
