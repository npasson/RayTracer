//
// Created by Nicholas on 03.09.2019.
//

#include "Material.h"

Material::Material(const Color phongAmbientMultiplier,
                   const Color phongDiffuseMultiplier,
                   const Color phongSpecularMultiplier,
                   double phongAlpha)
	: _phong_ambient_multiplier(phongAmbientMultiplier),
	  _phong_diffuse_multiplier(phongDiffuseMultiplier),
	  _phong_specular_multiplier(phongSpecularMultiplier),
	  _phong_alpha(phongAlpha) {
}

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
