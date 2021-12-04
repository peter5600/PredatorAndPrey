#pragma once
#include "Creature.h"
#include "Predator.h"
using namespace std;

class Prey : public Creature {
public:
	Prey(sf::Vertex pixel, unsigned int x, unsigned int y);
	void Move();
	void handleHealth();
	void reproduce();
};