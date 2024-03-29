#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <world.hpp>
#include <maths.hpp>
#include <animation.hpp>

struct Game;

struct Player {
  Player(Game *refGame);
  void Load(sf::Texture &entities);
  void MouseInput(sf::Vector2f cursor);
  void CheckInput(bool focused);
  void Move(float x, float y);
  sf::Vector2f CalculateMove(float dir, float speed, float frametime);
  void Update();

  EVector mouse; // Vector from the middle of player to the mouse position.
  AnimatedSprite sp;
  
  Game *game;
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
  friend struct Player;
  Player player;
  sf::Text fpsText;
  bool running;
  friend struct World;
  World world;

  bool debug;
};



#endif // GAME_HPP
