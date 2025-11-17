#include "Entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "spdlog/spdlog.h"
#include "World.hpp"

Entity::Entity() : sprite(defaultTexture)
{
  sprite.setTexture(defaultTexture);
}

void Entity::initialize() {
  if (world == nullptr)
  {
    spdlog::error("entity {} not attached to a world.", name);
    return;
  }

  spdlog::info("initializing {} entity", name);

  //DEBT! debug
  applyTexture();

  sprite.scale(initialScale);

  width = sprite.getGlobalBounds().size.x / PIXELS_PER_METER;
  height = sprite.getGlobalBounds().size.y / PIXELS_PER_METER;

  physicsComponent.createBody(bodyType, { position.x, position.y }, world);

  setupPlayerComponent();
}

void Entity::createBox()
{
  physicsComponent.createBox(width, height, friction);
}

// void Entity::createChain()
// {
//   physicsComponent.createChain();
// }

void Entity::setupPlayerComponent()
{
  spdlog::info("no actions or contexts bound to entity {}", name);
}

void Entity::update(float deltaTime)
{
  // animation handler
  animationComponent.update(deltaTime);

  applyTexture();

  float x = physicsComponent.getPosition().x;
  float y = physicsComponent.getPosition().y;

  sf::Vector2f pos(x * PIXELS_PER_METER, y * PIXELS_PER_METER);
  getSprite().setPosition(pos);
  rectangle.setPosition(pos);

  // update input
  inputContextComponent.handleInput();
}

void Entity::draw(sf::RenderWindow& renderWindow)
{
  sf::Vector2f size = { width * PIXELS_PER_METER, height * PIXELS_PER_METER };

  renderWindow.draw(getSprite());

  b2DebugDraw debugDraw = b2DefaultDebugDraw();
  debugDraw.context = &renderWindow;

  // DEBT! this will be part of the RenderComponent/PhysicsDebugRenderer
  debugDraw.DrawSegmentFcn = [](b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context)
    {
      auto* window = static_cast<sf::RenderWindow*>(context);

      std::array lines =
      {
        sf::Vertex{sf::Vector2f { p1.x * PIXELS_PER_METER, p1.y * PIXELS_PER_METER}, sf::Color::Red},
        sf::Vertex{sf::Vector2f { p2.x * PIXELS_PER_METER, p2.y * PIXELS_PER_METER}, sf::Color::Cyan},
      };

      window->draw(lines.data(), lines.size(), sf::PrimitiveType::Lines);
    };

  debugDraw.DrawSolidPolygonFcn = [](
    b2Transform transform,
    const b2Vec2* vertices,
    int vertexCount,
    float radius,
    b2HexColor color,
    void* context)
    {
      auto* window = static_cast<sf::RenderWindow*>(context);

      std::vector<sf::Vertex> verticeList;

      for (int index = 0; index < vertexCount; index++)
      {
        b2Vec2 worldPosition = transform.p + vertices[index];
        verticeList.emplace_back(
          sf::Vector2f({ worldPosition.x * PIXELS_PER_METER, worldPosition.y * PIXELS_PER_METER }),
          sf::Color::Red
        );
      }

      verticeList.push_back(verticeList.front());

      window->draw(verticeList.data(), verticeList.size(), sf::PrimitiveType::LineStrip);
    };

  debugDraw.drawShapes = true;
  b2World_Draw(world->getPhysicsWorldId(), &debugDraw);
}

std::map<std::string, Entity::CreatorFunc>& Entity::getRegistry()
{
  static std::map<std::string, CreatorFunc> registry;
  return registry;
}

std::unique_ptr<Entity> Entity::create(const std::string& name)
{
  // DEBT! implement getName();
  auto it = getRegistry().find(name);
  if (it == getRegistry().end()) return nullptr;

  return std::unique_ptr<Entity>(it->second());
}

InputContextComponent& Entity::getInputContextComponent()
{
  return inputContextComponent;
}

AnimationComponent& Entity::getAnimationComponent()
{
  return animationComponent;
}

PhysicsComponent& Entity::getPhysicsComponent()
{
  return physicsComponent;
}

const sf::Vector2f& Entity::getPosition() const { return position; }

sf::Sprite& Entity::getSprite() { return sprite; }
const sf::Sprite& Entity::getSprite() const { return sprite; }

const World* Entity::getWorld() const
{
  return world;
}

void Entity::setWorld(World* worldPtr)
{
  world = worldPtr;
};

void Entity::addMovementInput(const sf::Vector2f& newPosition)
{

  physicsComponent.setVelocity({ newPosition.x, newPosition.y });
}

void Entity::setPosition(const sf::Vector2f& newPosition)
{
  position = newPosition;

  physicsComponent.setTransform({ newPosition.x, newPosition.y });
}

void Entity::applyTexture()
{
  if (animationComponent.getCurrentTextureId() != lastTextureId)
  {
    sprite.setTexture(animationComponent.getCurrentTexture());
    lastTextureId = animationComponent.getCurrentTextureId();
  }

  if (animationComponent.getCurrentFrameInt() != lastFrameInt)
  {
    sprite.setTextureRect(animationComponent.getCurrentFrameRect());
    lastFrameInt = animationComponent.getCurrentFrameInt();
  }
}

void Entity::setPivotPoint(PivotPoints newPivotPoint)
{
  // if the texture changes during animation, the physics body size needs to be updated.
  // DEBT! getting the box to be the size of the sprite is debug only.
  // default hitbox can be the default sprite size, but client subclasses can override this.

  sf::Vector2f size = sprite.getLocalBounds().size;

  float halfWidth = size.x / 2.f;
  float halfHeight = size.y / 2.f;

  // switch (newPivotPoint)
  // {
  // case PivotPoints::TopLeft: pivotPoint = { 0.0f, 0.0f }; break;
  // case PivotPoints::TopCenter: pivotPoint = { halfWidth, 0.0f }; break;
  // case PivotPoints::CenterCenter: pivotPoint = { halfWidth, halfHeight }; break;
  // case PivotPoints::BottomCenter: pivotPoint = { halfWidth, size.y }; break;
  // }

  std::array<sf::Vector2f, 4> pivots = {
    sf::Vector2f({0.0f, 0.0f}),            // Top Left
    sf::Vector2f({halfWidth, 0.0f}),       // top center
    sf::Vector2f({halfWidth, halfHeight}), // center center
    sf::Vector2f({halfWidth, size.y}),     // bottom center
  };

  if (newPivotPoint < 0 || newPivotPoint >= pivots.size())
  {
    spdlog::error("invalid pivot point on entity {}", name);
    return;
  }

  pivotPoint = pivots[newPivotPoint];
  sprite.setOrigin(pivotPoint);
}
