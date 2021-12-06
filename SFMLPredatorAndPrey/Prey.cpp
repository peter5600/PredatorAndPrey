#include "Prey.h"

Prey::Prey(sf::Vertex pixel, unsigned int x, unsigned int y) : Creature(pixel, x, y)
{
	this->setHealth(1);
}

void Prey::Move()
{
	this->getMove();//this will set tmpX and tmpY so that i can try moving there
	if (this->getTmpX() != this->getX() || this->getTmpY() != this->getY()) {
		shared_ptr<Creature> creatureAtLocation = findCreatureAtPos(this->getTmpX(), this->getTmpY());//This line
		if (creatureAtLocation == NULL) {
			//its an empty space
			this->setX(this->getTmpX());
			this->setY(this->getTmpY());
			this->pixel.position.x = this->getX();
			this->pixel.position.y = this->getY();
		}
	}
}

void Prey::handleHealth()
{
	this->setHealth(this->getHealth() + 1);
	if (this->getHealth() >= this->maxHealth) {
		this->reproduce();
	}
}

void Prey::reproduce()
{
	//in here reset health back to 1 and then find the nearest random location to spawn a new prey
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//for now if there is no room then wait
			if (i != 1 && j != 1) {
				shared_ptr<Creature> creatureAtLocation = findCreatureAtPos(this->getX() + i, this->getY() + j);
				if (creatureAtLocation == NULL) {
					this->setHealth(1);
					Game::addPrey(this->getX() + i, this->getY() + j);
				}
			}
		}
	}
}
