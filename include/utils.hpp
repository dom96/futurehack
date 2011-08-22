#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <maths.hpp>
using namespace std;

string itos(int i);
void draw(EVector vec, sf::RenderTarget* win);
float AngleToPoint(sf::FloatRect objectSize, sf::Vector2f point,
                   sf::Vector2f left = sf::Vector2f(-1.f, -1.f));
float inverseAngle(float angle);

#endif /* UTILS_HPP */
