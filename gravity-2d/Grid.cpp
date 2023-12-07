#include "Grid.hpp"

const int padding = MAX_INNER_GRID;

Grid::Grid(int gridCellSize, int xOrigin, int yOrigin, int width, int height)
{
	this->xOrigin = xOrigin - padding;
	this->yOrigin = yOrigin - padding;
	this->width = width + 2 * padding;
	this->height = height + 2 * padding;
	this->_width = this->width;
	this->_height = this->height;
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

void Grid::changeOrigin()
{
	this->xOrigin = Utils::randomDouble(-gridCellSize, 0);
	this->yOrigin = Utils::randomDouble(-gridCellSize, 0);
	this->width = this->xOrigin + this->_width;
	this->height = this->yOrigin + this->_height;

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
	if (xShifted >= SCREEN_WIDTH + padding || yShifted >= SCREEN_HEIGHT + padding) return nullptr;

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
	this->centerX = 0;
	this->centerY = 0;
	this->mass = 0;
}

void GridCell::render(SDL_Renderer* renderer)
{
	if (mass == 0) return;

	/*SDL_Rect rect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, RGBA_WHITE);
	SDL_RenderDrawRect(renderer, &rect);*/

	const auto maxParticleColor = 105.; // need this number of particles in grid to reach 255
	const auto numParticles = mass / INITIAL_MASS;
	const auto intensity = min(maxParticleColor, numParticles) / maxParticleColor;
	auto [r, g, b] = Utils::heatToRGB(intensity);
	const int a = max(100., intensity * 255.);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void GridCell::resetMass()
{
	this->dx = 0;
	this->dy = 0;
	this->centerX = (this->x + this->w) / 2.;
	this->centerY = (this->y + this->h) / 2.;
	this->mass = 0;
}

void GridCell::addMass(Particle* p)
{
	this->centerX = (this->centerX + p->x) / 2.;
	this->centerY = (this->centerY + p->y) / 2.;
	this->mass += p->m;
}

void GridCell::applyForce(GridCell* gc)
{
	auto distance = Utils::distance(this->centerX, this->centerY, gc->centerX, gc->centerY);
	if (distance < 4) return;
	
	auto force = Utils::calculateForce(this->mass, gc->mass, distance);

	auto cadj = this->centerX - gc->centerX; // cateto adjacente
	auto cops = this->centerY - gc->centerY; // cateto oposto
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
