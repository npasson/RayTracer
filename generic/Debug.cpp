//
// Created by root on 02.06.2019.
//

#include "Debug.h"
#include "../objects/LightSource.h"
#include "../objects/Camera.h"
#include "../Bitmap.h"

namespace Debug {

	namespace Presets {
		void
		untie_io() {
			std::ios_base::sync_with_stdio(false);
			std::cin.tie(nullptr);
		}

		std::mt19937
		get_rand_seed() {
			std::random_device rd;
			std::mt19937       mt(rd());
			return mt;
		}
	}

	namespace Tests {
		void
		testFourRotations() {
			Ray3 test{{0, 0, 0},
			          {1, 0, 0}};

			std::cout << test << std::endl;

			test = test.rotate(Ray3::Z, 45);
			std::cout << test << std::endl;

			test = test.rotate(Ray3::DOWN, 30);
			std::cout << test << std::endl;

			test = test.rotate(Ray3::Z, -45);
			std::cout << test << std::endl;

			test = test.rotate(Ray3::UP, 30);
			std::cout << test << std::endl;
		}

		void
		testMatrixMultiplication() {
			Matrix m1(2,
			          3,
			          {{3, 2, 1},
			           {1, 0, 2}});
			Matrix m2(3,
			          2,
			          {{1, 2},
			           {0, 1},
			           {4, 0}});

			std::cout << "m1 = " << m1 << std::endl;
			std::cout << "m2 = " << m2 << std::endl;
			std::cout << "m1*m2 = " << ( m1 * m2 ) << std::endl;
		}

		void
		testRayCastDirections() {

			Camera& c = Camera::getInstance();

			c.setPosition({{0, 0, 0},
			               {1, 0, 0}});

			c.setFov(90);

			c.forEachPixel([](Ray3 currentRay,
			                  uint16_t x,
			                  uint16_t y) -> Color {
				//std::cout << "(" << x << "," << y << ") -> " << currentRay << "\n";
				std::cout << currentRay.getDirection() << "\n";

				return {}; // empty color
			});

			std::cout << "Done!" << std::endl;
		}

		void
		testBitmapGeneration(std::mt19937* mt) {
			const uint16_t height = 100;
			const uint16_t width  = 100;
			auto           image  = new uint8_t[height][width][Bitmap::BYTES_PER_PIXEL];

			std::string imageFileName = "bitmapImage2.bmp";

			double red, green, blue;

			if (mt == nullptr) {
				red   = 0.8;
				green = 0.3;
				blue  = 0.2;
			} else {/*
				std::uniform_real_distribution<double> dist(0.0, 1.0);
				red   = dist(mt);
				green = dist(mt);
				blue  = dist(mt);*/

				red   = 0.8;
				green = 0.3;
				blue  = 0.2;
			}

			std::cout << "Creating sun with color " << Color({red,
			                                                  green,
			                                                  blue}) << "\n";

			LightSource Sun = LightSource({100,
			                               30,
			                               0},
			                              {red,
			                               green,
			                               blue},
			                              10);

			int y, x;
			for (y = 0; y < width; ++y) {
				for (x = 0; x < height; ++x) {
					Point p = Point(y, x, 0); // NOLINT

					image[x][y][Bitmap::RED]   = static_cast<uint8_t>(p.getBrightnessFromLightSource(Sun)
					                                                   .getRed() * 255 );
					image[x][y][Bitmap::GREEN] = static_cast<uint8_t>(p.getBrightnessFromLightSource(Sun)
					                                                   .getGreen() * 255 );
					image[x][y][Bitmap::BLUE]  = static_cast<uint8_t>(p.getBrightnessFromLightSource(Sun)
					                                                   .getBlue() * 255 );
				}
			}

			Bitmap::saveImage(reinterpret_cast<byte_t*>(image), height, width, imageFileName);
			printf("Image generated!");

			delete[] image;
		}
	}
}