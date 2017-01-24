/*
	Programmer: Jonathan Galvan
*/

#ifndef EAGLE_H
#define EAGLE_H

#include "Creature.h"

class Eagle: public Creature {

public:

	Eagle(int, int, int, bool, bool, int, bool);

	void move(int, int, int, int, SquareYard**&);
	void changeFoodLevel();

	void setMovement(bool);
	void setAction(bool);
	void setHunger(bool);

	bool checkToKillCreature(int, int, SquareYard**&, int);
	bool actionMove(int, int, int, int, SquareYard **&);
	void animalEats(int, int, SquareYard **&);
	void setFoodLevel(int);
	void spawnAnimal(int, int, int, int, SquareYard **&, int, int);
	bool huntAction(int, int, int, int, SquareYard **&);

};

#endif