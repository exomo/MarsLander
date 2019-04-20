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
            bool collidesWith(const SurfaceObject& surfaceObject, double posX, double posY, double rot) const;

            std::vector<std::unique_ptr<sf::Shape>> getDisplayShapes(CoordinateTransformation transformation) const;

        private:
            std::vector<sf::FloatRect> collisionRects;
    };

}

#endif
