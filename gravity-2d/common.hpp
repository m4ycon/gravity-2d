#include "SDL.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Utils.hpp"

using namespace std;

typedef long long ll;
typedef double db;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define all(x) (x).begin(),(x).end()

#define RGBA_BLACK 0, 0, 0, 255
#define RGBA_WHITE 255, 255, 255, 255
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define N_PARTICLES 1500
#define INITIAL_MASS 1000000 // kg
#define INITIAL_VEL_LIMIT 0 // m/s - max initial particles velocity
#define GRID_SIZE 5 // px
