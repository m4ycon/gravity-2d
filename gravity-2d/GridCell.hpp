#pragma once

#include "common.hpp"
#include "Particle.hpp"

using namespace std;

class GridCell
{
public:
	GridCell(double x, double y, double w, double h);

	void render(SDL_Renderer* renderer);

	void resetMass();
	void addMass(Particle* p);

private:
	double x, y, w, h, midX, midY;
	double mass, dx, dy;
	vector<GridCell*> innerGrid;

	GridCell* getInnerGridCell(int x, int y);
};

