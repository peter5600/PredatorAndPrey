#pragma once
#include <memory>
using namespace std;

class Creature;//forward decleration

int const WIDTH = 300;
int const HEIGHT = 200;
extern shared_ptr<Creature> creatures[WIDTH][HEIGHT];