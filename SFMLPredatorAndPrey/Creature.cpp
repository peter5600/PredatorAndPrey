#include "Creature.h"
using namespace std;

Creature::Creature(sf::Vertex pixel, unsigned int x, unsigned int y)
{
	this->pixel = pixel;
	this->x = x;
	this->y = y;
}

void Creature::getMove()
{

	this->setTmpX(this->getX());
	this->setTmpY(this->getY());
	//add collision
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-1, 1);
	this->setTmpX(this->getTmpX() + dis(gen));
	this->setTmpY(this->getTmpY() + dis(gen));
}

//give each predator and prey its own move and call this something else

void Creature::setX(int val)
{
	if (val >= 0 && val < WIDTH) {
		this->x = val;
	}
}

unsigned int Creature::getX()
{
	return this->x;
}

void Creature::setY(int val)
{
	if (val >= 0 && val < HEIGHT) {
		this->y = val;
	}
}

unsigned int Creature::getY()
{
	return this->y;
}

shared_ptr<Creature> Creature::findCreatureAtPos(unsigned int x, unsigned int y)
{
	return creatures[x][y];
}

void Creature::setHealth(int val)
{
	this->health = val;
}

int Creature::getHealth()
{
	return this->health;
}

//tmpX and tmpY are where the creature will go before i move it
void Creature::setTmpX(int val)
{
	if (val >= 0 && val < WIDTH) {
		this->tmpX = val;
	}
}

unsigned int Creature::getTmpX()
{
	return this->tmpX;
}

void Creature::setTmpY(int val)
{
	if (val >= 0 && val < HEIGHT) {
		this->tmpY = val;
	}
}

unsigned int Creature::getTmpY()
{
	return this->tmpY;
}

