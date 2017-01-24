/*
	Programmer: Jonathan Galvan
*/

#include "Creature.h"
#include <iostream>
using namespace std;

// Returns food level of each creature
int Creature::getFoodLevel() {
	return this->foodLevel;
}

// Returns current age of each Creature
int Creature::getAge() {
	return this->currentAge;
}

bool Creature::getMovement() {
	return this->moved;
}

bool Creature::getAction() {
	return this->action;
}

bool Creature::getHunger() {
	return this->hungry;
}

void Creature::increaseAge() {
	this->currentAge++;
}

void Creature::resetMove() {
	this->moved = false;
}

void Creature::resetAction() {
	this->action = false;
}

void Creature::resetHunger() {
	this->hungry = false;
}

int Creature::getProb() {
	return this->probChance;
}