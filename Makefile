engine: load.cpp draw.cpp engine.cpp
	g++ load.cpp -c -o load.o
	g++ draw.cpp -c -o draw.o
	g++ engine.cpp -c -o engine.o
	g++ projectile.cpp -c -o projectile.o
	g++ enemy.cpp -c -o enemy.o
	g++ savefiles.cpp -c -o savefiles.o	
	g++ text.cpp -c -o text.o

	 
link: engine game map
	g++ draw.o load.o engine.o main.o  projectile.o enemy.o savefiles.o text.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -o app

map:
	python mapproc.py map.tmx map.txt
	python mapproc.py map0.tmx map0.txt
	python mapproc.py bonus.tmx bonus.txt
	python mapproc.py map1.tmx map1.txt
	python mapproc.py map2.tmx map2.txt
	python mapproc.py map3.tmx map3.txt
	python mapproc.py map4.tmx map4.txt

game: main.cpp
	g++ main.cpp -c -o main.o

all: link
	app.exe
mac:
	g++ `sdl-config --libs` -framework SDL_net -framework SDL_ttf -framework SDL -framework SDL_image -lpthread main.cpp engine.cpp load.cpp draw.cpp projectile.cpp enemy.cpp  -o main
	python mapproc.py
