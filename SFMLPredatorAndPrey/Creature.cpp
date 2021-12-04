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
	
	int direction = 1 + rand() % 100;//1 - 100
	
	if (direction <= 50) {
		//left and right
		direction = 1 + rand() % 100;//1 - 100
		if (direction <= 50) {
			//left
			this->setTmpX(this->getTmpX() - 1);
		}
		else {
			//right
			this->setTmpX(this->getTmpX() + 1);
		}
	}
	else {
		direction = 1 + rand() % 100;//1 - 100
		//up and down
		if (direction <= 50) {
			//up
			this->setTmpY(this->getTmpY() - 1);
		}
		else {
			//down
			this->setTmpY(this->getTmpY() + 1);
		}
	}
}

void Creature::Move()
{
	//cout << "hello";
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
