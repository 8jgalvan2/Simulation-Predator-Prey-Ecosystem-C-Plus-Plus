/*
	Programmer: Jonathan Galvan
*/

#include "Grass.h"

Grass::Grass(int fLevel, int mRate) {
	this->foodLevel = fLevel;
	this->metabolism = mRate;
}

void Grass::move(int x, int y, int mX, int mY, SquareYard**& board) {
	//Do Nothing
}

void Grass::changeFoodLevel() {

	this->foodLevel += this->metabolism;

	if (this->foodLevel > 100) {
		this->foodLevel = 100;
	}

}

bool Grass::checkGrassObject(Creature * a) {

	Grass* grassObj;

	grassObj = dynamic_cast<Grass *>(a);

	if (grassObj == 0) {
		return true;
	}

	else {
		return false;
	}

}

void Grass::setMovement(bool change) {
	// Do Nothing
}

bool Grass::checkToKillCreature(int x, int y, SquareYard**&, int a) {
	//Do Nothing
	return false;
}

bool Grass::actionMove(int x, int y, int mX, int mY, SquareYard **& grid) {
	//Do nothing
	return false;
}

void Grass::setAction(bool action) {
	//Do nothing
}

void Grass::animalEats(int x, int y, SquareYard **& grid) {
	// Do nothing 
}

void Grass::setFoodLevel(int change) {
	this->foodLevel -= change;

	if (this->foodLevel < 0) {
		this->foodLevel = 0;
	}

}

void Grass::spawnAnimal(int x, int y, int prevX, int prevY, SquareYard **& grid, int, int) {
	// Do nothing 
}

bool Grass:: huntAction(int, int, int, int, SquareYard **&) {
	// Do nothing 
	return false;
}

void Grass::setHunger(bool) {
	//Do nothing
}