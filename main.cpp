#include <string.h>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "SDL/SDL.h"
#include "load.h"
#include "engine.h"
#include "draw.h"
#include "text.h"
#include "savefiles.h"
#include "projectile.h"
#include "enemy.h"

#define TRUE 1
#define FALSE 0

int main(int , char **);
std::vector<std::string> doorVecMain;
short** themap;
short TICK_INTERVAL = 10;
short should_stop = 0;
int pX = 512;
int pY = 32;
int stop = FALSE;
int grav = 0;
int onGround = 0;
int goingRight = 0;
int goingLeft = 0;
int gravoverride = 0;
int currScore = 0;
std::string currName;
static Uint32 next_time;
int delayShoot = 20;

std::string IntToString(int number, std::string precText){
   std::stringstream ss;
   ss << precText;
   ss << number;
   return ss.str();
}

void draw(){
    clear();
    drawBackground();
    drawMap(pX, 0);
    drawPlayer(704-pY);
    drawProjectiles();
    drawEnemies();
    changeFont("FreeMonoBold.ttf", 16);
    drawText(IntToString(currScore, "Score: "), 0,0);
    flip();
}
int deathIndex = 0;
void drawDeath(){
    clear();
    drawBackground();
    drawMap(pX, 0);
    drawPlayer(704-pY);
    drawProjectiles();
    drawEnemies();
    changeFont("FreeMonoBold.ttf", 30);
    drawText("You DIED!", 480,384);
    flip();
}

void drawMenu(int index){
    clear();
    drawBackground();
    SDL_Surface * loadOption = loadSprite("loadOp.png");
    SDL_Surface * quitOption = loadSprite("quitOp.png");
    SDL_Surface * pointerIcon = loadSprite("player.png");
    drawSprite(512, 300, loadOption);
    //drawSprite(512, 330, loadOption);
    drawSprite(512, 330, quitOption);
    drawSprite(489, 300+(index*32), pointerIcon);
    flip();
}

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

int getTileXd(int thex){
//    printf("X: %d\n", thex);
//printf("%d\n", ceil(((float)thex)/32));
return floor(((float)thex)/32);
}
int getTileXu(int thex){
//    printf("X: %d\n", thex);
//printf("%d\n", ceil(((float)thex)/32));
return ceil(((float)thex)/32);
}
int getTileX(int thex){
//printf("X: %d\n", thex);
///printf("%d\n", ceil(((float)thex)/32));
return floor(((float)thex)/32);

}
int getTileY(int they){
return 22-ceil(they/32);
//printf("Y: %d\n", tileY);
}


void die(){
drawDeath();

SDL_Delay(1500);

for(int i = 0; i < 30; i++){
  pY += 8;
  drawDeath();
}
for(int i = 0; i< 5; i++){
  pY +=5;
  drawDeath();
}
for(int i = 0; i <5; i++){
 pY += 4;
 drawDeath();
}

  
deleteEnemies();

free(themap);
themap = getMap("map.txt", 100,24);
  if(fileExists("map.txt.save")){
    short xy[2];
    int testing123 = 0xBEEF;
    printf("TestLoc: %d\n", &testing123);
    printf("XYLoc: %d\n",xy);;
    loadSave("map.txt.save", xy);
    
    pX = xy[0];
    pY = xy[1];
  }else{
    
   pX = 512;
   pY = 32;
  }
  doorVecMain.clear();
  
  doorVecMain = getDoors();
  
  updateEnemies(pX-512, themap);
  initMap(themap, 100,24);
}


int isnotcollide(int tilenum,int x, int y){
  if(tilenum > 899){
  printf("Door %d\n", tilenum-900);
  printf("DoorName: %s\n", doorVecMain[tilenum-900].c_str());
  printf("Changing levels!\n");
  deleteEnemies();
  saveFile(currName+".save", pX, pY);
//  printf("Tile delta: %d, %d", pX-512, pY-32);
  free(themap);
  themap = getMap(doorVecMain[tilenum-900], 100,24);
  printf("pos: %d\n", themap);
  currName = doorVecMain[tilenum-900];
  
  if(fileExists((doorVecMain[tilenum-900]+".save").c_str())){
    short xy[2];
    loadSave(doorVecMain[tilenum-900]+".save", xy);
    printf("Loaded: %d, %d", xy[0], xy[1]);
  // pX = 512;
    pX = xy[0];
  // pY = 32;
    pY = xy[1];
  
  }else{
    printf("Did not load\n");
   pX = 512;
   pY = 32;
  }
  doorVecMain.clear();
  doorVecMain = getDoors();
  updateEnemies(pX-512, themap);
  initMap(themap, 100,24);
    return 1;
  }
  if(tilenum == 3){
    die();
   // should_stop = TRUE;
  }
  if(tilenum == 9){
    themap[x][y] = 0;
    currScore++;
   // printf("Token: %d, %d, changed to %d\n", x, y, themap[x][y]);
    initMap(themap, 100,24);
  }

  return 0;
}

