#include "SDL/SDL.h"

#define JUMPING 0 //Enemy that jumps every X frames
#define ROAMING 1 // Enemy that goes back and forth along a platform
#define SHOOTING 2 // Enemy that stands still, but constantly shoots in the direction of the player

//Enemy struct
struct Enemy
{
	SDL_Surface * sprite;
	int X;
	int Y;
	int screenX;
	int screenY;
	char type;
	SDL_Surface * bulletSprite;
	char onGround;
	short gravity;
	short gravResist;
	short delay;
	char movingRight;
	char speed;
};

void updateEnemies(int pDelta, short** themap);
void drawEnemies();
void deleteEnemies();
void addEnemies(Enemy newEnemy);
int collidesEnemies(int thisX, int thisY);