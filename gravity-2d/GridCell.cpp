#include "GridCell.hpp"

GridCell::GridCell(double x, double y, double w, double h)
{
	this->x = x, this->y = y;
	this->w = w, this->h = h;
	this->midX = x + w / 2;
	this->midY = y + h / 2;
	
	this->dx = 0, this->dy = 0;
	this->mass = 0;

	if (w <= MIN_INNER_GRID) return;

	// 0 1
	// 2 3
	this->innerGrid.push_back(new GridCell(   x,    y, w / 2, h / 2)); // 0
	this->innerGrid.push_back(new GridCell(midX,    y, w / 2, h / 2)); // 1
	this->innerGrid.push_back(new GridCell(   x, midY, w / 2, h / 2)); // 2
	this->innerGrid.push_back(new GridCell(midX, midY, w / 2, h / 2)); // 3
}

void GridCell::render(SDL_Renderer* renderer)
{
	/*SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, RGBA_WHITE);
	SDL_RenderDrawRect(renderer, &rect);*/


	if (innerGrid.size() > 0) {
		for (auto ig : innerGrid) ig->render(renderer);
		return;
	}

	const int maxParticleColor = 10; // need this number of particles in grid to achieve 255 in color
	int numParticles = mass / INITIAL_MASS;
	int intensity = min(maxParticleColor, numParticles) * (255 / maxParticleColor);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, intensity);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void GridCell::resetMass()
{
	this->mass = 0;
	for (auto ig : innerGrid) ig->resetMass();
}

void GridCell::addMass(Particle* p)
{
	this->mass += p->m;
	auto ig = getInnerGridCell(p->x, p->y);
	if (ig != nullptr) ig->addMass(p);
}

GridCell* GridCell::getInnerGridCell(int x, int y)
{
	for (auto ig : innerGrid) {
		if (   x >= ig->x && x <= ig->x + ig->w
			&& y >= ig->y && y <= ig->y + ig->h
		) return ig;
	}

	return nullptr;
}
