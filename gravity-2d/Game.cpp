#include "Game.hpp"

Game::Game(int nParticles, double initialVelLimit, double mass, int gridSize)
{
    this->nParticles = nParticles;
    this->initialVelLimit = initialVelLimit;
    this->initialMass = mass;
    this->gridSize = gridSize;
    
    this->isRunning = false;
    this->window = nullptr;
    this->renderer = nullptr;
    this->grid = nullptr;
}

Game::~Game()
{
}

void Game::init(string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    isRunning = false;

	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
    if (!window) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }
    SDL_SetRenderDrawColor(renderer, RGBA_BLACK);

    isRunning = true;

    this->initParticles();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    if (event.type == SDL_QUIT) {
        isRunning = false;
        return;
    }

    if (event.type != SDL_KEYDOWN) return;

    switch (event.key.keysym.sym) {
        case SDLK_q:
            isRunning = false;
            break;
        case SDLK_r:
            this->initParticles();
            break;
        default:
            break;
    }
}

void Game::update(Uint32 frameStart)
{
    grid->resetMass();

    for (auto p : particles) grid->addMass(p);

    rep(i, 0, particles.size()) {
        rep(j, i + 1, particles.size()) {
            particles[i]->applyForce(particles[j]);
        }
    }

    double frameTime = (SDL_GetTicks() - static_cast<double>(frameStart)) / 1000.;
    for (auto p : particles) p->move(frameTime);
}

void Game::render()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    SDL_SetRenderDrawColor(renderer, RGBA_BLACK);
    SDL_RenderClear(renderer);
    
    grid->render(renderer);
    //for (auto p : particles) p->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::renderFPS(Uint32 frameStart)
{
    auto actualFPS = 1000 / (SDL_GetTicks() - frameStart);
    cout << "FPS: " << actualFPS << endl;
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}

void Game::initParticles()
{
    this->particles = {};
    this->grid = new Grid(MIN_INNER_GRID);

    const auto safePadding = 100;
    rep(_, 0, nParticles) {
        auto x = Utils::randomDouble(0 + safePadding, SCREEN_WIDTH - safePadding);
        auto y = Utils::randomDouble(0 + safePadding, SCREEN_HEIGHT - safePadding);
        auto dx = Utils::randomDouble(-initialVelLimit, initialVelLimit);
        auto dy = Utils::randomDouble(-initialVelLimit, initialVelLimit);
        
        Particle* p = new Particle(x, y, dx, dy, initialMass);
        this->particles.push_back(p);
    }
}
