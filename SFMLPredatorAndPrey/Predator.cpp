#include "Predator.h"

Predator::Predator(sf::Vertex pixel, unsigned int x, unsigned int y) : Creature(pixel, x, y){
	this->setHealth(this->maxHealth);
}

void Predator::Move()
{
	//cout << "pred test " << endl;
	this->getMove();//this will set tmpX and tmpY so that i can try moving there
	if (this->getTmpX() != this->getX() || this->getTmpY() != this->getY()) {
		shared_ptr<Creature> creatureAtLocation= findCreatureAtPos(this->getTmpX(), this->getTmpY());
		if (creatureAtLocation == NULL) {
			//its an empty space
			this->setX(this->getTmpX());
			this->setY(this->getTmpY());
			this->pixel.position.x = this->getX();
			this->pixel.position.y = this->getY();
		}
		else {
			//its either predator or prey
			shared_ptr<Prey> preyCreature = dynamic_pointer_cast<Prey>(creatureAtLocation);
			if (preyCreature) {
				//its a prey in this location
				Game::addPredator(this->getTmpX(), this->getTmpY());
			}
		}

	}
}

void Predator::handleHealth()
{
	this->setHealth(this->getHealth()-1);
	
	if (this->getHealth() <= 0) {
		this->die();
	}
}

void Predator::die()
{
	Game::removeCreature(this->getX(), this->getY());
}
