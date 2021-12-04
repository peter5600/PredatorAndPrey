#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>//rand()
#include "GlobalSettings.h"
#include <memory>
#include <random>

using namespace std;

class Creature {
public: 
	Creature(sf::Vertex pixel, unsigned int x, unsigned int y);
	sf::Vertex pixel;
	unsigned int getX();
	unsigned int getY();
private:
	unsigned int x;
	unsigned int y;
	unsigned int tmpX;
	unsigned int tmpY;
	int health;
	
protected:
	virtual void getMove();//Adding virtual makes the entire class polymorphic and works with dynamic cast
	unsigned int getTmpY();
	unsigned int getTmpX();
	void setTmpX(int val);
	void setTmpY(int val);
	void setX(int val);
	void setY(int val);
	shared_ptr<Creature> findCreatureAtPos(unsigned int x, unsigned int y);
	void setHealth(int val);
	int getHealth();
	const int maxHealth = 10;//const can be assigned in h file
	

};