#ifndef COORDINATETRANSFORMATION_H
#define COORDINATETRANSFORMATION_H

#include <SFML/Graphics.hpp>

#include <cmath>

namespace ExomoMarsLander
{

    /** Transformation von Simulationskoordinatensystem in das Anzeigekoordinatensystem 
     *
     * Für Simulation und Anzeige werden unterschiedliche Koorsinatensysteme verwendet mit dem Ziel,
     * die Berechnungen der Simulation von der Bildschirmgröße unabhängig zu machen.
     * 
     * Die Koordinatentransformation rechnet die beiden Systeme in einander um. 
     * 
     * Simulation:
     * 
     *              y (+) [mm]
     *              ^
     *              |
     *              |
     *              |
     *              |
     * x(-) <-------+--------> x (+) [mm]
     * 
     * Anzeige:
     * 
     * +---------> y (+) [Pixel]
     * |
     * |
     * |
     * |
     * v 
     * x (+) [Pixel]
    */
    class CoordinateTransformation
    {
        public:
            CoordinateTransformation() = default;
            CoordinateTransformation(int pixelWidth, int pixelHeight, double simulationWidth, double simulationHeight);

            int ToDisplayY(double simulationY) const;
            int ToDisplayX(double simulationX) const;
            int ToDisplayAngle(double simulationAngle) const;
            
            double ToSimulationY(int displayY) const;
            double ToSimulationX(int displayX) const;
            double ToSimulationAngle(int displayAngle) const;

            int ScaleToDisplayY(double simulationY) const;
            int ScaleToDisplayX(double simulationX) const;

            sf::Vector2f transformPoint(const sf::Vector2f& point) const;
            sf::Vector2f transformPoint2(const sf::Vector2f& point) const;

        private:
            constexpr double pi() const { return std::atan(1)*4; }

            int pixelHeight;
            int pixelCenter;
            double simToPixelYFactor;
            double simToPixelXFactor;
    };

}

#endif
