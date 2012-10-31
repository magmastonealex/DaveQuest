#include "SDL/SDL.h"
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define false 0
#define true 1

struct projectile {
SDL_Surface * sprite;
int startx;
int starty;
int realx;
short dir;
int speed;

} ;

void addProjectile(projectile toadd);
void updateProjectiles(int pxdelta);
void drawProjectiles();
int collidesProjectiles(int X, int Y);