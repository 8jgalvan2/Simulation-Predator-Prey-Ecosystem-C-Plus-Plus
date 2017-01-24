/*
	Programmer: Jonathan Galvan
*/

#include "Lion.h"
#include "SquareYard.h"

using namespace std;
#include "Wolf.h";
#include "Deer.h"

Lion::Lion(int fLevel, int mRate, int age, bool moved, bool action, int chance, bool hasAte) {
	this->foodLevel = fLevel;
	this->metabolism = mRate;
	this->currentAge = age;
	this->moved = moved;
	this->action = action;
	this->probChance = chance;
	this->hungry = hasAte;
}

bool Lion::huntAction(int currX, int currY, int maxX, int maxY, SquareYard **& grid) {

	int i = currX;
	int j = currY;

	int movedX;
	int movedY;

	bool canEat = false;


	// Check up 
	if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal != NULL) {
		Creature *up = grid[currX][currY - 1].animal;

		if (dynamic_cast<Wolf*>(up) != 0 || dynamic_cast<Deer*>(up) != 0) {

			movedX = i;
			movedY = j - 1;
			canEat = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal != NULL) {
		Creature *right = grid[currX + 1][currY].animal;

		if (dynamic_cast<Wolf*>(right) != 0 || dynamic_cast<Deer*>(right) != 0 && canEat != true) {

			movedX = i + 1;
			movedY = j;
			canEat = true;
		}

	}

	if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal != NULL) {
		Creature *down = grid[currX][currY + 1].animal;

		if (dynamic_cast<Wolf*>(down) != 0 || dynamic_cast<Deer*>(down) != 0 && canEat != true) {

			movedX = i;
			movedY = j + 1;
			canEat = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal != NULL) {
		Creature *left = grid[currX - 1][currY].animal;

		if (dynamic_cast<Wolf*>(left) != 0 || dynamic_cast<Deer*>(left) != 0 && canEat != true) {

			movedX = i - 1;
			movedY = j;
			canEat = true;
		}

	}

	// Wolf will eat the rabbit 
	if (canEat == true) {

		grid[movedX][movedY].animal = NULL;
		grid[movedX][movedY].animal = grid[i][j].animal;

		grid[i][j].animal = NULL;
		grid[movedX][movedY].animal->setFoodLevel(30);
		//grid[movedX][movedY].animal->setHunger(false);

		//Animation
		grid[movedX][movedY].SetInnerSquare(sf::Color::Yellow);
		grid[movedX][movedY].SetOuterSquare(sf::Color::Yellow);

		grid[i][j].SetInnerSquare(sf::Color::Green);
		grid[i][j].SetOuterSquare(sf::Color::Green);
		return true;
	}


	return false;
}

void Lion::move(int currX, int currY, int maxX, int maxY, SquareYard**& grid) {
	 

	int i = currX;
	int j = currY;

	if (grid[currX][currY].animal->huntAction(currX, currY, maxX, maxY, grid) == true) {
		//At this point we know the wolf ate 
	}

	else {

		// If not hunted
		if (grid[currX][currY].animal->getAction() == false) {

			bool ableToMove = false;
			int mx;
			int my;

			if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal == NULL && grid[i][j].animal->getMovement() == false) {

				mx = i;
				my = j - 1;
				ableToMove = true;

			}

			if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i - 1;
				my = j;
				ableToMove = true;
			}

			if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i;
				my = j + 1;
				ableToMove = true;

			}

			if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i + 1;
				my = j;
				ableToMove = true;
			}

			if (ableToMove == true) {

				grid[mx][my].animal = grid[i][j].animal;
				grid[i][j].animal = NULL;

				grid[mx][my].SetInnerSquare(sf::Color::Yellow);
				grid[mx][my].SetOuterSquare(sf::Color::Yellow);

				grid[i][j].SetInnerSquare(sf::Color::Green);
				grid[i][j].SetOuterSquare(sf::Color::Green);

				grid[mx][my].animal->setMovement(true);

				//Spawns another wolf
				grid[mx][my].animal->spawnAnimal(mx, my, i, j, grid, maxX, maxY);


			}


		}

	}


}

void Lion::changeFoodLevel() {
	this->foodLevel -= this->metabolism;

}

void Lion::setMovement(bool change) {
	this->moved = change;
}

void Lion::setAction(bool change) {
	this->action = change;
}

void Lion::setHunger(bool change) {
	this->hungry = change;
}

bool Lion::checkToKillCreature(int x, int y, SquareYard **& grid, int day) {


	// Lion dies if food level is 0 or reaches 25 days  
	if (grid[x][y].animal->getFoodLevel() <= 0 || day == 80) {
		grid[x][y].animal = NULL;

		grid[x][y].SetInnerSquare(sf::Color::Green);
		grid[x][y].SetOuterSquare(sf::Color::Green);

		return true;
	}

	return false;
}

bool Lion::actionMove(int currX, int currY, int maxX, int maxY, SquareYard **&) {
	// DO NOTHING
	return false;
}

void Lion::animalEats(int x, int y, SquareYard **& grid) {
	// Did the implemation on hunt action 
}

void Lion::setFoodLevel(int change) {
	this->foodLevel += change;
}

void Lion::spawnAnimal(int currX, int currY, int prevX, int prevY, SquareYard **& grid, int maxX, int maxY) {

	srand(time(NULL));

	// Randomize probability 
	int probTarget = rand() % 100 + 1;

	int i = currX;
	int j = currY;


	// Reproduce if no carnivores found in its surroundings
	if (grid[currX][currY].animal->getProb() == probTarget && grid[prevX][prevY].animal == NULL && grid[currX][currY].animal->getAge() >= 20 && grid[currX][currY].animal->getFoodLevel() >= 150) {

		// Create new Bunny :). Has Age 1 
		grid[prevX][prevY].animal = new Lion(300, 5, 1, false, false, 30, false);
		grid[prevX][prevY].SetInnerSquare(sf::Color::Red);
		grid[prevX][prevY].SetOuterSquare(sf::Color::Red);
	}


}

// Lion HP 300 M 5