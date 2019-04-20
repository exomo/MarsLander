#ifndef COORDINATETRANSFORMATION_H
#define COORDINATETRANSFORMATION_H

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

            int ToDisplayY(double simulationY);
            int ToDisplayX(double simulationX);
            int ToDisplayAngle(double simulationAngle);
            
            double ToSimulationY(int displayY);
            double ToSimulationX(int displayX);
            double ToSimulationAngle(int displayAngle);

            int ScaleToDisplayY(double simulationY);
            int ScaleToDisplayX(double simulationX);

        private:
            constexpr double pi() { return std::atan(1)*4; }

            int pixelHeight;
            int pixelCenter;
            double simToPixelYFactor;
            double simToPixelXFactor;
    };

}

#endif
