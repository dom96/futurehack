#include <SFML/Graphics.hpp>
#include <iostream>
#include <maths.hpp>
#include <cmath>
#include <cassert>

using namespace std;

int main()
{
  EVector a = EVector(sf::Vector2f(0, 0), sf::Vector2f(2, 3), sf::Vector2f(1, 1));
  float norm = euclideanNorm(a);
  float product = dotProduct(a, a);
  float s = sqrt(product);
  cout << norm << endl;
  cout << s << endl;
  cout << product << endl;
  assert(norm == s);
  
}
