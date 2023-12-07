#include "Game.hpp"

Game::Game(int nParticles, double initialVelLimit, double mass)
{
    this->nParticles = nParticles;
    this->initialVelLimit = initialVelLimit;
    this->initialMass = mass;
    
    this->isRunning = false;
    this->window = nullptr;
    this->renderer = nullptr;
    this->grids.clear();
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

    this->resetParticles();
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
            this->resetParticles();
            break;
        default:
            break;
    }
}

void Game::update(Uint32 frameStart)
{
    this->moveGrids();

    for (auto g : grids) {
        g->resetMass();
        for (auto p : particles) g->addMass(p);
        g->updateForces();
    }

    double frameTime = (SDL_GetTicks() - static_cast<double>(frameStart)) / 1000.;
    for (auto p : particles) {
        double xAcc = 0, yAcc = 0;

        for (auto g : grids) {
            auto [fx, fy] = g->getForces(p);
            xAcc += fx;
            yAcc += fy;
        }

        p->dx += xAcc;
        p->dy += yAcc;
        p->move(frameTime);
    }

    gridDisplay->resetMass();
    for (auto p : particles) gridDisplay->addMass(p);
}

void Game::render()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    SDL_SetRenderDrawColor(renderer, RGBA_BLACK);
    SDL_RenderClear(renderer);
    
    //for (auto p : particles) p->render(renderer);
    gridDisplay->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::printFPS(Uint32 frameStart)
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

void Game::resetParticles()
{
    this->resetGrids();
    this->particles.clear();

    const auto safePadding = 10;
    rep(_, 0, nParticles) {
        auto x = Utils::randomDouble(0 + safePadding, SCREEN_WIDTH - safePadding);
        auto y = Utils::randomDouble(0 + safePadding, SCREEN_HEIGHT - safePadding);
        auto dx = Utils::randomDouble(-initialVelLimit, initialVelLimit);
        auto dy = Utils::randomDouble(-initialVelLimit, initialVelLimit);
        
        Particle* p = new Particle(x, y, dx, dy, initialMass);
        this->particles.push_back(p);
    }
}


void Game::resetGrids()
{
    const int numberOfGrids = 4;

    this->grids.clear();
    for (int i = 0; i < numberOfGrids; i++) {
        auto g = new Grid(MAX_INNER_GRID >> i);
        this->grids.push_back(g);
    }

    gridDisplay = new Grid(4);
}

void Game::moveGrids()
{
    for (auto g : grids) g->changeOrigin();
}
