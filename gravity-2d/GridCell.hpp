#pragma once

#include "common.hpp"

class GridCell
{
public:
	GridCell(double x, double y, double w, double h, double mass);

	void render(SDL_Renderer* renderer);
private:
	double x, y, w, h, mass;
};

