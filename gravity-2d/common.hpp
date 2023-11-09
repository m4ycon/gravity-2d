#include "SDL.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <random>

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

#define G 6.67e-11
#define N_PARTICLES 2000
#define INITIAL_MASS 250000 // kg
#define INITIAL_VEL_LIMIT 1 // m/s
