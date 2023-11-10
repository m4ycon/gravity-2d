#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

using namespace std;

class Utils
{
public:
	static void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
	static void WriteOnScreen(SDL_Renderer* renderer, string text, int x, int y);
};

