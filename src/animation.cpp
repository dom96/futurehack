#include <SFML/Graphics.hpp>

#include <cassert>

#include <animation.hpp>

void AnimatedSprite::SetFrame(int frame)
{
  currentFrame = frame;
  
  SetSubRect(frames[currentFrame]);
}

AnimatedSprite::AnimatedSprite()
{
  currentFrame = -1;
  offset = 250;
  timeout = 100;
}

/* This function will not use the first frame.
   It only cycles through 1 to ``size``. */
void AnimatedSprite::Animate()
{
  assert(frames.size() > 1);
  timeoutTimer.Reset();
  unsigned int nextFrame = currentFrame + 1;
  if (nextFrame >= frames.size())
    nextFrame = 1;
  
  if (animTimer.GetElapsedTime() >= offset)
  {
    SetFrame(nextFrame);
    animTimer.Reset();
  }
}

void AnimatedSprite::Update()
{
  if (timeoutTimer.GetElapsedTime() >= timeout)
  {
    SetFrame(0);
    timeoutTimer.Reset();
  }
}

void AnimatedSprite::AddFrame(sf::IntRect frame)
{
  frames.push_back(frame);
  if (currentFrame == -1) currentFrame = 1;
}
