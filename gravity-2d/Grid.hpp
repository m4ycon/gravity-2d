#pragma once

#include "common.hpp"
#include "Particle.hpp"

using namespace std;

class GridCell;

class Grid
{
public:
	Grid(int gridCellSize, int xOrigin = 0, int yOrigin = 0, int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);

	void render(SDL_Renderer* renderer);

	void changeOrigin();

	void resetMass();
	void addMass(Particle* p);
	void updateForces();
	pair<double, double> getForces(Particle* p);

private:
	double gridCellSize = 0;
	int xOrigin = 0, yOrigin = 0, width = 0, height = 0;
	int _width = 0, _height = 0;

	vector<vector<GridCell*>> cells;

	GridCell* getGridCell(int x, int y);

	void resetCells();
};

class GridCell {
public:
	int x = 0, y = 0, w = 0, h = 0;
	double dx = 0, dy = 0, centerX = 0, centerY = 0, mass = 0;
	
	GridCell(int x, int y, int w, int h);

	void render(SDL_Renderer* renderer);

	void resetMass();
	void addMass(Particle* p);
	void applyForce(GridCell* gc);
};

