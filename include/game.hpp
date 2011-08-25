#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <world.hpp>
#include <maths.hpp>

struct Player {
  Player();
  void Load(sf::Texture &entities);
  void MouseInput(sf::Vector2f cursor);
  void CheckInput(sf::RenderWindow &win, bool focused);
  void Move(float x, float y);
  sf::Vector2f CalculateMove(float dir, float speed, float frametime);

  EVector mouse; // Vector from the middle of player to the mouse position.
  sf::Sprite sp;
};

struct Game {
  Game();
  ~Game();
  
  int Run(); // Returns the application's exit code.
private:
  void CheckEvents();
  void Update();
  void Draw();

  sf::RenderWindow win;
  bool winFocused; // Whether the window is focused.
  sf::View camera;
  sf::Clock fpsClock; // Clock for measuring FPS.
  int frames; // A counter of frames rendered.
  sf::Font entityFont; // Font used for entities: player, enemies etc.
  sf::Texture entities; // Entities texture
  Player player;
  sf::Text fpsText;
  bool running;
  World world;
};



#endif // GAME_HPP
