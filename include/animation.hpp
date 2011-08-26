#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SFML/Graphics.hpp>
#include <vector>


class AnimatedSprite : public sf::Sprite {
public:
  AnimatedSprite();
  void Animate();
  void Update();
  void AddFrame(sf::IntRect frame);
  void SetFrame(int frame);

  unsigned int offset; // Time between frame switch in miliseconds.
  unsigned int timeout; // Time to wait until animation is stopped.
  // A frame is a subrect of the sprite's texture
  std::vector<sf::IntRect> frames;

private:


  sf::Clock animTimer;
  sf::Clock timeoutTimer;
  int currentFrame;
};


#endif
