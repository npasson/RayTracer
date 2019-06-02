#include <cstdio>
#include <cstdint>
#include <ctime>
#include <iostream>
#include "Bitmap.h"
#include "objects/LightSource.h"
#include "math/Matrix.h"
#include "math/misc.h"
#include "objects/Camera.h"
#include "generic/Debug.h"

int
main() {
	Debug::Presets::untie_io();
	auto mt = Debug::Presets::get_rand_seed();

	Debug::Tests::testBitmapGeneration(&mt);
}


