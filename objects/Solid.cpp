//
// Created by root on 01.06.2019.
//

#include "Solid.h"

std::queue<Solid*> Solid::solids = std::queue<Solid*>();;

Solid::Solid() {
	Solid::solids.emplace(this);
}

const std::queue<Solid*>&
Solid::getSolids() {
	return solids;
}
