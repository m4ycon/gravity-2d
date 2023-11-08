#include "Particle.hpp"

const double Particle::G = 6.67e-11;

Particle::Particle(double x, double y, double dx, double dy, double m)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->m = m;
}

void Particle::applyForce(Particle* particle)
{
	auto distance = this->distance(particle);
	auto force = this->calculateForce(this->m, particle->m, distance);

	auto cadj = this->x - particle->x; // cateto adjacente
	auto cops = this->y - particle->y; // cateto oposto
	auto hipo = sqrt(cadj * cadj + cops * cops); // hipotenusa
	auto cosDist = cadj / hipo;
	auto sinDist = cops / hipo;

	auto xForce = force * cosDist;
	auto yForce = force * sinDist;

	this->dx -= xForce;
	this->dy -= yForce;
	particle->dx += xForce;
	particle->dy += yForce;
}

double Particle::distance(Particle* particle)
{
	auto dx = this->x - particle->x;
	auto dy = this->y - particle->y;
	auto distance = sqrt(dx * dx + dy * dy);
	return distance;
}

void Particle::merge(Particle* particle)
{
	// merge particles
	this->dx += particle->dx;
	this->dy += particle->dy;
	this->m += particle->m;

	particle->m = 0;
	particle->dx = 0;
	particle->dy = 0;
}

void Particle::move(Uint32 timeLapsed)
{
	this->x += this->dx * timeLapsed;
	this->y += this->dy * timeLapsed;
}

double Particle::calculateForce(double mass1, double mass2, double distance)
{
	return G * mass1 * mass2 / (distance * distance);
}
