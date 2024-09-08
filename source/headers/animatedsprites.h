#ifndef ANIMATEDSPRITES_H
#define ANIMATEDSPRITES_H

#include "globals.h"
#include "sprite.h"
#include <SDL2/SDL_rect.h>
#include <map>
#include <string>
#include <vector>

class Graphics;

/* AnimatedSprites class
 * Holds logic for animating spirites
 */

class AnimatedSprites : public Sprite {
public:
  AnimatedSprites();

  AnimatedSprites(Graphics &graphics, const std::string &filePath, int sourceX,
                  int sourceY, int width, int height, float posX, float posY,
                  float timeUpdate);

  /* void playAnimation()
   * Plays the animation provided if it's not playing already
   */
  void playAnimation(std::string animation, bool once = false);

  /* void update
   * Updates the animated sprite (with a timer)
   */
  void update(int elapsedTime);

  /* void draw
   * Draws the sprite to the screen
   */
  void draw(Graphics &graphics, int x, int y);

protected:
  double _timeToUpdate;
  bool _currentAnimationOnce;
  std::string _currentAnimation;

  /* void addAnimation
   * Adds an animation to the map of animations for the sprite
   */
  void addAnimation(int frames, int x, int y, std::string name, int width,
                    int height, Vector2 offset);

  /* void resetAnimations
   * Resets all animations associated with this sprite
   */
  void resetAnimations();

  /* void stopAnimation
   * Stops the current animation
   */
  void stopAnimation();

  /* void setVisible
   * Changes the visiblity of the animated sprite
   */
  void setVisible(bool visible);

  /* virtual void animationDone
   * Logic that happens when an animation ends
   */
  virtual void animationDone(std::string currentAnimation) = 0;

  /* void setupAnimations
   * A Required functions that sets up all animations for a sprite
   */

  virtual void setupAnimation() = 0;

private:
  std::map<std::string, std::vector<SDL_Rect>> _animations;
  std::map<std::string, Vector2> _offsets;

  int _frameIndex;
  double _timeElapsed;
  bool _visible;
};

#endif // !ANIMATEDSPRITES_H
