#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <string>

class Graphics;
struct SDL_Texture;

class Level {
public:
  Level();
  Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);

  void update(int elapsedTime);
  void draw(Graphics &graphics);
  ~Level();

private:
  std::string _mapName;
  Vector2 _spawnPoint;
  Vector2 _size; // size of the entire map not just what's being shown currently
  SDL_Texture *_backgroundTexture;

  /* void loadMap
   * Loads a map
   */
  void loadMap(std::string mapName, Graphics &graphics);
};

#endif // !LEVEL_H
