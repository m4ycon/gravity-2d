#include "Particle.hpp"

Particle::Particle(double x, double y, double dx, double dy, double m)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->m = m;


	int area = this->m / INITIAL_MASS; // num of particles
	this->radius = sqrt(M_PI * area);
}

void Particle::move(double timeLapsed)
{
	this->x += this->dx * timeLapsed;
	this->y += this->dy * timeLapsed;
}

void Particle::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, RGBA_WHITE);

	// point
	SDL_RenderDrawPoint(renderer, this->x, this->y);
	
	// square
	//SDL_Rect rect = { this->x - this->radius, this->y - this->radius, this->radius * 2, this->radius * 2 };
	//SDL_RenderFillRect(renderer, &rect);

	// circle
	//Utils::DrawCircle(renderer, this->x, this->y, this->radius);
}
