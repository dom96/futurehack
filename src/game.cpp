#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <utils.hpp>
#include <maths.hpp>
#include <game.hpp>

using namespace std;

Game::Game() :
  running(false),
  frames(0)
{ 
  const float initialPlayerX = 400.f;
  const float initialPlayerY = 300.f;

  // Create & initialize the window.
  win.Create(sf::VideoMode(800, 600), "Futurehack");
  win.SetFramerateLimit(60);
  
  entityFont.LoadFromFile("resources/Monospace.ttf");
  
  // Init camera
  camera.Reset(sf::FloatRect(0, 0, 800, 600));
  camera.SetCenter(initialPlayerX, initialPlayerY);
  
  // Init drawables
  player = sf::Text("@");
  player.SetFont(entityFont);
  player.SetX(initialPlayerX); player.SetY(initialPlayerY);
  player.SetCharacterSize(14);
  sf::FloatRect playerSize = player.GetRect();
  player.SetOrigin(playerSize.Width / 2, playerSize.Height / 2);
  
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
        float angle = AngleToPoint(player.GetRect(), pos);
        player.SetRotation(angle);
        break;
    }
  }
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
  
  win.Draw(player);

  sf::Shape rect = sf::Shape::Rectangle(360, 260, 10, 10, sf::Color::White);
  win.Draw(rect);
  
  // Camera independent drawing - HUD etc.
  win.SetView(win.GetDefaultView());
  
  win.Draw(fpsText);
}
