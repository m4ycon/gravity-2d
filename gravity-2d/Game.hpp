#pragma once
#include "common.hpp"
#include "Particle.hpp"

class Game
{
public:
	Game(int nParticles, double initialVelLimit, double initialMass);
	~Game();

	void init(string title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update(Uint32 frameStart);
	void render();
	void clean();

	bool running() { return isRunning; }

	static double randomDouble(double lowerBound, double upperBound);

private:
	int nParticles;
	double initialVelLimit;
	double initialMass;

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	vector<Particle*> particles;
	void resetParticles();
};

