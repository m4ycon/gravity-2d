#pragma once
#include "common.hpp"

class Particle
{
public:
	double x = 0, y = 0, dx = 0, dy = 0, m = 0, radius = 0;

	Particle(double x, double y, double dx, double dy, double m);
	
	void applyForce(Particle* particle);
	void merge(Particle* particle);
	void move(double timeLapsed);

	void render(SDL_Renderer* renderer);

	double distance(Particle* particle);
	bool colision(Particle* particle);

	static double calculateForce(double mass1, double mass2, double distance);

private:
};
