all: src/main.cpp
	g++ src/main.cpp src/Game.cpp src/Ball.cpp -g -pedantic -o build/program -lSDL2 -lSDL2_image