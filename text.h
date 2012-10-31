#include <string>
#include "SDL/SDL.h"

void initFonts(std::string fontName, int size);
void drawtextutil(std::string text, SDL_Surface *surfDraw, int x, int y);
void changeFont(std::string fontName, int size);