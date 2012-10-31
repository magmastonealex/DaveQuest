#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"
#include <vector>
#include "load.h"
#include "engine.h"
#include "text.h"

std::vector<SDL_Surface*> allTiles;

SDL_Surface * screen;
SDL_Surface * playerSprite;
SDL_Surface * background;
SDL_Surface * mapSurf;

SDL_Surface * loadSprite(std::string filename){
    SDL_Surface* temptile = SDL_DisplayFormatAlpha(IMG_Load(filename.c_str()));
    SDL_SetAlpha(temptile, SDL_SRCALPHA, 255);
    return temptile;
}
void drawSprite(int x, int y, SDL_Surface* sprite){
			SDL_Rect place;
			place.x = x;
            place.y = y;
            place.w = 32;
            place.h = 32;
			SDL_BlitSurface( sprite, NULL, screen, &place );
}

void flip(){
	SDL_Flip(screen);
}

void clear(){
	SDL_FillRect(screen,NULL, 0x000000); 
}
void initTiles(int numTiles){
	int tileNum = numTiles;
	char filename[11]; //8.3 filenames max
	sprintf(filename, "tiles/%d.png", tileNum );
    SDL_Surface* temptile = SDL_DisplayFormat(IMG_Load(filename));
    allTiles.push_back(temptile);

//}
}
void initTransparentTiles(int tileNum){
	char filename[11]; //8.3 filenames max
	sprintf(filename, "tiles/%d.png", tileNum );
    SDL_Surface* temptile = SDL_DisplayFormatAlpha(IMG_Load(filename));    //
     SDL_SetAlpha(temptile, 0, 255);
	allTiles.push_back(temptile); 
}

void setPlayerSprite(std::string name){
playerSprite = SDL_DisplayFormatAlpha(IMG_Load(name.c_str()));
}

void setBackground(std::string name){
background = SDL_DisplayFormat(IMG_Load(name.c_str()));
}

void initMap(short** map, int mapx, int mapy){
//printf("LenDraw: %d\n", map);
//printf("TestDraw: %d", map[13][10]);
int rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif


    if(mapSurf != NULL) SDL_FreeSurface(mapSurf);
    mapSurf =SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, mapx*32, 768, 32, rmask, gmask, bmask, amask);


		for(int x=0; x<mapx; x++){

		for(int y=0; y<mapy; y++){
			short currentTile  = map[x][y];
			if(currentTile != 0){
			SDL_Surface * surf;
			if(currentTile > 899){
			surf = allTiles[5];
			} else{
			//printf("Tile: %d at %d, %d\n", currentTile-1, x, y);
			surf = allTiles[currentTile-1];
			}
			SDL_Rect place;
			place.x = x*32;
            place.y = y*32;
            place.w = 32;
            place.h = 32; 
			SDL_BlitSurface( surf, NULL, mapSurf, &place );
		//	printf("Tile!\n");
			}
		}
	}
}


void drawMap( int pX, int pY){
SDL_Rect splace;
splace.w = 1024;
splace.h = 768;
splace.x = pX-528;
splace.y = 0;

SDL_Rect destplace;
destplace.x =0;
destplace.y =0;
destplace.w =1024;
destplace.h =768;


SDL_BlitSurface(mapSurf, &splace, screen, &destplace);

}

void drawPlayer(int ply){

	SDL_Rect place;
	place.x = 512;
    place.y = ply;
	SDL_BlitSurface( playerSprite, NULL, screen, &place );

}

void graphicsInit(){
	screen = SDL_SetVideoMode( 1024, 768, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA );
}

void drawBackground(){
	SDL_Rect place;
	place.x = 0;
    place.y = 0;
	SDL_BlitSurface( background, NULL, screen, &place );
}

void drawText(std::string text, int x, int y){
	drawtextutil(text, screen, x, y);
}