Dave's Quest
===


[Link to the main game page](jacknoir.no-ip.org/game/)

This was a game I made for computer technology class, in a few weeks. It was written in C++, using SDL for graphics. The code is formatted so that the "engine" layer is seperated from the "game" layer.
This means that I could run the "game" layer on any engine that supports the same function calls. (I tested this using an old engine I wrote)

This was also an experiment in compiling into object files, and then linking all of them into an executable. This is the first time I have done this, and it resulted in much faster compiling times.

The sprites were made by a friend for a game a long time ago, and I modified a few of them (thin platforms, for example).

The collisions are interesting, it's the first time I've successfully implemented pixel-by-pixel collisions in C++. They took a long time to make work properly, but most of that was mapping a pixel position on screen to game co-ordinates, and then to tile posistions (which took a surprising amount of math).

The enemy AI was surprisingly easy to implement (once player collisions were figured out...), although there isn't a lot of "thinking" going on.

To compile: You will need MinGW installed, along with SDL, SDL_Image and SDL_TTF. 

