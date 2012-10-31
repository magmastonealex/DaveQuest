#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"
#include <vector>
#ifndef __APPLE__
#include <windows.h>
#endif
void engineInit(){
	#ifndef __APPLE__
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	#endif
    SDL_Init( SDL_INIT_EVERYTHING );
    #ifndef __APPLE__
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );	
    
    #endif
}