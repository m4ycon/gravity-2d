#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game();
	game->init("SDL2 test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	
	return 0;
}
