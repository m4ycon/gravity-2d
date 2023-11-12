#pragma once

#include "common.hpp"

using namespace std;

class GridCell
{
public:
	GridCell(double x, double y, double w, double h, double mass);

	void render(SDL_Renderer* renderer);

	void resetMass() { this->mass = 0; }
	void addMass(double mass) { this->mass += mass; }

private:
	double x, y, w, h, mass;
	double midX, midY;
};

