/*
	Programmer: Jonathan Galvan
*/

#include "Wolf.h"
#include "SquareYard.h"

using namespace std;
#include "Rabbit.h";
#include "Deer.h"

Wolf::Wolf(int fLevel, int mRate, int age, bool moved, bool action, int chance, bool hasAte) {
	this->foodLevel = fLevel;
	this->metabolism = mRate;
	this->currentAge = age;
	this->moved = moved;
	this->action = action;
	this->probChance = chance;
	this->hungry = hasAte;
}

bool Wolf:: huntAction(int currX, int currY, int maxX, int maxY, SquareYard **& grid) {
	
	int i = currX;
	int j = currY;

	int movedX;
	int movedY;

	bool canEat = false;


	// Check up 
	if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal != NULL) {
		Creature *up = grid[currX][currY - 1].animal;

		if (dynamic_cast<Rabbit*>(up) != 0 || dynamic_cast<Deer*>(up) != 0) {

			movedX = i;
			movedY = j - 1;
			canEat = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal != NULL) {
		Creature *right = grid[currX + 1][currY].animal;

		if (dynamic_cast<Rabbit*>(right) != 0 || dynamic_cast<Deer*>(right) != 0 && canEat != true) {
			
			movedX = i + 1;
			movedY = j;
			canEat = true;
		}

	}

	if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal != NULL) {
		Creature *down = grid[currX][currY + 1].animal;

		if (dynamic_cast<Rabbit*>(down) != 0 || dynamic_cast<Deer*>(down) != 0 && canEat != true) {

			movedX = i;
			movedY = j + 1;
			canEat = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal != NULL) {
		Creature *left = grid[currX - 1][currY].animal;

		if (dynamic_cast<Rabbit*>(left) != 0 || dynamic_cast<Deer*>(left) != 0 && canEat != true) {
			
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
		grid[movedX][movedY].animal->setFoodLevel(10);
		

		//Animation
		grid[movedX][movedY].SetInnerSquare(sf::Color::Red);
		grid[movedX][movedY].SetOuterSquare(sf::Color::Red);

		grid[i][j].SetInnerSquare(sf::Color::Green);
		grid[i][j].SetOuterSquare(sf::Color::Green);
		return true;
	}


	return false;
}

void Wolf::move(int currX, int currY, int maxX, int maxY, SquareYard**& grid) {

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

			if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i + 1;
				my = j;
				ableToMove = true;
			}

			if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i;
				my = j + 1;
				ableToMove = true;

			}

			if (ableToMove == true) {

				grid[mx][my].animal = grid[i][j].animal;
				grid[i][j].animal = NULL;

				grid[mx][my].SetInnerSquare(sf::Color::Red);
				grid[mx][my].SetOuterSquare(sf::Color::Red);

				grid[i][j].SetInnerSquare(sf::Color::Green);
				grid[i][j].SetOuterSquare(sf::Color::Green);

				grid[mx][my].animal->setMovement(true);
			
				//Spawns another wolf
				grid[mx][my].animal->spawnAnimal(mx,my,i,j,grid,maxX,maxY);


			}


		}

	}

}

void Wolf::changeFoodLevel() {
	this->foodLevel -= this->metabolism;

}

void Wolf::setMovement(bool change) {
	this->moved = change;
}

void Wolf::setAction(bool change) {
	this->action = change;
}

void Wolf::setHunger(bool change) {
	this->hungry= change;
}

bool Wolf::checkToKillCreature(int x, int y, SquareYard **& grid, int day) {


	// Wolf dies if food level is 0 or reaches 25 days  
	if (grid[x][y].animal->getFoodLevel() <= 0 || day == 50) {
		grid[x][y].animal = NULL;

		grid[x][y].SetInnerSquare(sf::Color::Green);
		grid[x][y].SetOuterSquare(sf::Color::Green);

		return true;
	}

	return false;
}

bool Wolf::actionMove(int currX, int currY, int maxX, int maxY, SquareYard **&) {
	// DO NOTHING AT THE MOMENT;
	return false;
}

void Wolf::animalEats(int x, int y, SquareYard **& grid) {
	// Did the implemation on hunt action
}

void Wolf::setFoodLevel(int change) {
	this->foodLevel += change;
}

void Wolf::spawnAnimal(int currX, int currY, int prevX, int prevY, SquareYard **& grid, int maxX, int maxY) {
	
	srand(time(NULL));

	// Randomize probability 
	int probTarget = rand() % 100 + 1;

	int i = currX;
	int j = currY;
	 

		// Reproduce if no carnivores found in its surroundings
		if (grid[currX][currY].animal->getProb() == probTarget && grid[prevX][prevY].animal == NULL && grid[currX][currY].animal->getAge() >= 10 && grid[currX][currY].animal->getFoodLevel() >= 120) {

			// Create new Bunny :). Has Age 1 
			grid[prevX][prevY].animal = new Wolf(150, 2, 1, false, false, 40,false);
			grid[prevX][prevY].SetInnerSquare(sf::Color::Red);
			grid[prevX][prevY].SetOuterSquare(sf::Color::Red);
		}

	
}