//
// Created by Nicholas on 03.09.2019.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "../math/Color.h"

class Material {
	Color  _phong_ambient_multiplier{0.5};
	Color  _phong_diffuse_multiplier{2};
	Color  _phong_specular_multiplier{0.2};
	double _phong_alpha{50};
public:
	Material() = default;

	Material(Color phongAmbientMultiplier,
	         Color phongDiffuseMultiplier,
	         Color phongSpecularMultiplier,
	         double phongAlpha);

	const Color&
	getPhongAmbientMultiplier() const;

	const Color&
	getPhongDiffuseMultiplier() const;

	const Color&
	getPhongSpecularMultiplier() const;

	double
	getPhongAlpha() const;
};

#endif //RAYTRACING_MATERIAL_H
