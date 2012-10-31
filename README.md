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


How to add a new map
----

_This is confusing right now, so bear with me..._

First, create a new map in Tiled Map Editor. Ensure that file format is set to CSV in Preferences.
The map should be 100 tiles wide, and 24 tiles high.
The tileset is in outline.png.
Create your map.
Now edit another map file, to include a door to connect to your map. Just place the sprite for now.
Add your new map to the makefile, under map, like this:

python mapproc.py YourMapName.tmx YourMapName.txt

Now open up the map that leads into yours door file, like so:

MapLeadIn.txt.door.txt

Keep that open in another window.

Now, run

make map

Then, run python newMap.py MapLeadIn.txt.
Look at Tiled to determine where the doors are (in the lead-in map), and where they should lead. Type the map like this:

map.txt

Then, run python newMap.py YourMapName.txt

Again, look at Tiled to determine where the doors are in your level, and where they ushould leave.