#ifndef SURFACEOBJECT_H
#define SURFACEOBJECT_H

#include <CoordinateTransformation.h>

#include <SFML/Graphics.hpp>

#include <vector>

namespace ExomoMarsLander
{

    /** Teil der Landschaft. Die Landschaft besteht aus mehreren aneinendergereihten SurfaceObjects 
     *  
    */
    struct SurfaceObject
    {
        // Position des Objekts in der simulierten Welt
        double leftSide;
        double rightSide;

        bool allowLanding;

        virtual std::unique_ptr<sf::Shape> getDisplayShape(CoordinateTransformation transformation) const = 0;
        virtual sf::FloatRect getCollisionRect() const = 0;
    };

    struct SurfaceFlat : public SurfaceObject
    {
        double altitude;

        std::unique_ptr<sf::Shape> getDisplayShape(CoordinateTransformation transformation) const override;
        sf::FloatRect getCollisionRect() const override;
    };

    struct SurfaceSlope : public SurfaceObject
    {
        double leftAltitude;
        double centerAltitude;
        double rightAltitude;
        double centerOffset;

        std::unique_ptr<sf::Shape> getDisplayShape(CoordinateTransformation transformation) const override;
        sf::FloatRect getCollisionRect() const override;
    };
}

#endif
