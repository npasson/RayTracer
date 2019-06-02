//
// Created by root on 02.06.2019.
//

#ifndef RAYTRACING_DEBUG_H
#define RAYTRACING_DEBUG_H

#include <random>
#include <iostream>
#include "../math/Ray3.h"
#include "../math/Matrix.h"

namespace Debug {

	namespace Presets {
		void
		untie_io();

		std::mt19937
		get_rand_seed();
	}

	namespace Tests {
		void
		testFourRotations();

		void
		testMatrixMultiplication();

		void
		testRayCastDirections();

		void
		testBitmapGeneration(std::mt19937* = nullptr);
	}
}

#endif //RAYTRACING_DEBUG_H
