#include <stdio.h>
#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "nlohmann/json.hpp"
#include "game1/animations.hpp"

using json = nlohmann::json;

struct Frame
{
    int x, y, w, h;
};

struct FrameData
{
    Frame frame;
    std::string filename;
    int duration;
};

struct SpriteSheet
{
    std::vector<FrameData> frames;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Frame, x, y, w, h);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FrameData, frame, filename, duration);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpriteSheet, frames);

int main()
{
    sf::RenderWindow window(sf::VideoMode({400, 400}), "Game 1");

    std::ifstream file("./alucard.json");
    SpriteSheet alucardIdle = json::parse(file).get<SpriteSheet>();

    int x = 0;
    int y = 0;
    int width = 27;
    int height = 48;
    int spriteFrame = 5;
    int currentFrame = 0;
    float elapsedTime = 0.0f;
    float frameTime = 0.1f; // 10 frames per second
    bool isKeyPressed = false;

    sf::Texture texture("./image.png");
    sf::Texture bmoTexture("./bmo.png");

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({x, y}, {width, height}));
    sprite.setScale({5.0f, 5.0f});

    // game clock
    sf::Clock clock;

    int animationCycleCount = 0;

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if(isKeyPressed == false)
            {
                animate(bmoTexture, sprite);
                isKeyPressed = true;
            }
        }
        else
        {
            isKeyPressed = false;
        }


        elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= frameTime)
        {
            elapsedTime = 0.0f;

            currentFrame = (currentFrame + 1) % alucardIdle.frames.size();
            Frame frame = alucardIdle.frames[currentFrame].frame;
            sprite.setTextureRect(sf::IntRect({frame.x, frame.y}, {frame.w, frame.h}));

            if(currentFrame == alucardIdle.frames.size() - 1)
            {
                animationCycleCount++;
            }

            if(animationCycleCount == 4)
            {
                sprite.setTexture(bmoTexture);
            }
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}


