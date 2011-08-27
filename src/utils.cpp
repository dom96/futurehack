#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>
#include <iostream>
#include <cassert>

#include <utils.hpp>
#include <maths.hpp>

using namespace std;

string itos(int i)
{
    char result[21];
    sprintf(result, "%d", i); // decided to go with sprintf since it's part of stdlib.
    return string(result);
}

void draw(EVector vec, sf::RenderTarget* win)
{
    sf::Shape line = sf::Shape::Line(vec.origin.x, vec.origin.y, 
                                     vec.final.x, vec.final.y,
                                     2.5f, sf::Color::Green);
    win->Draw(line);
}

float CalcAngle(EVector v)
{
  float theta = atan2(v.origin.y - v.final.y, v.origin.x - v.final.x);
  return theta * (180 / M_PI);
}
