#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "spriteSheet.hpp"

void animate(const sf::Texture& texture, const SpriteSheet& spriteSheet, sf::Sprite& sprite);