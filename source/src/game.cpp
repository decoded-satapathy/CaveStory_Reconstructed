#include "../headers/game.h"
#include "../headers/graphics.h"
#include "../headers/input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>

namespace {
const int FPS = 50;
const int MAX_FRAME_TIME = 5 * 1000 / FPS;
} // namespace

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  this->gameLoop();
}
Game::~Game() {}
void Game::gameLoop() {
  Input input;
  Graphics graphics;
  SDL_Event event;

  this->_player = Player(graphics, 100, 100);
  this->_level = Level("map 1", Vector2(100, 100), graphics);

  int LAST_UPDATE_TIME = SDL_GetTicks();

  while (true) {
    input.beginNewFrame();
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        if (event.key.repeat == 0) {
          input.keyDownEvent(event);
        }
      } else if (event.type == SDL_KEYUP) {
        input.keyUpEvent(event);
      } else if (event.type == SDL_QUIT) {
        return;
      }
    }

    if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
      return;
    } else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
      this->_player.moveLeft();
    } else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
      this->_player.moveRight();
    }

    if (!input.isKeyHeld(SDL_SCANCODE_LEFT) &&
        !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
      this->_player.stopMoving();
    }

    const int CURRENT_TIME_MS = SDL_GetTicks();
    int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
    this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
    LAST_UPDATE_TIME = CURRENT_TIME_MS;

    this->draw(graphics);
  }
}
void Game::draw(Graphics &graphics) {
  graphics.clear();

  this->_level.draw(graphics);
  this->_player.draw(graphics);

  graphics.flip();
}
void Game::update(float elapsedTime) {
  this->_player.update(elapsedTime);
  this->_level.update(elapsedTime);
}
