/*
	Programmer: Jonathan Galvan
*/

#include "Eagle.h"
#include "SquareYard.h"

using namespace std;
#include "Rabbit.h";

Eagle::Eagle(int fLevel, int mRate, int age, bool moved, bool action, int chance, bool hasAte) {
	this->foodLevel = fLevel;
	this->metabolism = mRate;
	this->currentAge = age;
	this->moved = moved;
	this->action = action;
	this->probChance = chance;
	this->hungry = hasAte;
}

bool Eagle::huntAction(int currX, int currY, int maxX, int maxY, SquareYard **& grid) {

	int i = currX;
	int j = currY;

	int movedX;
	int movedY;

	bool rabbitExists = false;


	// Check up 
	if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal != NULL) {
		Creature *up = grid[currX][currY - 1].animal;

		if (dynamic_cast<Rabbit*>(up) != 0) {

			movedX = i;
			movedY = j - 1;
			rabbitExists = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal != NULL) {
		Creature *right = grid[currX + 1][currY].animal;

		if (dynamic_cast<Rabbit*>(right) != 0 && rabbitExists != true) {

			movedX = i + 1;
			movedY = j;
			rabbitExists = true;
		}

	}

	if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal != NULL) {
		Creature *down = grid[currX][currY + 1].animal;

		if (dynamic_cast<Rabbit*>(down) != 0 && rabbitExists != true) {

			movedX = i;
			movedY = j + 1;
			rabbitExists = true;
		}

	}

	if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal != NULL) {
		Creature *left = grid[currX - 1][currY].animal;

		if (dynamic_cast<Rabbit*>(left) != 0 && rabbitExists != true) {

			movedX = i - 1;
			movedY = j;
			rabbitExists = true;
		}

	}

	// Eagle will eat the rabbit 
	if (rabbitExists == true) {

		grid[movedX][movedY].animal = NULL;
		grid[movedX][movedY].animal = grid[i][j].animal;

		grid[i][j].animal = NULL;
		grid[movedX][movedY].animal->setFoodLevel(20);
		
		//Animation
		grid[movedX][movedY].SetInnerSquare(sf::Color::Magenta);
		grid[movedX][movedY].SetOuterSquare(sf::Color::Magenta);

		grid[i][j].SetInnerSquare(sf::Color::Green);
		grid[i][j].SetOuterSquare(sf::Color::Green);
		return true;
	}


	return false;
}

void Eagle::move(int currX, int currY, int maxX, int maxY, SquareYard**& grid) {
	
	int i = currX;
	int j = currY;

	if (grid[currX][currY].animal->huntAction(currX, currY, maxX, maxY, grid) == true) {
		//At this point we know the Eagle ate 
	}

	else {

		// If not hunted
		if (grid[currX][currY].animal->getAction() == false) {

			bool ableToMove = false;
			int mx;
			int my;

			if ((j - 2 >= 0 && j - 2 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 2].animal == NULL && grid[i][j].animal->getMovement() == false) {

				mx = i;
				my = j - 2;
				ableToMove = true;

			}

			if ((j >= 0 && j < maxY) && (i - 2 >= 0 && i - 2 < maxX) && grid[i - 2][j].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i - 2;
				my = j;
				ableToMove = true;
			}

			if ((j + 2 >= 0 && j + 2 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 2].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i;
				my = j + 2;
				ableToMove = true;

			}

			if ((j >= 0 && j < maxY) && (i + 2 >= 0 && i + 2 < maxX) && grid[i + 2][j].animal == NULL && grid[i][j].animal->getMovement() == false && ableToMove != true) {

				mx = i + 2;
				my = j;
				ableToMove = true;
			}

			if (ableToMove == true) {

				grid[mx][my].animal = grid[i][j].animal;
				grid[i][j].animal = NULL;

				grid[mx][my].SetInnerSquare(sf::Color::Magenta);
				grid[mx][my].SetOuterSquare(sf::Color::Magenta);

				grid[i][j].SetInnerSquare(sf::Color::Green);
				grid[i][j].SetOuterSquare(sf::Color::Green);

				grid[mx][my].animal->setMovement(true);

				//Spawns another wolf
				grid[mx][my].animal->spawnAnimal(mx, my, i, j, grid, maxX, maxY);


			}

		}

	}

}

void Eagle::changeFoodLevel() {
	this->foodLevel -= this->metabolism;

}

void Eagle::setMovement(bool change) {
	this->moved = change;
}

void Eagle::setAction(bool change) {
	this->action = change;
}

void Eagle::setHunger(bool change) {
	this->hungry = change;
}

bool Eagle::checkToKillCreature(int x, int y, SquareYard **& grid, int day) {


	// Eagle dies if food level is 0 or reaches 60 days  
	if (grid[x][y].animal->getFoodLevel() <= 0 || day == 60) {
		grid[x][y].animal = NULL;

		grid[x][y].SetInnerSquare(sf::Color::Green);
		grid[x][y].SetOuterSquare(sf::Color::Green);

		return true;
	}

	return false;
}

bool Eagle::actionMove(int currX, int currY, int maxX, int maxY, SquareYard **&) {
	// DO NOTHING AT THE MOMENT;
	return false;
}

void Eagle::animalEats(int x, int y, SquareYard **& grid) {
	// Did the implemation on hunt action
}

void Eagle::setFoodLevel(int change) {
	this->foodLevel += change;
}

void Eagle::spawnAnimal(int currX, int currY, int prevX, int prevY, SquareYard **& grid, int maxX, int maxY) {

	srand(time(NULL));

	// Randomize probability 
	int probTarget = rand() % 100 + 1;

	int i = currX;
	int j = currY;


	// Reproduce if no carnivores found in its surroundings
	if (grid[currX][currY].animal->getProb() == probTarget && grid[prevX][prevY].animal == NULL && grid[currX][currY].animal->getAge() >= 10 && grid[currX][currY].animal->getFoodLevel() >= 40) {

		// Create new Bunny :). Has Age 1 
		grid[prevX][prevY].animal = new Eagle(100, 4, 1, false, false, 50, false);
		grid[prevX][prevY].SetInnerSquare(sf::Color::Magenta);
		grid[prevX][prevY].SetOuterSquare(sf::Color::Magenta);
	}


}