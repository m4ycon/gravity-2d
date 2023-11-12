#pragma once

#include "common.hpp"
#include "Particle.hpp"

using namespace std;

class GridCell
{
public:
	GridCell(double x, double y, double w, double h, double mass);

	void render(SDL_Renderer* renderer);

	void resetMass();
	void addMass(Particle* p);

private:
	double x, y, w, h, mass;
	double midX, midY;
	vector<GridCell*> innerGrid;

	GridCell* getInnerGridCell(int x, int y);
};

