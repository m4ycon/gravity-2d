#pragma once
#include "common.hpp"
#include "Particle.hpp"
#include "Grid.hpp"

class Game
{
public:
	Game(int nParticles, double initialVelLimit, double initialMass);
	~Game();

	void init(string title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update(Uint32 frameStart);
	void render();
	void printFPS(Uint32 frameStart);
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int nParticles;
	double initialVelLimit;
	double initialMass;

	vector<Particle*> particles;
	vector<Grid*> grids;
	Grid* gridDisplay;
	void resetParticles();
	void resetGrids();
	void moveGrids();
};
