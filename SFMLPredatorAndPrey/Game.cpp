#include "Game.h"
using namespace std;

/*
Rules:
-For prey:
-Tries to move in a random direction.
-Health increases.
-When health reaches a threshold:
-They will reproduce, creating a new "Prey"
-Their health resets to 1

-For predator:
-Tries to move in a random direction.
-Health decreases.
-When health reaches 0, they die and turn into "Nothing".
-If the adjacent square is a prey:
-They will eat it, turning it into a "predator" (reproducing)
-Their health will increase by the amount of health the eaten prey had

Prey health increases once it reaches a threashold it reproduces and their health resets to default value
Predator health decreases once it reaches zero it dies
if predator moves onto the prey it will reproduce and steal the preys remaning health

it still has the bias and if i leave it on without the ability to reproduce, kill or die then they always get stuck in top left 
test this otherwise i might generate the same results everytime

the position of the death function can significantly change how the game is played so play around with moving it around so that 
creatures can perform their action then do a health check etc

Things to do:
to optimise see how well hopsons videos run
remove redundant functions that creature dosen't use but predator and prey do
it is still possible for all predators to die but for now it seems that is unlikely so for now should be fine
test the game using the release API to check if its any faster or breaks
*/

shared_ptr<Creature> creatures[WIDTH][HEIGHT];

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Predator and Prey"),
			   pixels(WIDTH * HEIGHT)//What is this
{
	
	window.setFramerateLimit(60);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 1000);//look into whether this still makes it unique
	for (float x = 0; x < WIDTH; x++) {
		for (float y = 0; y < HEIGHT; y++) {
			int n = dis(gen);
			if (n < 50) {
				//predator
				sf::Vertex tmpPixel;
				tmpPixel.position = { x,y };
				tmpPixel.color = { 255, 0, 0 };
				shared_ptr<Predator> predator = make_shared<Predator>(tmpPixel, x, y);
				creatures[(int)x][(int)y] = predator;
			}
			else if (n < 100) {
				//prey
				sf::Vertex tmpPixel;
				tmpPixel.position = { x,y };
				tmpPixel.color = { 0, 255, 0 };
				shared_ptr<Prey> prey = make_shared<Prey>(tmpPixel, x, y);
				creatures[(int)x][(int)y] = prey;
			}
		}
	}
}

void Game::run() {
	sf::Clock clock; // starts the clock
	while (window.isOpen())
	{
		window.clear();
		handleCreatures();
		handlePixelsVector();
		window.draw(pixels.data(), pixels.size(), sf::Points);
		window.display();
		pollEvents();
		sf::Time elapsed1 = clock.getElapsedTime();
		std::cout << 1.f / elapsed1.asSeconds() << "FPS" << std::endl;
		clock.restart();
	}
}

void Game::addPredator(unsigned int x, unsigned int y)
{
	if ((x >= 0 && x <= WIDTH) && (y > 0 && y < HEIGHT)) {
		sf::Vertex tmpPixel;
		tmpPixel.position = { (float)x,(float)y };
		tmpPixel.color = { 255, 0, 0 };
		shared_ptr<Predator> predator = make_shared<Predator>(tmpPixel, x, y);
		creatures[x][y] = predator;
	}
}

void Game::addPrey(unsigned int x, unsigned int y)
{
	if ((x >= 0 && x <= WIDTH) && (y > 0 && y < HEIGHT)) {
		sf::Vertex tmpPixel;
		tmpPixel.position = { (float)x, (float)y };
		tmpPixel.color = { 0, 255, 0 };
		shared_ptr<Prey> prey = make_shared<Prey>(tmpPixel, x, y);
		creatures[x][y] = prey;
	}
}

void Game::removeCreature(unsigned int x, unsigned int y)
{
	creatures[x][y] = NULL;
}

void Game::pollEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::handlePixelsVector()
{
	pixels.clear();
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			if (creatures[x][y] != NULL) {
				pixels.push_back(creatures[x][y]->pixel);
			}
		}
	}
}

void Game::handleCreatures()
{
	//Call all of the behaviour in here
	for (int x = 0; x < WIDTH; x++) {//for performance i could store them in a vector and 2d array so that i know which to check instead of doing the null check
		for (int y = 0; y < HEIGHT; y++) {
			if (creatures[x][y] != NULL) {
				//This defeats the point of having different classes if i have to do multiple if statements to 
				//check which one it is try to get something like finalTakeoutApp working
				
				shared_ptr<Prey> derivedCreature = dynamic_pointer_cast<Prey>(creatures[x][y]);
				if (derivedCreature) {
					derivedCreature->Move();
					creatures[x][y] = NULL;
					creatures[derivedCreature->getX()][derivedCreature->getY()] = derivedCreature;
					derivedCreature->handleHealth();
				}
				else {
					shared_ptr<Predator> derivedCreature = dynamic_pointer_cast<Predator>(creatures[x][y]);
					derivedCreature->Move();
					creatures[x][y] = NULL;
					creatures[derivedCreature->getX()][derivedCreature->getY()] = derivedCreature;
					derivedCreature->handleHealth();//for now has to be here otherwise its added back
					
				}
			}
		}
	}
}


