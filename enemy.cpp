#include "draw.h"
#include <math.h>
#include "SDL/SDL.h"
#include <vector>
#include "enemy.h"
#include "projectile.h"

#define true 1
#define false 0
extern int currScore;
//Keep track of all of the enemies
//Enemy is a struct defined in enemy.h.
std::vector<Enemy> allEnemies;

//Get tile positions from pixel coordinates
int getTileXE(int thex){
return floor(((float)thex)/32);

}
int getTileYE(int they){
return 22-ceil(they/32);

}

//Update all enemy positions and states.]
// Must be called every frame.
// Takes a delta of the player movement in the frame, and the current map.
void updateEnemies(int pDelta, short** themap){
//For all enemies in the vector
for (unsigned int i=0; i < allEnemies.size(); i++) {
	Enemy theEnemy = allEnemies[i]; // Get the enemy in an easy to access way
    theEnemy.screenX -= pDelta; // Move against the delta. This keeps the enemy on screen in the same place.
//Don't allow jumping enemies to die
if(theEnemy.type != JUMPING){
if(collidesProjectiles(theEnemy.screenX, 704-theEnemy.Y)){

	allEnemies.erase(allEnemies.begin()+i); //Remove the enemy.
	currScore += 10;
	continue;
}
}

//If we're on the ground
if(themap[getTileXE(theEnemy.X)][getTileYE(theEnemy.Y-theEnemy.gravity)] != 0){

theEnemy.onGround = 1;
}else{
theEnemy.onGround = 0;
}
//If we're touching water.
if(themap[getTileXE(theEnemy.X)][getTileYE(theEnemy.Y-theEnemy.gravity)] == 3){
	allEnemies.erase(allEnemies.begin()+i);
	continue;
}
//GravResist allows the enemy to jump without immediately being pulled down by gravity.
if(theEnemy.gravResist == 0){

if(theEnemy.gravity <= 5){
    theEnemy.gravity++; // Gravity is the number of pixels that the enemy moves down in a frame from gravity.

}

}else{
    theEnemy.gravResist--;

}
 //Move down if we're not on the ground
if(theEnemy.onGround == false){
 theEnemy.Y -= theEnemy.gravity;

}

//Class-specific updates now.


if(theEnemy.type == JUMPING){

	// Check if we should jump
		if(theEnemy.delay == 0){

			theEnemy.gravResist = 10; //Jump!
			theEnemy.gravity = -20;
			theEnemy.delay = 130;
		} else{
			theEnemy.delay--;
		}
	
    
} else if (theEnemy.type == ROAMING){
	//Are we moving right?
	if(theEnemy.movingRight){

		if(themap[getTileXE(theEnemy.X+theEnemy.speed)][getTileYE(theEnemy.Y)] == 0){ // If the tile to the right is air

			if(themap[getTileXE(theEnemy.X+theEnemy.speed)][getTileYE(theEnemy.Y-32)] != 0){ // If the tile below, to the right is air

				theEnemy.X+=theEnemy.speed;
				theEnemy.screenX+=theEnemy.speed;
			}else{
				theEnemy.movingRight = false; //We can't move right anymore. Move left.
			}
		}else{
			theEnemy.movingRight = false; //Can't move right. Move left.
		}
	}else{ //Must be moving left

		if(themap[getTileXE(theEnemy.X-theEnemy.speed)][getTileYE(theEnemy.Y)] == 0){ // Same checks as before.
			if(themap[getTileXE(theEnemy.X-theEnemy.speed)][getTileYE(theEnemy.Y-32)] != 0){
				theEnemy.X-=theEnemy.speed;
				theEnemy.screenX-=theEnemy.speed;
			}else{
				theEnemy.movingRight = true; // Move right now
			}
		}else{
			theEnemy.movingRight = true; // Move right now
		}
	}
}

allEnemies[i] = theEnemy; //Reassign the enemy back into the vector.
}
}
//Check for collisions.
//Takes the current player X and Y.
int collidesEnemies(int thisX, int thisY){
for (unsigned int i=0; i < allEnemies.size(); i++) {
    SDL_Rect a; //The enemy position
    a.x = allEnemies[i].X;
    a.y = allEnemies[i].Y;
    a.w = 32;
    a.h = 32;

    SDL_Rect b; // Player position
    b.x = thisX;
    b.y = thisY;
    b.w = 32;
    b.h = 32;
	if(b.x + b.w < a.x)	continue;//Continue if there is no collision.
	if(b.x > a.x + a.w)	continue;

	if(b.y + b.h < a.y)	continue;
	if(b.y > a.y + a.h)	continue;

	return 1;
}
	return 0;
}
//Draw all the enemies
void drawEnemies(){
//Loop through enemies.

for (unsigned int i=0; i < allEnemies.size(); i++) {

  drawSprite(allEnemies[i].screenX, 704-allEnemies[i].Y, allEnemies[i].sprite); //Draw the enemy
}

}
//Deletes all enemies.
void deleteEnemies(){
allEnemies.clear();
}
//Adds a new, preconstructed enemy.
void addEnemies(Enemy newEnemy){
newEnemy.screenX = newEnemy.X;

allEnemies.push_back(newEnemy);

}