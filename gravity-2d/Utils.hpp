#pragma once
#include "SDL.h"
#include <iostream>
#include <random>

#define G 6.67e-11

using namespace std;

class Utils
{
public:
	static void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
	static double calculateForce(double mass1, double mass2, double distance);
	static double randomDouble(double lowerBound, double upperBound);
};
