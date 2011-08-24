#ifndef MATH_HPP
#define MATH_HPP
#include <SFML/Graphics.hpp>

// Euclidean vector

// -  Second point is the "final point".
// -  Third point is the direction.
struct EVector {
    sf::Vector2f origin; // First point.
    sf::Vector2f final; // Final point.
    float direction; // Where this vector is going.
    
    EVector(sf::Vector2f origin, sf::Vector2f final, float direction);
    void CalcDir();
}; 

// Otherwise known as the "magnitude"
float euclideanNorm(EVector j);
float dotProduct(EVector j, EVector i);
sf::Vector2f normalize(EVector j);
EVector scalarMult(EVector j, int i);
void add(EVector *j, int len);

#endif // MATH_HPP
