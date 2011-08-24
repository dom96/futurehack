#include <iostream>

#include <cmath>

#include <maths.hpp>
#include <utils.hpp>

EVector::EVector(sf::Vector2f initOrigin, sf::Vector2f initFinal,
                 float initDirection)
{
  origin = initOrigin;
  final = initFinal;
  direction = initDirection; 
}

/* Calculate the direction in radians. */
void EVector::CalcDir()
{
  direction = atan2(final.y - origin.y, final.x - origin.x);
}

// Otherwise known as the "magnitude"
float euclideanNorm(EVector j)
{
  return sqrt(pow(j.origin.x - j.final.x, 2) +
              pow(j.origin.y - j.final.y, 2));
}

float dotProduct(EVector j, EVector i)
{
  return (j.origin.x * i.origin.x) + (j.origin.y * i.origin.y) +
         (j.final.x * i.final.x) + (j.final.y * i.final.y);
}
/*
EVector scalarMult(EVector j, int i)
{
  return EVector(j.final, sf::Vector2f((j.direction.x * i) * j.final.x,
                                       (j.direction.y * i) * j.final.y),
                 j.direction); 
}
*/

/*
EVector add(EVector j, int i)
{
  float xaxis = i * cos(j.direction);
  float yaxis = i * sin(j.direction);
  return EVector(sf::Vector2f(j.origin.x + xaxis,
                              j.origin.y + yaxis),
                 sf::Vector2f(j.final.x + xaxis, 
                              j.final.y + yaxis), j.direction);
}
*/


sf::Vector2f normalize(EVector j)
{
  float len = euclideanNorm(j);
  float dx = j.origin.x - j.final.x;
  float dy = j.origin.y - j.final.y;
  return sf::Vector2f(dx / len, dy / len);
}
