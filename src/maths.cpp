#include <cmath>

#include <maths.hpp>

EVector::EVector(sf::Vector2f initOrigin, sf::Vector2f initFinal, sf::Vector2f initDirection)
{
  origin = initOrigin;
  final = initFinal;
  direction = initDirection; 
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
EVector normalize(EVector j)
{
  sf::Vector2f a = sf::Vector2f((j.x.x / euclideanNorm(j)) * e1,
                              (j.x.y / euclideanNorm(j)) * e1);
  sf::Vector2f b = sf::Vector2f((j.y.x / euclideanNorm(j)) * e2,
                              (j.y.y / euclideanNorm(j)) * e2);
  sf::Vector2f c = sf::Vector2f((j.z.x / euclideanNorm(j)) * e3,
                              (j.z.y / euclideanNorm(j)) * e3);
  return EVector(a, b, c);
}*/
