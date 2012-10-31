#include "SDL/SDL.h"
#include <string>
void initTiles(int numTiles);
void setPlayerSprite(std::string name);
void setBackground(std::string name);
void initMap(short** map, int mapx, int mapy);
void drawMap( int pX, int pY);
void drawPlayer(int ply);
void graphicsInit();
void drawBackground();
void flip();
void clear();
void initTransparentTiles(int tileNum);
SDL_Surface * loadSprite(std::string filename);
void drawSprite(int x, int y, SDL_Surface* sprite);
void drawText(std::string text, int x, int y);