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
    // TODO: Why do I not need to add half of the height to the origin?
    // -- I think I get it now. The lines are parallel yielding 0 degrees.

    // Get left if `left` is (-1, -1)
    if (left == sf::Vector2f(-1.f, -1.f))
    {
        left = sf::Vector2f(0,
                            objectSize.Top);
    }
    
    if (!(left.x == 0 or left.y == 0))
        assert(false);
    
    //cout << objectSize.Left << " " << objectSize.Top << " " 
    //     << objectSize.Width << " " << objectSize.Height << endl;
 
    // Create two EVectors. The origin will be the middle of the player.
    sf::Vector2f origin = sf::Vector2f(objectSize.Left,
                                       objectSize.Top);

    EVector a = EVector(origin, point, 0);
    EVector b = EVector(origin, left, 0);
    
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
    cout << angle << endl;
    return angle;
}

float CalcAngle(EVector v)
{
  float theta = atan2(v.origin.y - v.final.y, v.origin.x - v.final.x);
  return theta * (180 / M_PI);
}

float inverse(float num)
{
  if (num > 0)
    return 0 - num;
  else
    return abs(num);
}
