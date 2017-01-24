/*
	Programmer: Jonathan Galvan
*/

#ifndef Grass_H
#define Grass_H

#include "Creature.h"


class Land; // Foward Declaration

class Grass : public Creature {

public:
	Grass(int, int);

	void move(int, int,int,int, SquareYard**&);
	void changeFoodLevel();
	bool checkGrassObject(Creature*);
	void setMovement(bool);
	bool checkToKillCreature(int, int, SquareYard**&, int);
	bool actionMove(int, int, int, int, SquareYard **&);
	void setAction(bool);
	void animalEats(int, int, SquareYard **&);
	void setFoodLevel(int);
	void spawnAnimal(int, int, int, int, SquareYard **&, int, int);
	bool huntAction(int, int, int, int, SquareYard **&);
	void setHunger(bool);

};
#endif