#pragma once
#include "common.hpp"

class Particle
{
public:
	static const double G;

	double x = 0, y = 0, dx = 0, dy = 0, m = 0;

	Particle(double x, double y, double dx, double dy, double m);
	
	void applyForce(Particle* particle);
	void move();

	static double calculateForce(double mass1, double mass2, double distance);

private:
};
