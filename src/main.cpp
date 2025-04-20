#include <stdio.h>

#include <fstream>
#include <iostream>

#include "AnimationData.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SpriteAnimator.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
  sf::RenderWindow window(sf::VideoMode({400, 400}), "Game 1");

  std::ifstream idleFile("./idle.json");
  std::ifstream run2File("./running.json");

  Animation::TextureData idleData =
      json::parse(idleFile).get<Animation::TextureData>();
  Animation::TextureData run2Data =
      json::parse(run2File).get<Animation::TextureData>();

  sf::Texture idleTexture("./idle.png");
  sf::Texture run2Texture("./running.png");

  bool isKeyPressed = false;

  SpriteAnimator animator;
  animator.add(idleTexture, idleData, State::IDLE, 6);
  animator.add(run2Texture, run2Data, State::RUNNING);
  animator.play(State::IDLE);

  sf::Clock clock;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      if (isKeyPressed == false) {
        if (animator.getState() != State::RUNNING) {
          animator.play(State::RUNNING);
        }

        isKeyPressed = true;
      }
    } else {
      if (isKeyPressed == true) {
        if (animator.getState() != State::IDLE) {
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
