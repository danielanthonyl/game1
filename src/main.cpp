#include <stdio.h>
#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "nlohmann/json.hpp"
#include "animations.hpp"
#include "spriteSheet.hpp"
#include "SpriteAnimator.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode({400, 400}), "Game 1");

  std::ifstream idleFile("./crow_idle.json");
  std::ifstream run2File("./crow_walk.json");

  SpriteSheet idleData = json::parse(idleFile).get<SpriteSheet>();
  SpriteSheet run2Data = json::parse(run2File).get<SpriteSheet>();

  sf::Texture idleTexture("./crow_idle.png");
  sf::Texture run2Texture("./crow_walk.png");

  bool isKeyPressed = false;

  SpriteAnimator animator;
  animator.add(idleTexture, idleData, State::IDLE);
  animator.add(run2Texture, run2Data, State::RUNNING);
  animator.play(State::IDLE);

  sf::Clock clock;

  while (window.isOpen())
  {

    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
      if (isKeyPressed == false)
      {
        if (animator.getState() != State::RUNNING)
        {
          animator.play(State::RUNNING);
        }

        isKeyPressed = true;
      }
    }
    else
    {
      if (isKeyPressed == true)
      {
        if (animator.getState() != State::IDLE)
        {
          animator.play(State::IDLE);
        }
      }

      isKeyPressed = false;
    }

    float deltaTime = clock.restart().asSeconds();
    animator.update(deltaTime);

    window.clear(sf::Color::White);
    window.draw(animator.getSprite());
    window.display();
  }

  return 0;
}