void gravityCalc(){
if(themap[getTileX(pX)][getTileY(pY-grav)] != 0){
//printf("On Ground?\n");
onGround = 1;
}else{
onGround = 0;
}
if(themap[getTileX(pX)][getTileY(pY-grav)] == 3){
//  should_stop = TRUE;
  die();
}
if(themap[getTileX(pX)][getTileY(pY-grav)] == 9){
    themap[getTileX(pX)][getTileY(pY-grav)] = 0;
    currScore++;
   // printf("Token: %d, %d, changed to %d\n", x, y, themap[x][y]);
    initMap(themap, 100,24);
}
if(gravoverride == 0){
if(grav <= 5){
    grav++;
}

}else{
    gravoverride--;
}

if(onGround == FALSE){
 pY -= grav;
}

}

void fire(){
if(delayShoot == 0){
    projectile proj;
    proj.sprite = loadSprite("bullet1.png");
    proj.startx = 512;
    proj.realx = 512;
    proj.starty = 704-pY;
    proj.speed = 9;
    if(goingLeft) proj.speed = -10;
    addProjectile(proj);
    delayShoot = 20;

  }

}

void menuInit(){
    engineInit();
    graphicsInit();
    setBackground("background.png");
}
void init(){
    #ifdef __APPLE__
    printf("On a Mac!");
    #endif
    free(themap);
    themap = getMap("map.txt", 100,24);
    printf("pos: %d\n", themap);
    currName = "map.txt";
    doorVecMain = getDoors();
  if(fileExists("map.txt.save")){
    short xy[2];
    loadSave("map.txt.save", xy);
    pX = xy[0];
    pY = xy[1];
  }else{
   pX = 512;
   pY = 32;
  }
  updateEnemies(pX-512, themap);

    printf("Back from mapload\n");
    initTiles(1);
    initTiles(2);

    initTransparentTiles(3);
    initTransparentTiles(4);
    initTransparentTiles(5);
    initTransparentTiles(6);
    initTiles(7);
    initTiles(7);
    initTransparentTiles(9);
    printf("testing\n");
    initMap(themap, 100,24);

    setPlayerSprite("player.png");
    setBackground("background.png");
   
}

int main(int argc, char *argv[]){
    menuInit();
    initFonts("FreeMonoBold.ttf", 16);

    SDL_Event theEvent;
  int menuindex = 0;
  drawMenu(0);
short shouldExit = FALSE;
while(1){
  while(SDL_PollEvent(&theEvent)){
    if(theEvent.type == SDL_KEYUP){
                    if ( theEvent.key.keysym.sym == SDLK_DOWN ){
                        if(menuindex < 1){
                          menuindex++;
                          drawMenu(menuindex);
                        }
                    } else if(theEvent.key.keysym.sym == SDLK_UP){
                        if(menuindex > 0){
                          menuindex--;
                          drawMenu(menuindex);
                        }
                    } else if(theEvent.key.keysym.sym == SDLK_RETURN){
                        if(menuindex == 1){
                          printf("Quit\n");
                          SDL_Quit();
                          return 1;
                        } else if (menuindex == 0){
                          printf("Loading\n");
                          shouldExit = TRUE;
                        //  system("del *.save");
                          shouldExit = TRUE;
                        }
                    }
    }
  }
  if(shouldExit) break;
}

init();
draw();
    while(1){
      int pxdelta = 0;
      int pydelta = 0;
        while(SDL_PollEvent(&theEvent)){
            switch(theEvent.type){
                case SDL_KEYUP:{
                    if ( theEvent.key.keysym.sym == SDLK_RIGHT ){
                        goingRight = FALSE;
                    } else if(theEvent.key.keysym.sym == SDLK_LEFT){
                        goingLeft = FALSE;
                        
                    }

                    break;
                }
                case SDL_KEYDOWN:{
                    if ( theEvent.key.keysym.sym == SDLK_RIGHT ){
                        goingRight = TRUE;
                    } else if(theEvent.key.keysym.sym == SDLK_LEFT){
                        goingLeft = TRUE;
                        
                    }
                    if(theEvent.key.keysym.sym == SDLK_RETURN){
                      fire();
                    }
                    if(theEvent.key.keysym.sym == SDLK_SPACE){
                        if(onGround == 1){
                        grav = -5;
                        gravoverride = 15;
                      }
                    }
                    if(theEvent.key.keysym.sym == SDLK_ESCAPE){
                      return 0;
                    }
                }

                default: {
                    break;
                }

            }

        }
if(!should_stop){
        if(goingRight){
         if(themap[getTileXd((pX)+5)][getTileY(pY)] == 0 || isnotcollide(themap[getTileXd((pX)+5)][getTileY(pY)],getTileXd((pX)+5),getTileY(pY))){
         pX+=5;
         pxdelta = 5;
         }

       } else if (goingLeft){

          if(themap[getTileXd((pX)-5)][getTileY(pY)] == 0 || isnotcollide(themap[getTileXd((pX)-5)][getTileY(pY)],getTileXd((pX)-5),getTileY(pY))){
           if(pX > 5){
              pX-=5;
              pxdelta = -5;
           }
          }

       }


    
    
    updateProjectiles(pxdelta);

    updateEnemies(pxdelta, themap);
    gravityCalc();
    if(delayShoot > 0){
    delayShoot--;
}
    if(collidesEnemies(pX, pY)){
      printf("Death\n");
      die();
   //   should_stop = TRUE;
    }
}

        draw();
        next_time = SDL_GetTicks() + TICK_INTERVAL;
        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;


  
}

	return 1;

}