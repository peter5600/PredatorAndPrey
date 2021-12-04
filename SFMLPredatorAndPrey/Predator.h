#pragma once
#include "Creature.h"
#include "Prey.h"
#include "Game.h"
using namespace std;

class Predator : public Creature {
public:
	Predator(sf::Vertex pixel, unsigned int x, unsigned int y);
	void Move();
	void handleHealth();
	void die();
};