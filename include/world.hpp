#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>

#include <level.hpp>

struct World {
  World(int seed = -1);
  ~World();
  
  void Update();
  void DrawMap();
private:
  int currentLevel;
  int maxLevels;
  int seedUsed;
  
  sf::RenderTexture mapTexture;
  
  Level* levels; // Initialized at runtime.
  // Monsters should <del>not</del> be separated per level.
};

#endif // WORLD_HPP
