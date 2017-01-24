/*
	Programmer: Jonathan Galvan
*/

#ifndef CREATURE_H
#define CREATURE_H

// Foward Declaration 
class SquareYard;


class Creature {

protected:

	int foodLevel;
	int metabolism;
	
	// Unused at the moment
	int positionX;
	int positiony;

	int currentAge;
	int probChance;
	bool moved;

	// Bunny Action = evade , Wolf Action = chase
	bool action;
	bool hungry;

public:

	virtual void move(int, int, int, int, SquareYard **&) = 0;
	
	// Keep this. Easier to retrieve current level of each Creature object
	int getFoodLevel();
	int getAge();
	void increaseAge();
	void resetMove();
	void resetAction();
	void resetHunger();
	int getProb();

	// Checks to see if the creatures has moved
	bool getMovement();

	// Checks to see if the animal has made an action. Rabbit(Moved), Wolf(Hunted)
	bool getAction();

	bool getHunger();

	virtual void setMovement(bool) = 0;
	virtual void setAction(bool) = 0;
	virtual void setHunger(bool) = 0;


	virtual void changeFoodLevel() = 0;
	virtual void setFoodLevel(int) = 0;

	virtual bool checkToKillCreature(int, int, SquareYard **&, int) = 0;

	virtual bool actionMove(int, int, int, int, SquareYard **&) = 0;
	
	virtual void animalEats(int, int, SquareYard **&) = 0;

	virtual void spawnAnimal(int, int, int, int, SquareYard **&, int, int) = 0;

	virtual bool huntAction(int, int, int, int, SquareYard **&) = 0;

};
#endif