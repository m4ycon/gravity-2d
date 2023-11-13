#pragma once
#include "common.hpp"

class Particle
{
public:
	double x = 0, y = 0, dx = 0, dy = 0, m = 0, radius = 0;

	Particle(double x, double y, double dx, double dy, double m);
	
	void move(double timeLapsed);

	void render(SDL_Renderer* renderer);

private:
};
