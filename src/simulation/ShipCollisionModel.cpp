#include <GlobalResources.h>
#include <simulation/ShipCollisionModel.h>
#include <simulation/SurfaceObject.h>

#include <iostream>
#include <memory>

using namespace ExomoMarsLander;

ShipCollisionModel::ShipCollisionModel()
{
    // Kopiere die Raumschiff Textur in ein lokales Bild, um daraus das Kollisionsmodell zu berechnen
    auto& glob  = GlobalResources::GetInstance();
    auto shipImage = glob.GetSpaceship().copyToImage();
    auto imageSize = shipImage.getSize();

    for(int x=0; x<imageSize.x;++x)
    {
        for(int y=0; y<imageSize.y;++y)
        {
            // Alle Pixel, die nicht komplett transparent sind werden für die Kollisionserkennung blau (mit halber Transparenz) gemacht
            if(shipImage.getPixel(x,y) != sf::Color::Transparent)
            {
                shipImage.setPixel(x,y, sf::Color(0, 0, 255, 130));
            }
        }
    }

    collisionTexture.loadFromImage(shipImage);

    collisionSprite.setTexture(collisionTexture, true);
    collisionSprite.setScale(0.5, 0.5);
    collisionSprite.setOrigin(imageSize.x / 2, imageSize.y / 2);

    // Die bounding Box ist vereinfacht die Größe des Sprites, transformiert ins Simulations-Koordinatensystem
    // TODO: korrekte Transformation an sinnvoller Stelle berücksichtigen, Faktor 5000 könnte sich ändern
    boundingRect = sf::FloatRect(- (static_cast<float>(imageSize.x) / 2) * 5000, - (static_cast<float>(imageSize.y) / 2) * 5000, static_cast<float>(imageSize.x) * 5000, static_cast<float>(imageSize.y) * 5000);
}

sf::FloatRect ShipCollisionModel::getBoundingRect(float posX, float posY, float rot) const
{
    auto transformed = sf::Transform().translate(posX, posY).transformRect(boundingRect);
    return transformed;
}

const sf::Sprite& ShipCollisionModel::getCollisionSprite(float posX, float posY, float rot, CoordinateTransformation transformation)
{
    collisionSprite.setPosition(transformation.transformPoint2(sf::Vector2f(posX, posY)));
    collisionSprite.setRotation(transformation.ToDisplayAngle(rot));
    return collisionSprite;
}