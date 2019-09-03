//
// Created by Nicholas on 03.09.2019.
//

#include "Material.h"

const Color&
Material::getPhongAmbientMultiplier() const {
	return _phong_ambient_multiplier;
}

const Color&
Material::getPhongDiffuseMultiplier() const {
	return _phong_diffuse_multiplier;
}

const Color&
Material::getPhongSpecularMultiplier() const {
	return _phong_specular_multiplier;
}

double
Material::getPhongAlpha() const {
	return _phong_alpha;
}
