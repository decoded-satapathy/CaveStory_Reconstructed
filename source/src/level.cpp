#include "../headers/level.h"

#include "../headers/graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics)
    : _mapName(mapName), _spawnPoint(spawnPoint), _size(Vector2()) {
  this->loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics &graphics) {
  this->_backgroundTexture = SDL_CreateTextureFromSurface(
      graphics.getRenderer(),
      graphics.loadImage("../content/background/bkBlue.png"));
  this->_size = Vector2(1280, 960); // Whole map size including the stuff which
                                    // isn't currently on screen
}

void Level::update(int elapsedTime) {}

void Level::draw(Graphics &graphics) {
  // Draw the rectangle
  SDL_Rect sourceRect = {0, 0, 64, 64};
  SDL_Rect destRect;

  for (int x = 0; x < this->_size.x / 64; x++) {
    for (int y = 0; y < this->_size.y / 64; y++) {
      destRect.x = x * 64;
      destRect.y = y * 64;
      destRect.w = 64;
      destRect.h = 64;

      graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
    }
  }
}
