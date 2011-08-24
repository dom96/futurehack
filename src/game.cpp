#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <utils.hpp>
#include <maths.hpp>
#include <game.hpp>

using namespace std;
const float initialPlayerX = 400.f;
const float initialPlayerY = 300.f;

Game::Game() :
  running(false),
  frames(0)
{ 

  // Create & initialize the window.
  win.Create(sf::VideoMode(800, 600), "Futurehack",
             sf::Style::Close | sf::Style::Titlebar);
  win.SetFramerateLimit(60);

  entityFont.LoadFromFile("resources/Monospace.ttf");
  
  // Init camera
  camera.Reset(sf::FloatRect(0, 0, 800, 600));
  camera.SetCenter(initialPlayerX, initialPlayerY);
  
  entities.LoadFromFile("resources/entities.png");
  entities.SetSmooth(true);
  
  // Init drawables
  player.Load(entities);
    
  fpsText = sf::Text("");
  fpsText.SetX(5.f); fpsText.SetY(5.f);
  fpsText.SetCharacterSize(16);
  fpsText.SetColor(sf::Color(0, 75, 122, 255));
}

Game::~Game()
{
  win.Close();
}

int Game::Run()
{
  running = true;
  while (running && win.IsOpened())
  {
    win.Clear();
    
    CheckEvents();
    
    Update();
    
    Draw();
    
    win.Display();
  }
  
  return EXIT_SUCCESS;
}

void Game::CheckEvents()
{
  sf::Event event;
  while (win.PollEvent(event))
  {
    switch (event.Type) {
      case sf::Event::Closed:
        running = false;
        break;
      case sf::Event::MouseMoved:
        sf::Vector2f pos = sf::Vector2f(event.MouseMove.X,
                                        event.MouseMove.Y);
        player.MouseInput(pos);
        break; 
    }
  }
  player.CheckInput(win);
  camera.SetCenter(player.sp.GetPosition());
}

void Game::Update()
{
  // If one second has passed, change the FPS text.
  if (fpsClock.GetElapsedTime() >= 1000)
  {
    fpsText.SetString(itos(frames) + " FPS");
    frames = 0;
    fpsClock.Reset();
  }
  
  frames++;
  
  world.Update();
}

void Game::Draw()
{
  win.SetView(camera);
  
  sf::Sprite mapSprite(world.mapTexture.GetTexture());
  mapSprite.SetPosition(0, 0);
  win.Draw(mapSprite);
  
  win.Draw(player.sp);
  
  // Camera independent drawing - HUD etc.
  win.SetView(win.GetDefaultView());
  
  win.Draw(fpsText);
}

Player::Player() :
  mouse(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0)
{ }

void Player::Load(sf::Texture &entities)
{
  sp.SetTexture(entities);
  sp.SetSubRect(sf::IntRect(3, 3, 64, 64));
  sp.SetX(initialPlayerX); sp.SetY(initialPlayerY);
  mouse.origin.x = initialPlayerX; mouse.origin.y = initialPlayerY;
  //sf::FloatRect playerSize = player.GetRect();
  sp.SetOrigin(32, 32);
}

void Player::MouseInput(sf::Vector2f cursor)
{
  mouse.final = cursor;
  mouse.CalcDir();
  
  float angle = CalcAngle(mouse);
  sp.SetRotation(angle);
}

void Player::CheckInput(sf::RenderWindow &win)
{

  float multiplier = 110 * (win.GetFrameTime() / 1000.f);
  float xaxis = multiplier * cos(mouse.direction);
  float yaxis = multiplier * sin(mouse.direction);

  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::W))
  {
    Move(xaxis, yaxis);
  }
}

void Player::Move(float x, float y)
{
  sp.Move(x, y);
  //mouse.origin.x += x;
  //mouse.origin.y += y;
}
