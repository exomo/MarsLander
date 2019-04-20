#include <graphics/CoordinateTransformation.h>

using namespace ExomoMarsLander;


CoordinateTransformation::CoordinateTransformation(int pixelWidth, int pixelHeight, double simulationWidth, double simulationHeight)
    : pixelHeight(pixelHeight), pixelCenter(pixelWidth/2), simToPixelXFactor(simulationWidth / pixelWidth), simToPixelYFactor(simulationHeight / pixelHeight)
{

}

int CoordinateTransformation::ToDisplayY(double simulationY)
{
    return pixelHeight - simulationY / simToPixelYFactor;
}

int CoordinateTransformation::ToDisplayX(double simulationX)
{
    return pixelCenter + simulationX / simToPixelXFactor;
}


double CoordinateTransformation::ToSimulationY(int displayY)
{
    return (pixelHeight - displayY) * simToPixelYFactor;
}

double CoordinateTransformation::ToSimulationX(int displayX)
{
    return (displayX - pixelCenter) * simToPixelXFactor;
}

int CoordinateTransformation::ToDisplayAngle(double simulationAngle)
{
    return static_cast<int>(simulationAngle / pi() * 180);
}

double CoordinateTransformation::ToSimulationAngle(int displayAngle)
{
    return displayAngle * pi() / 180;
}

int CoordinateTransformation::ScaleToDisplayY(double simulationY)
{
    return - (simulationY / simToPixelYFactor);
}

int CoordinateTransformation::ScaleToDisplayX(double simulationX)
{
    return simulationX / simToPixelXFactor;
}
