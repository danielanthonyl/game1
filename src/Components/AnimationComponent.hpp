#pragma once

#include <functional>
#include <map>
#include <string>

#include "../AnimationData.hpp"
#include "../ResourceManager.hpp"

class AnimationComponent
{
 public:
  AnimationComponent();

  struct StandbyConfig
  {
    int cyclesBeforeStandby = 0;
    size_t standbyFrame = 0;
    std::function<void()> onEnterStandby = nullptr;
  };

  struct TextureConfig
  {
    std::string textureId;
    const sf::Texture *texture = nullptr;
    const Animation::TextureData *textureData = nullptr;
    StandbyConfig standby;
    float frameTime = 0.01f;
  };

  void addAnimation(const std::string& textureId);

  /**
   * @brief Add an animation
   *
   * DEBT! when we can export aseprite json data with
   *       standby, timing and other configs we can remove
   *       a ton of properties from this function
   *
   * @param textureId Unique identifier for the animation
   * @param texture Pointer to the texture
   * @param textureData Pointer to the sprite sheet data
   * @param cycles Number of cycles before entering standby (0 = never)
   * @param standbyFrame Frame to display in standby mode
   * @param frameTime Time between frames in seconds
   * @param onEnterStandby Callback when entering standby mode
   */
  void addAnimation(const std::string &textureId, const sf::Texture *texture,
                    const Animation::TextureData *textureData,
                    const int cycles = 0, const int standbyFrame = 0,
                    const float frameTime = 0.1f,
                    std::function<void()> onEnterStandby = nullptr);

  void play(std::string textureId);
  void update(float deltaTime);
  void updateStandbyState();

  void setAnimation(const std::string textureId);

  const sf::Texture &getCurrentTexture();
  const sf::IntRect getCurrentFrameRect() const;

  std::string getCurrentAnimationId() const;

 private:
  void updateFrame();

  ResourceManager& resourceManager;
  std::map<std::string, TextureConfig> textures;
  std::string currentTextureId;
  size_t currentFrame;
  float elapsedTime;
  bool inStandbyMode;
  int animationCycleCount;
};
