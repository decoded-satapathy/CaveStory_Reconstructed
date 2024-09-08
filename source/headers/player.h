#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprites.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprites {
public:
  Player();
  Player(Graphics &graphics, float x, float y);
  void draw(Graphics &graphics);
  void update(float elapsedTime);

  virtual void animationDone(std::string currentAnimation);
  virtual void setupAnimation();

  /* void moveLeft()
   * Moves the player by -dx (negative dx means in left direction)
   */
  void moveLeft();

  /* void moveRight()
   * Moves the player by dx (positive dx means in right direction)
   */
  void moveRight();

  /* void stopMoving()
   * Stops the movement of the character and it faces it's last moved direction
   */
  void stopMoving();

private:
  float _dx, _dy; // change in the x direction and change in y direction

  Direction _facing;
};

#endif // !PLAYER_H
