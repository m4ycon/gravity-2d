#pragma once
#include "SDL.h"
#include <iostream>

using namespace std;

class Utils
{
public:
	static void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
};
