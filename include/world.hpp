#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>

#include <level.hpp>

const int maxLevels = 26;

struct Game;

struct World {
  World(Game *refGame);
  ~World();
  
  void Update();
  void DrawMap();
  void Draw(sf::RenderWindow &win);
  bool CollidesWith(TileType tile, sf::FloatRect rect);
private:
  int currentLevel;
  int seedUsed;
  
  sf::RenderTexture mapTexture;
  
  Level* levels; // Initialized at runtime.
  // Monsters should <del>not</del> be separated per level.

  Game *game; // Useful for debugging. 
};

#endif // WORLD_HPP
