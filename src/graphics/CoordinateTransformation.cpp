#include <graphics/CoordinateTransformation.h>

using namespace ExomoMarsLander;


CoordinateTransformation::CoordinateTransformation(int pixelWidth, int pixelHeight, double simulationWidth, double simulationHeight)
    : pixelHeight(pixelHeight), pixelCenter(pixelWidth/2), simToPixelXFactor(simulationWidth / pixelWidth), simToPixelYFactor(simulationHeight / pixelHeight)
{

}

int CoordinateTransformation::ToDisplayY(double simulationY) const
{
    return pixelHeight - simulationY / simToPixelYFactor;
}

int CoordinateTransformation::ToDisplayX(double simulationX) const
{
    return pixelCenter + simulationX / simToPixelXFactor;
}


double CoordinateTransformation::ToSimulationY(int displayY) const
{
    return (pixelHeight - displayY) * simToPixelYFactor;
}

double CoordinateTransformation::ToSimulationX(int displayX) const
{
    return (displayX - pixelCenter) * simToPixelXFactor;
}

int CoordinateTransformation::ToDisplayAngle(double simulationAngle) const
{
    return static_cast<int>(simulationAngle / pi() * 180);
}

double CoordinateTransformation::ToSimulationAngle(int displayAngle)  const
{
    return displayAngle * pi() / 180;
}

int CoordinateTransformation::ScaleToDisplayY(double simulationY) const
{
    return - (simulationY / simToPixelYFactor);
}

int CoordinateTransformation::ScaleToDisplayX(double simulationX) const
{
    return simulationX / simToPixelXFactor;
}


sf::Vector2f CoordinateTransformation::transformPoint(const sf::Vector2f& point) const
{
    return sf::Vector2f((float) ScaleToDisplayX(point.x), (float) ScaleToDisplayY(point.y) );
}

sf::Vector2f CoordinateTransformation::transformPoint2(const sf::Vector2f& point) const
{
    return sf::Vector2f((float) ToDisplayX(point.x), (float) ToDisplayY(point.y) );
}