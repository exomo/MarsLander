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
            const sf::Sprite& getCollisionSprite(float posX, float posY, float rot, CoordinateTransformation transformation);

        private:
            sf::Texture collisionTexture;
            sf::Sprite collisionSprite;
            sf::FloatRect boundingRect;
    };

}

#endif
