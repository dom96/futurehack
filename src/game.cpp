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
  player(this)
{ 
  running = false;
  frames = 0;
  winFocused = true;

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
     
    Update();
    
    Draw();
   
    CheckEvents();
    
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
      case sf::Event::LostFocus:
        winFocused = false;
        break;
      case sf::Event::GainedFocus:
        winFocused = true;
        break;
      case sf::Event::MouseMoved:
        sf::Vector2f pos = sf::Vector2f(event.MouseMove.X,
                                        event.MouseMove.Y);
        player.MouseInput(pos);
        break; 
    }
  }
  player.CheckInput(winFocused);
  camera.SetCenter(player.sp.GetPosition());
  //camera.SetRotation(player.sp.GetRotation());
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
  player.Update();
}

void Game::Draw()
{
  win.SetView(camera);
  
  world.Draw(win);

  win.Draw(player.sp);
  
  // Camera independent drawing - HUD etc.
  win.SetView(win.GetDefaultView());
  
  win.Draw(fpsText);
}

Player::Player(Game *refGame) :
  mouse(sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0),
  game(refGame)
{ }

void Player::Load(sf::Texture &entities)
{
  sp.SetTexture(entities);
  // Add animation frames.
  sp.AddFrame(sf::IntRect(3, 3, 64, 64)); // Default frame
  sp.AddFrame(sf::IntRect(71, 3, 64, 64));
  sp.AddFrame(sf::IntRect(139, 3, 64, 64));
  sp.SetFrame(0);

  sp.SetX(initialPlayerX); sp.SetY(initialPlayerY);
  mouse.origin.x = initialPlayerX; mouse.origin.y = initialPlayerY;
  sp.SetOrigin(32, 32);
}

void Player::MouseInput(sf::Vector2f cursor)
{
  mouse.final = cursor;
  mouse.CalcDir();
  
  float angle = CalcAngle(mouse);
  sp.SetRotation(angle);
}

sf::Vector2f Player::CalculateMove(float dir, float speed, float frametime)
{
  float multiplier = speed * (frametime / 1000.f);
  float xaxis = multiplier * cos(dir);
  float yaxis = multiplier * sin(dir);
  return sf::Vector2f(xaxis, yaxis);
}

void Player::CheckInput(bool focused)
{
  if (focused) 
  {
    float dir = -1.57079633;
    float frametime = game->win.GetFrameTime();

    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::W))
    {
      sf::Vector2f moveBy = CalculateMove(dir, 210, frametime);
      sp.Animate();
      Move(moveBy.x, moveBy.y);
    }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::S))
    {
      sf::Vector2f moveBy = CalculateMove(+dir, 210, frametime); 
      sp.Animate();
      Move(-moveBy.x, -moveBy.y);
    }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A))
    {
      // Don't allow moving left and right at the same time.
      if (sf::Keyboard::IsKeyPressed(sf::Keyboard::D)) return;
      dir -= 1.57079633; // 90 degrees.
      sf::Vector2f moveBy = CalculateMove(dir, 210, frametime);
      sp.Animate();
      Move(moveBy.x, moveBy.y);
    }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::D))
    {
      dir += 1.57079633;
      sf::Vector2f moveBy = CalculateMove(dir, 210, frametime);
      sp.Animate();
      Move(moveBy.x, moveBy.y);
    }
  }
}

void Player::Move(float x, float y)
{
  cout << x << " " << y << endl;
  sf::Vector2f curPos = sp.GetPosition();
  sf::Vector2f curCenter = sp.GetOrigin();
  sf::Vector2f curSize = sp.GetSize();
  sf::FloatRect rect(curPos.x + x - (curCenter.x / 2), 
                     curPos.y + y - (curCenter.y / 2),
                     64, 64);
  if (!game->world.CollidesWith(TileWall, rect))
  {
    sp.Move(x, y);
  }
}

void Player::Update()
{
  sp.Update(); // Check if animation should be stopped.
}
