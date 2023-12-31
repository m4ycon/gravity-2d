#include "Utils.hpp"

// ref: https://stackoverflow.com/a/48291620
void Utils::DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);
	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0) {
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0) {
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

double Utils::calculateForce(double mass1, double mass2, double distance)
{
	return G * mass1 * mass2 / (distance * distance);
}

double Utils::randomDouble(double lowerBound, double upperBound)
{
	random_device rd;  // Create a random device
	mt19937 gen(rd());  // Create a Mersenne Twister pseudo-random number generator
	uniform_real_distribution<> dis(lowerBound, upperBound);

	return dis(gen);
}

double Utils::distance(double x1, double y1, double x2, double y2)
{
	auto dx = x1 - x2;
	auto dy = y1 - y2;
	auto distance = sqrt(dx * dx + dy * dy);
	return distance;
}

tuple<int, int, int> Utils::heatToRGB(double heat)
{
	heat = max(0., min(1., heat));

	/*if (heat <= 0.5)
		return make_tuple(0, 255 * (heat * 2), 255 - 255 * (heat * 2));
	
	return make_tuple(255 * (heat - 0.5) * 2, 255 - 255 * (heat - 0.5) * 2, 0);*/

	int red = min((2 * heat) * 255, 255.);
	int blue = min((2 * (1 - heat)) * 255, 255.);
	int green = 255 - abs(red - blue);
	return make_tuple(red, green, blue);
}
