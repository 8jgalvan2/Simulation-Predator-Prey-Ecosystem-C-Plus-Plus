/*
	Programmer: Jonathan Galvan
*/

#ifndef DEER_H
#define DEER_H

#include "Creature.h"


class Deer :public Creature {

public:

	Deer(int, int, int, bool, bool, int);

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