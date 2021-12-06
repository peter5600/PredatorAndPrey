#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <functional>//for std::bind
#include <memory>
#include <thread>
#include <future>         // std::async, std::future
#include <stdlib.h>
#include <iostream>
#include "Creature.h"
#include "Predator.h"
#include "Prey.h"
#include "GlobalSettings.h"
using namespace std;


//has to be static and has to be outside the local scope so that its 
//put on the heap instead of the stack because the stack has a limit that this exceeds
//also has to be static so that I can access it from creature
class Game {
public: 
	Game();
	void run();
	static void addPredator(unsigned int x, unsigned int y);
	static void removeCreature(unsigned int x, unsigned int y);
	static void addPrey(unsigned int x, unsigned int y);
private:
	void pollEvents();
	sf::RenderWindow window;
	vector<sf::Vertex> pixels;
	void handlePixelsVector();
	void handleCreatures(int minX, int minY, int maxX, int maxY);
};