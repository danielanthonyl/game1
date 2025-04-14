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

  std::ifstream idleFile("./alucard.json");
  std::ifstream run2File("./run2.json");

  SpriteSheet idleData = json::parse(idleFile).get<SpriteSheet>();
  SpriteSheet run2Data = json::parse(run2File).get<SpriteSheet>();

  sf::Texture idleTexture("./image.png");
  sf::Texture bmoTexture("./bmo.png");
  sf::Texture run2Texture("./run2.png");

  int x = 0;
  int y = 0;
  int width = 27;
  int height = 48;
  // int spriteFrame = 5;
  // int currentFrame = 0;
  // float elapsedTime = 0.0f;
  // float frameTime = 0.1f; // 10 frames per second
  bool isKeyPressed = false;

  // SpriteSheet data = idleData;
  // sf::Texture texture = idleTexture;

  sf::Sprite sprite(idleTexture);
  sprite.setTextureRect(sf::IntRect({x, y}, {width, height}));
  sprite.setScale({5.0f, 5.0f});

  SpriteAnimator animator(sprite);
  animator.add(idleTexture, idleData, State::IDLE, 6);
  animator.add(run2Texture, run2Data, State::RUNNING);
  animator.play(State::IDLE);

  // animator.configureStandby(State::IDLE, 6, 0);

  // game clocstd::cout << "bbbb" << std::endl;k
  sf::Clock clock;

  // int animationCycleCount = 0;

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
          // animationCycleCount = 0;
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
    window.draw(sprite);
    window.display();
  }

  return 0;
}
