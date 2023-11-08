#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int nParticles = 2000;
	double initialVelLimit = .1; // m/s
	double initialMass = INITIAL_MASS; // kg

	game = new Game(nParticles, initialVelLimit, initialMass);
	game->init("Gravity 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update(frameStart);
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->clean();
	
	return 0;
}
