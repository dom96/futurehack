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

// point is the point where to rotate to.
float AngleToPoint(sf::FloatRect objectSize, sf::Vector2f point,
                   sf::Vector2f left)
{
    // I'm very proud of this function. Too bad the `acos` way doesn't work.

    // Get left if `left` is (-1, -1)
    if (left == sf::Vector2f(-1.f, -1.f))
    {
        left = sf::Vector2f(0,
                            objectSize.Top + (objectSize.Height / 2));
    }
    
    if (!(left.x == 0 or left.y == 0))
        assert(false);
    
    // Create two EVectors. The origin will be the middle of the player.
    sf::Vector2f origin = sf::Vector2f(objectSize.Left + (objectSize.Width / 2),
                                       objectSize.Top + (objectSize.Height / 2));

    EVector a = EVector(origin, point, sf::Vector2f(-1,-1));
    EVector b = EVector(origin, left, sf::Vector2f(-1,0));
    
    // Calculate the angle between the two points.
    /*
    float u = euclideanNorm(a);
    cout << "U : " << u << endl;
    float v = euclideanNorm(b);
    cout << "V : " << v << endl;
    float product = dotProduct(a, b);
    cout << "Product : " << product << endl;
    float angle = acos(product / (u * v)) * (180 / PI);
    */
    float thetaA = atan2(a.origin.x - a.final.x, a.origin.y - a.final.y);
    float thetaB = atan2(b.origin.x - b.final.x, b.origin.y - b.final.y);
    float thetaAB = thetaB - thetaA;
    
    while (thetaAB <= -M_PI)
        thetaAB += 2 * M_PI;
    
    while (thetaAB > M_PI)
        thetaAB -= 2 * M_PI;
        
    //cout << thetaAB << endl;
    float angle = thetaAB * (180 / M_PI);
    //cout << angle << endl;
    return angle;
}

float inverseAngle(float angle)
{
  if (angle > 0)
    return 0 - angle;
  else
    return abs(angle);
}
