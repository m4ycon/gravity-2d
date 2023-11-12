#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int LIMIT_FPS = 60;
	const int frameDelay = 1000 / LIMIT_FPS;

	Uint32 frameStart;
	int frameTime;

	int nParticles = N_PARTICLES;
	double initialVelLimit = INITIAL_VEL_LIMIT;
	double initialMass = INITIAL_MASS;
	int gridSize = GRID_SIZE;

	game = new Game(nParticles, initialVelLimit, initialMass, gridSize);
	game->init("Gravity 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update(frameStart);
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

		game->renderFPS(frameStart);
	}

	game->clean();
	
	return 0;
}
