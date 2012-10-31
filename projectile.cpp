//Projectiles
#include "load.h"
#include "engine.h"

#include "projectile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "SDL/SDL.h"
#include "draw.h"



std::vector<projectile> allProjectiles;


void addProjectile(projectile toadd){
allProjectiles.push_back(toadd);
}


void updateProjectiles(int delta){
for (unsigned int i=0; i < allProjectiles.size(); i++) {
     allProjectiles[i].startx += allProjectiles[i].speed;
     allProjectiles[i].realx += allProjectiles[i].speed;
     allProjectiles[i].startx -= delta;
} 
}


int collidesProjectiles(int thisX, int thisY){
for (unsigned int i=0; i < allProjectiles.size(); i++) {
    SDL_Rect a;
    a.x = allProjectiles[i].realx;
    a.y = allProjectiles[i].starty;

    a.w = 32;
    a.h = 32;

    SDL_Rect b;
    b.x = thisX;
    b.y = thisY;
    b.w = 32;
    b.h = 32;

	if(b.x + b.w < a.x)	continue;	//just checking if their
	if(b.x > a.x + a.w)	continue;	//bounding boxes even touch

	if(b.y + b.h < a.y)	continue;
	if(b.y > a.y + a.h)	continue;


    allProjectiles.erase(allProjectiles.begin()+i);
	return 1;				//bounding boxes intersect
}
	return 0;
}

void drawProjectiles(){
for (unsigned int i=0; i < allProjectiles.size(); i++) {
     drawSprite(allProjectiles[i].startx, allProjectiles[i].starty, allProjectiles[i].sprite);
} 
}