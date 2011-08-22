#ifndef MATH_HPP
#define MATH_HPP
#include <SFML/Graphics.hpp>

// Euclidean vector

// -  Second point is the "final point".
// -  Third point is the direction.
struct EVector {
    sf::Vector2f origin; // First point.
    sf::Vector2f final; // Final point.
    sf::Vector2f direction; // Where this vector is going.
    
    EVector(sf::Vector2f origin, sf::Vector2f final, sf::Vector2f direction);
}; 

const sf::Vector3f e1 = sf::Vector3f(1.f, 0.f, 0.f);
const sf::Vector3f e2 = sf::Vector3f(0.f, 1.f, 0.f);
const sf::Vector3f e3 = sf::Vector3f(0.f, 0.f, 1.f);

// TODO: Scalar multiplication.

// Otherwise known as the "magnitude"
float euclideanNorm(EVector j);
float dotProduct(EVector j, EVector i);
EVector normalize(EVector j);


#endif // MATH_HPP
