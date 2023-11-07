#include "Particle.hpp"

Particle::Particle(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Particle::applyForce(Particle* particle)
{
	auto dx = this->x - particle->x;
	auto dy = this->y - particle->y;
	auto distance = sqrt(dx * dx + dy * dy);
	auto force = this->calculateForce(1, 1, distance);

	auto cadj = this->x - particle->x; // cateto adjacente
	auto cops = this->y - particle->y; // cateto oposto
	auto hipo = sqrt(cadj * cadj + cops * cops); // hipotenusa
	auto cosDist = cadj / hipo;
	auto sinDist = cops / hipo;

	auto xForce = force * cosDist;
	auto yForce = force * sinDist;

	this->dx += xForce;
	this->dy += yForce;
	particle->dx -= xForce;
	particle->dy -= yForce;
}

void Particle::move()
{
	this->x += this->dx;
	this->y += this->dy;
}

double Particle::calculateForce(double mass1, double mass2, double distance)
{
	return G * mass1 * mass2 / (distance * distance);
}
