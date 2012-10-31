#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "load.h"
#include "draw.h"
#include "enemy.h"
#include <vector>
using namespace std;
//Fill a map. Note that the returned value is a POINTER to an array, which is initialized in this function.
//Be very careful, szX and szY must EXACTLY fit the size of the map, otherwise, it will segfault.
std::vector<string> doorVec;
void AddEnemy(int x, int y,char type){

    Enemy en;
    if(type == JUMPING) en.sprite = loadSprite("jumper.png");
    if(type == ROAMING) en.sprite = loadSprite("roamer.png");
    en.X = x*32;
    en.Y = 704-(y*32);
    en.onGround = 0;
    en.type = type;
    en.gravResist = 0;
    en.gravity = 5;
    en.delay = 0;
    en.movingRight = 1;
    en.speed = 2;
    addEnemies(en);

}

void loadSave(std::string saveFile, short* xy){
    ifstream thesave;
    thesave.open(saveFile.c_str());
   // short xy[2];
    std::string tempstring;
    getline(thesave, tempstring);
    xy[0] = atoi(tempstring.c_str());
    getline(thesave, tempstring);
    xy[1] = atoi(tempstring.c_str());
    xy[1] += 35;
    return;

}

std::vector<std::string> getDoors(){
    return doorVec;    
}
short** getMap(string filename, int szX, int szY){
	//Begin allocations
    int doorCount = 0;
    
    short** tempMapArray;
    tempMapArray = (short**) malloc(szX * sizeof(short *));
    for(int i = 0; i < szX; i++){

        tempMapArray[i] = (short*)malloc(szY * sizeof(short));
    }
    //Begin map loading
    char * pch;
    string line;
    ifstream myfile;
    ifstream doorfile;
    myfile.open(filename.c_str());
    filename+=".door.txt";
    doorfile.open(filename.c_str());
    doorVec.clear();
    if (myfile.is_open())
    {

        int iter = 0;
        while ( myfile.good() )
        {
            
            getline (myfile,line);

            replace(line.begin(), line.end(), '\n', '\0');  
            char * theline = (char *)line.c_str();
            pch = strtok (theline,",");
            int i = 0;
            while (pch != NULL)
            {


                tempMapArray[i][iter] = atoi(pch);
            if(tempMapArray[i][iter] == 7){
                tempMapArray[i][iter] = 0;
          //      printf("Adding Enemy: Jumper\n");
                AddEnemy(i,iter,JUMPING);
                
            }else if (tempMapArray[i][iter] == 8){
                tempMapArray[i][iter] = 0;
            //    printf("Adding Enemy: Roamer\n");
                AddEnemy(i,iter,ROAMING);
            }else if(tempMapArray[i][iter] == 6){
                tempMapArray[i][iter] = 900+doorCount;
                doorCount++;
                string doorline;
                getline(doorfile, doorline);
                printf("Door loaded: %s\n", doorline.c_str());
                doorVec.push_back(doorline);
            }
                pch = strtok(NULL, ",");

                i++;

            }
            iter++;
        
    }
        myfile.close();

    }

return tempMapArray;

}
