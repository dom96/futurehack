#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <maths.hpp>
using namespace std;

string itos(int i);
void draw(EVector vec, sf::RenderTarget* win);
float CalcAngle(EVector v);

#endif /* UTILS_HPP */
