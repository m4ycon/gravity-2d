#include "Game.hpp"

Game::Game(int nParticles, double initialVelLimit, double mass)
{
    this->nParticles = nParticles;
    this->initialVelLimit = initialVelLimit;
    this->initialMass = mass;
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
    vector<Particle*> newParticles;
    rep(i, 0, particles.size()) {
        if (particles[i]->m == 0) continue;
        rep(j, i + 1, particles.size()) {

            particles[i]->applyForce(particles[j]);

            if (particles[i]->colision(particles[j]))
                particles[i]->merge(particles[j]);
        }
        newParticles.push_back(particles[i]);
    }

    this->particles = newParticles;

    double frameTime = (SDL_GetTicks() - static_cast<double>(frameStart)) / 1000.;
    for (auto p : particles) p->move(frameTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, RGBA_BLACK);
    SDL_RenderClear(renderer);

    for (auto p : particles) p->render(renderer);

    SDL_RenderPresent(renderer);
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
    this->particles = {};

    rep(_, 0, nParticles) {
        auto x = randomDouble(0, SCREEN_WIDTH);
        auto y = randomDouble(0, SCREEN_HEIGHT);
        auto dx = randomDouble(-initialVelLimit, initialVelLimit);
        auto dy = randomDouble(-initialVelLimit, initialVelLimit);
        
        Particle* p = new Particle(x, y, dx, dy, initialMass);
        this->particles.push_back(p);
    }
}

double Game::randomDouble(double lowerBound = 0, double upperBound = 1)
{
    random_device rd;  // Create a random device
    mt19937 gen(rd());  // Create a Mersenne Twister pseudo-random number generator
    uniform_real_distribution<> dis(lowerBound, upperBound);

    return dis(gen);
}
