#include "GridCell.hpp"

GridCell::GridCell(double x, double y, double w, double h, double mass)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->mass = mass;
}

void GridCell::render(SDL_Renderer* renderer)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}
