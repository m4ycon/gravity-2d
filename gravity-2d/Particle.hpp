#pragma once
#include "common.hpp"

const double Particle::G = 6.67e-11;

class Particle
{
public:
	static const double G;

	double x = 0, y = 0, dx = 0, dy = 0;

	Particle(double x, double y);
	
	void applyForce(Particle* particle);
	void move();

	static double calculateForce(double mass1, double mass2, double distance);

private:
};
