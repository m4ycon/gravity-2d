#pragma once

#include "common.hpp"
#include "Particle.hpp"

using namespace std;

class GridCell;

class Grid
{
public:
	Grid(int gridCellSize);

	void render(SDL_Renderer* renderer);

	void resetMass();
	void addMass(Particle* p);

private:
	double gridCellSize = 0;

	vector<vector<GridCell*>> cells;

	GridCell* getGridCell(int x, int y);
};

class GridCell {
public:
	int x = 0, y = 0, w = 0, h = 0;
	double mass = 0;
	
	GridCell(int x, int y, int w, int h);

	void render(SDL_Renderer* renderer);

	void resetMass();
	void addMass(Particle* p);
};

