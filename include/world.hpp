#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>

#include <level.hpp>

const int maxLevels = 26;

struct World {
  World();
  ~World();
  
  void Update();
  void DrawMap();
  void Draw(sf::RenderWindow &win);
private:
  int currentLevel;
  int seedUsed;
  
  sf::RenderTexture mapTexture;
  
  Level* levels; // Initialized at runtime.
  // Monsters should <del>not</del> be separated per level.
};

#endif // WORLD_HPP
