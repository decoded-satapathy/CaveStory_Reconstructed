#include "../headers/animatedsprites.h"
#include "../headers/graphics.h"
#include "../headers/sprite.h"
#include <SDL2/SDL_rect.h>

/* AnimatedSprite Class
 * Animates our sprites
 */

AnimatedSprites::AnimatedSprites() {}

AnimatedSprites::AnimatedSprites(Graphics &graphcis,
                                 const std::string &filepath, int sourceX,
                                 int sourceY, int width, int height, float posX,
                                 float posY, float timeToUpdate)
    : Sprite(graphcis, filepath, sourceX, sourceY, width, height, posX, posY),
      _frameIndex(0), _timeToUpdate(timeToUpdate), _visible(true),
      _currentAnimationOnce(false), _currentAnimation("") {}

void AnimatedSprites::addAnimation(int frames, int x, int y, std::string name,
                                   int width, int height, Vector2 offset) {

  std::vector<SDL_Rect> rectangles;
  for (int i = 0; i < frames; i++) {
    SDL_Rect newRect = {(i + x) * width, y, width, height};
    rectangles.push_back(newRect);
  }
  this->_animations.insert(
      std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
  this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprites::resetAnimations() {
  this->_animations.clear();
  this->_animations.clear();
}

void AnimatedSprites::playAnimation(std::string animation, bool once) {
  this->_currentAnimationOnce = once;
  if (this->_currentAnimation != animation) {
    this->_currentAnimation = animation;
    this->_frameIndex = 0;
  }
}

void AnimatedSprites::setVisible(bool visible) { this->_visible = visible; }

void AnimatedSprites::stopAnimation() {
  this->_frameIndex = 0;
  this->animationDone(this->_currentAnimation);
}

void AnimatedSprites::update(int elapsedTime) {
  Sprite::update();
  this->_timeElapsed += elapsedTime;

  if (this->_timeElapsed > this->_timeToUpdate) {
    this->_timeElapsed -= this->_timeToUpdate;
    if (this->_frameIndex <
        this->_animations[this->_currentAnimation].size() - 1) {
      this->_frameIndex++;
    } else {
      if (this->_currentAnimationOnce == true) {
        this->setVisible(false);
      }
      this->_frameIndex = 0;
      this->animationDone(this->_currentAnimation);
    }
  }
}

void AnimatedSprites::draw(Graphics &graphics, int x, int y) {
  if (this->_visible) {
    SDL_Rect destinationRectangle;
    destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
    destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
    destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
    destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

    SDL_Rect sourceRect =
        this->_animations[this->_currentAnimation][this->_frameIndex];
    graphics.blitSurface(this->_spriteSheet, &sourceRect,
                         &destinationRectangle);
  }
}
