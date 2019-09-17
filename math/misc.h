//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_MISC_H
#define RAYTRACING_MISC_H

#include <cmath>
#include <iostream>

#include "Ray3.h"
#include "Matrix.h"
#include "../objects/LightSource.h"
#include "../objects/Solid.h"

namespace rt_math {

	enum Axes {
		X, Y, Z
	};

	inline double
	clamp(double value,
	      double min,
	      double max) {
		if (value > max) { return max; }
		if (value < min) { return min; }
		return value;
	}

	inline double
	deg2rad(double degrees) {
		return ( degrees * M_PI ) / 180;
	}

	inline Ray3
	rotateVector(Ray3 ray,
	             Axes axis,
	             double degrees) {
		// TODO
		Matrix rotationMatrix(3, 3);

		degrees = deg2rad(degrees);

		if (axis == X) {
			rotationMatrix = {{1, 0,            0},
			                  {0, cos(degrees), -sin(degrees)},
			                  {0, sin(degrees), cos(degrees)}};
		} else if (axis == Y) {
			rotationMatrix = {{cos(degrees),  0, sin(degrees)},
			                  {0,             1, 0},
			                  {-sin(degrees), 0, cos(degrees)}};
		} else {
			rotationMatrix = {{cos(degrees), -sin(degrees), 0},
			                  {sin(degrees), cos(degrees),  0},
			                  {0,            0,             1}};
		}

		Matrix directional(Matrix::_t{{ray.getDirection()
		                                  .getX()},
		                              {ray.getDirection()
		                                  .getY()},
		                              {ray.getDirection()
		                                  .getZ()}});

		Matrix rotated = rotationMatrix * directional;

		Ray3 rotatedRay(
			ray.getOrigin(),
			{
				rotated.getData()[0][0],
				rotated.getData()[1][0],
				rotated.getData()[2][0]
			},
			ray.getDistance());

		return rotatedRay;
	}

	inline Color
	phong(Point& p,
	      Solid& s,
	      const Vec3& cameraVectorArg) {

		Vec3 cameraVector = cameraVectorArg.getNormalize();

		Color i_a{},
		      i_d{},
		      i_s{};

		Color k_a = s.getMaterial()
		             .getPhongAmbientMultiplier(),
		      k_d = s.getMaterial()
		             .getPhongDiffuseMultiplier(),
		      k_s = s.getMaterial()
		             .getPhongSpecularMultiplier();

		double alpha = s.getMaterial()
		                .getPhongAlpha();

		Vec3 v_normal = s.getNormal(p);
		Vec3 v_v      = -cameraVector;

		auto lights = LightSource::getLights();

		//std::cout << "Light count: " << lights.size() << "\n";

		Color each_light_sum;
		Color ambient;

		std::vector<Color> ambients;

		while (!lights.empty()) {
			LightSource ls = *( lights.front());
			lights.pop();

			ambients.push_back(ls.getColor() * ls.getBrightness());

			i_d = Color{ls.getBrightness()}; // p.getBrightnessFromLightSource(ls);
			i_s = ls.getColor();

			Vec3 lightVector = ls.getVectorTo(p)
			                     .getNormalize();

			Vec3 v_l_m = -lightVector;
			Vec3 v_r_m = lightVector.reflectOff(v_normal)
			                        .getNormalize();

			//	std::cout << "LightVector:" << v_l_m << "\n";
			//	std::cout << "RflctVector:" << v_r_m << "\n";

			double diffuse_dot_product = v_l_m * v_normal;

			if (diffuse_dot_product > 0) {

				// diffuse element
				each_light_sum += k_d * ( diffuse_dot_product ) * i_d;

				// specular element
				double specular_dot_product = v_r_m * v_v;
				if (specular_dot_product > 0) {
					each_light_sum += k_s * std::pow(specular_dot_product, alpha) * i_s;
				}
			}
		}

		ambient = Color::combine(ambients);

		// std::cout << "Ambient before: " << ambient << "\n";

		ambient = ambient * k_a;

		// std::cout << "Ambient after:  " << ambient << "\n";

		each_light_sum += ambient;

		//std::cout << "Phong: " << each_light_sum << "\n";

		return each_light_sum;
	}
}

#endif //RAYTRACING_MISC_H
