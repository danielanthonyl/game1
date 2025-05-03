#pragma once

class Entity;

class ControllerComponent
{
 public:
  void handleInput(Entity& entity);
};