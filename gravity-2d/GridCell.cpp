#include "GridCell.hpp"

GridCell::GridCell(double x, double y, double w, double h, double mass)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->mass = mass;
	this->midX = x + w / 2;
	this->midY = y + h / 2;
}

void GridCell::render(SDL_Renderer* renderer)
{
	const int maxParticleColor = 20;
	int numParticles = mass / INITIAL_MASS;
	int intensity = min(maxParticleColor, numParticles) * (255 / maxParticleColor);
	SDL_SetRenderDrawColor(renderer, intensity, 0, 0, 255);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}
