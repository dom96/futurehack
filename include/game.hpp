#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <world.hpp>

struct Game {
  Game();
  ~Game();
  
  int Run(); // Returns the application's exit code.
private:
  void CheckEvents();
  void Update();
  void Draw();

  sf::RenderWindow win;
  sf::View camera;
  sf::Clock fpsClock; // Clock for measuring FPS.
  int frames; // A counter of frames rendered.
  sf::Font entityFont; // Font used for entities: player, enemies etc.
  sf::Text player; // TODO: Make this a struct when we need to store more info.
  sf::Text fpsText;
  bool running;
  World world;
};


#endif // GAME_HPP
