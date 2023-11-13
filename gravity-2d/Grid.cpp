#include "Grid.hpp"

Grid::Grid(int gridCellSize)
{
	this->gridCellSize = gridCellSize;

	this->cells = {};
	for (int x = 0; x < SCREEN_WIDTH; x += gridCellSize) {
		cells.push_back({});
		for (int y = 0; y < SCREEN_HEIGHT; y += gridCellSize) {
			auto gc = new GridCell(x, y, gridCellSize, gridCellSize);
			cells[x / gridCellSize].push_back(gc);
		}
	}
}

void Grid::render(SDL_Renderer* renderer)
{
	for (auto& line : cells) for (auto col : line) col->render(renderer);
}

void Grid::resetMass()
{
	for (auto& line : cells) for (auto col : line) col->resetMass();
}

void Grid::addMass(Particle* p)
{
	auto gc = getGridCell(p->x, p->y);
	if (gc != nullptr) gc->addMass(p);
}

void Grid::updateForces()
{
	const int lines = cells.size();
	const int cols = cells[0].size();
	rep(i, 0, lines) {
		rep(j, 0, cols) {
			rep(x, 0, lines) {
				rep(y, 0, cols) {
					if (i == x && j == y) continue;
					cells[i][j]->applyForce(cells[x][y]);
				}
			}
		}
	}
}

pair<double, double> Grid::getForces(Particle* p)
{
	auto gc = this->getGridCell(p->x, p->y);
	if (gc == nullptr) return { 0, 0 };

	return { gc->dx, gc->dy };
}

GridCell* Grid::getGridCell(int x, int y)
{
	if (x < 0 || y < 0) return nullptr;
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) return nullptr;

	return cells[x / gridCellSize][y / gridCellSize];
}

GridCell::GridCell(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	this->dx = 0;
	this->dy = 0;
	this->mass = 0;
}

void GridCell::render(SDL_Renderer* renderer)
{
	if (mass == 0) return;

	/*SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, RGBA_WHITE);
	SDL_RenderDrawRect(renderer, &rect);*/

	int maxParticleColor = 10; // need this number of particles in grid to reach 255
	int numParticles = mass / INITIAL_MASS;
	int intensity = min(maxParticleColor, numParticles) * (255 / maxParticleColor);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, intensity);

	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void GridCell::resetMass()
{
	this->dx = 0;
	this->dy = 0;
	this->mass = 0;
}

void GridCell::addMass(Particle* p)
{
	this->mass += p->m;
}

void GridCell::applyForce(GridCell* gc)
{
	int tx = (this->x + this->w) / 2;
	int ty = (this->y + this->h) / 2;
	int gx = (gc->x + gc->w) / 2;
	int gy = (gc->y + gc->h) / 2;

	auto distance = Utils::distance(tx, ty, gx, gy);
	auto force = Utils::calculateForce(this->mass, gc->mass, distance);

	if (distance < 1) return;

	auto cadj = tx - gx; // cateto adjacente
	auto cops = ty - gy; // cateto oposto
	auto hipo = sqrt(cadj * cadj + cops * cops); // hipotenusa
	auto cosDist = cadj / hipo;
	auto sinDist = cops / hipo;

	auto xForce = force * cosDist;
	auto yForce = force * sinDist;

	this->dx -= xForce;
	this->dy -= yForce;
	gc->dx += xForce;
	gc->dy += yForce;
}
