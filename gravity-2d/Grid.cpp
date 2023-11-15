#include "Grid.hpp"

const int padding = 128;

Grid::Grid(int gridCellSize, int xOrigin, int yOrigin, int width, int height)
{
	this->xOrigin = xOrigin - padding;
	this->yOrigin = yOrigin - padding;
	this->width = this->_width = xOrigin + width + padding;
	this->height = this->_height = yOrigin + height + padding;
	this->gridCellSize = gridCellSize;

	this->resetCells();
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
	
	// n = lines * cols
	// O( n * (n-1) / 2 )
	/*rep(i, 0, lines) rep(j, 0, cols) {
		rep(y, j+1, cols) cells[i][j]->applyForce(cells[i][y]);

		rep(x, i+1, lines) rep(y, 0, cols) {
			cells[i][j]->applyForce(cells[x][y]);
		}
	}*/

	// n = lines * cols, r = radius
	// O( n * (2r + 1)^2 )
	int radius = 5;
	rep(i, 0, lines) rep(j, 0, cols) {
		rep(x, max(i - radius, 0), min(i + radius + 1, lines)) {
			rep(y, max(j - radius, 0), min(j + radius + 1, cols)) {
				if (i == x && j == y) continue;
				cells[i][j]->applyForce(cells[x][y]);
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

void Grid::changeOrigin(int x, int y)
{
	this->xOrigin = x;
	this->yOrigin = y;
	this->width = x + this->_width;
	this->height = y + this->_height;

	for (int x = this->xOrigin; x < this->width; x += gridCellSize) {
		for (int y = this->yOrigin; y < this->height; y += gridCellSize) {
			auto c = cells[(x - this->xOrigin) / gridCellSize][(y - this->yOrigin) / gridCellSize];
			c->x = x, c->y = y;
			c->resetMass();
		}
	}
}

GridCell* Grid::getGridCell(int x, int y)
{
	int xShifted = x - this->xOrigin;
	int yShifted = y - this->yOrigin;

	if (xShifted < 0 || yShifted < 0) return nullptr;
	if (xShifted >= SCREEN_WIDTH || yShifted >= SCREEN_HEIGHT) return nullptr;

	return cells[xShifted / gridCellSize][yShifted / gridCellSize];
}

void Grid::resetCells()
{
	this->cells.clear();
	for (int x = this->xOrigin; x < this->width; x += gridCellSize) {
		cells.push_back({});
		for (int y = this->yOrigin; y < this->height; y += gridCellSize) {
			auto gc = new GridCell(x, y, gridCellSize, gridCellSize);
			cells[(x - this->xOrigin) / gridCellSize].push_back(gc);
		}
	}
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

	int maxParticleColor = 250; // need this number of particles in grid to reach 255
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

	if (distance < 5) return;

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
