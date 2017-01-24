/*
	Programmer: Jonathan Galvan
*/

#include "Deer.h"
#include "SquareYard.h"
#include "Wolf.h"


Deer::Deer(int fLevel, int mRate, int age, bool moved, bool action, int chance) {
	this->foodLevel = fLevel;
	this->metabolism = mRate;
	this->currentAge = age;
	this->moved = moved;
	this->action = action;
	this->probChance = chance;
}


void Deer::move(int currX, int currY, int maxX, int maxY, SquareYard**& grid) {

	int i = currX;
	int j = currY;


	int currentGrass;
	bool valid_check = false;
	int mx, my;

	// Check Upwards direction. If valid bunny moves over 
	if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal == NULL && grid[i][j].animal->getMovement() == false) {

		mx = i;
		my = j - 1;
		currentGrass = grid[i][j - 1].grass->getFoodLevel();
		valid_check = true;

	}


	// Check right direction. If valid bunny moves over 
	if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal == NULL && grid[i][j].animal->getMovement() == false) {

		if (valid_check == true) {

			if (currentGrass < grid[i + 1][j].grass->getFoodLevel()) {
				mx = i + 1;
				my = j;
				currentGrass = grid[i + 1][j].grass->getFoodLevel();
			}

		}

		// Make Default
		else {

			mx = i + 1;
			my = j;
			currentGrass = grid[i + 1][j].grass->getFoodLevel();
			valid_check = true;

		}

	}



	// Check Downwards direction. If valid bunny moves over 
	if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal == NULL && grid[i][j].animal->getMovement() == false) {


		if (valid_check == true) {

			if (currentGrass < grid[i][j + 1].grass->getFoodLevel()) {
				mx = i;
				my = j + 1;
				currentGrass = grid[i][j + 1].grass->getFoodLevel();
			}

		}

		// Make Default
		else {

			mx = i;
			my = j + 1;
			currentGrass = grid[i][j + 1].grass->getFoodLevel();
			valid_check = true;

		}


	}



	// Check left direction. If valid bunny moves over 
	if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal == NULL && grid[i][j].animal->getMovement() == false) {

		if (valid_check == true) {

			if (currentGrass < grid[i - 1][j].grass->getFoodLevel()) {
				mx = i - 1;
				my = j;
				currentGrass = grid[i - 1][j].grass->getFoodLevel();
			}

		}

		// Make Default
		else {

			mx = i - 1;
			my = j;
			currentGrass = grid[i - 1][j].grass->getFoodLevel();
			valid_check = true;

		}



	}

	// If true then the bunny is able to move to the grass with the most food level around it
	if (valid_check == true) {

		grid[mx][my].animal = grid[i][j].animal;
		grid[i][j].animal = NULL;

		grid[mx][my].SetInnerSquare(sf::Color::White);
		grid[mx][my].SetOuterSquare(sf::Color::White);

		grid[i][j].SetInnerSquare(sf::Color::Green);
		grid[i][j].SetOuterSquare(sf::Color::Green);

		grid[mx][my].animal->setMovement(true);

		// Evade
		if (grid[mx][my].animal->actionMove(mx, my, maxX, maxY, grid) == true) {
			//Do nothing 
		}

		else {

			// Determine if the animal will eat or not. **Testing**. Works . Check if all statements are included 
			grid[mx][my].animal->animalEats(mx, my, grid);

			//Reproduce. Check if all statements are in if statement 
			grid[mx][my].animal->spawnAnimal(mx, my, i, j, grid, maxX, maxY);
		}
	}


}


// Subtract 6 from food level each day
void Deer::changeFoodLevel() {

	this->foodLevel -= this->metabolism;

}

void Deer::setMovement(bool change) {
	this->moved = change;
}

void Deer::setAction(bool change) {
	this->action = change;
}

void Deer::setHunger(bool) {
	// Do Nothing 
}

bool Deer::checkToKillCreature(int x, int y, SquareYard**& grid, int day) {

	// Deer dies if food level is 0 or reaches 35 days 
	if (grid[x][y].animal->getFoodLevel() <= 0 || day == 35) {
		grid[x][y].animal = NULL;

		grid[x][y].SetInnerSquare(sf::Color::Green);
		grid[x][y].SetOuterSquare(sf::Color::Green);

		return true;
	}


	return false;

}

bool Deer::actionMove(int currX, int currY, int maxX, int maxY, SquareYard **& grid) {

	int i = currX;
	int j = currY;

	int movedX;
	int movedY;

	bool being_chased = false; //True if chased away
	bool pathFound = false; // True if found a "Possible Path" To escape 
	
	// Check All FOUR DIRECTIONS 

	// Checks if a wolf exists on top. ADD LION 
	if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal != NULL) {

		Creature* up = grid[i][j - 1].animal;

		// Checks to see if its a type of Wolf || Lion
		if (dynamic_cast<Wolf *>(up) != 0 && grid[i][j].animal->getFoodLevel() > 15) {

			// Move 3 Left 
			if ((j >= 0 && j < maxY) && (i - 3 >= 0 && i - 3 < maxX) && grid[i - 3][j].animal == NULL) {

				movedX = i - 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}

			else if ((j + 3 >= 0 && j + 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 3].animal == NULL) {

				movedX = i;
				movedY = j + 3;
				pathFound = true;
				being_chased = true;

			}

			else if ((j >= 0 && j < maxY) && (i + 3 >= 0 && i + 3 < maxX) && grid[i + 3][j].animal == NULL) {

				movedX = i + 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}



		}


	}

	// Check if an animal exists on the right. TEST CASE
	if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal != NULL && pathFound != true) {

		Creature* right = grid[i + 1][j].animal;

		// Checks to see if its a type of wolf 
		if (dynamic_cast<Wolf *>(right) != 0 && grid[i][j].animal->getFoodLevel() > 15) {

			if ((j - 3 >= 0 && j - 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 3].animal == NULL) {

				movedX = i;
				movedY = j - 3;
				pathFound = true;
				being_chased = true;

			}

			else if ((j >= 0 && j < maxY) && (i - 3 >= 0 && i - 3 < maxX) && grid[i - 3][j].animal == NULL) {
				movedX = i - 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}

			else if ((j + 3 >= 0 && j + 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 3].animal == NULL) {
				movedX = i;
				movedY = j + 3;
				pathFound = true;
				being_chased = true;
			}

			else {
				// Cant invade can be eaten 
			}

		}

	}

	// Check if an animal exists down. TEST CASE
	if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal != NULL && pathFound != true) {

		Creature* down = grid[i][j + 1].animal;

		// Checks to see if its a type of wolf 
		if (dynamic_cast<Wolf *>(down) != 0 && grid[i][j].animal->getFoodLevel() > 15) {

			if ((j >= 0 && j < maxY) && (i - 3 >= 0 && i - 3 < maxX) && grid[i - 3][j].animal == NULL) {
				movedX = i - 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}

			else if ((j - 3 >= 0 && j - 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 3].animal == NULL) {
				movedX = i;
				movedY = j - 3;
				pathFound = true;
				being_chased = true;
			}

			else if ((j >= 0 && j < maxY) && (i + 3 >= 0 && i + 3 < maxX) && grid[i + 3][j].animal == NULL) {
				movedX = i + 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}

			else {
				//cant invade. Can be eat
			}

		}
	}

	// Check if an animal exists on the left. TEST CASE
	if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal != NULL && pathFound != true) {

		Creature* left = grid[i - 1][j].animal;

		// Checks to see if its a type of wolf 
		if (dynamic_cast<Wolf *>(left) != 0 && grid[i][j].animal->getFoodLevel() > 15) {

			// Move 3 upwards
			if ((j - 3 >= 0 && j - 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 3].animal == NULL) {

				movedX = i;
				movedY = j - 3;
				pathFound = true;
				being_chased = true;
			}

			// Move 3 to the right
			else if ((j >= 0 && j < maxY) && (i + 3 >= 0 && i + 3 < maxX) && grid[i + 3][j].animal == NULL) {

				movedX = i + 3;
				movedY = j;
				pathFound = true;
				being_chased = true;
			}

			// Move 3 bottom
			else if ((j + 3 >= 0 && j + 3 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 3].animal == NULL) {
				movedX = i;
				movedY = j + 3;
				pathFound = true;
				being_chased = true;
			}

		}
	}


	// Moved rabbit to appropiate position. Bunny has been chases and moves away  
	if (being_chased == true && pathFound == true) {

		//cout << "Rabbit Being hunted by a wolf" << endl;

		// Update spots and colors.
		grid[movedX][movedY].animal = grid[currX][currY].animal;
		grid[movedX][movedY].animal->setAction(true);
		grid[currX][currY].animal = NULL;

		grid[movedX][movedY].SetInnerSquare(sf::Color::White);
		grid[movedX][movedY].SetOuterSquare(sf::Color::White);

		grid[currX][currY].SetInnerSquare(sf::Color::Green);
		grid[currX][currY].SetOuterSquare(sf::Color::Green);
		return true;
	}

	return false;
}

void Deer::animalEats(int x, int y, SquareYard **& grid) {

	// Will eat the certain amount of plant food level 

	// Deer able to eat since it did not evade
	if (grid[x][y].animal->getAction() == false) {

		int currentPlantLevel = grid[x][y].grass->getFoodLevel();

		// Deer will only eat however much food the plant has 
		if (currentPlantLevel < 5) {

			grid[x][y].animal->setFoodLevel(currentPlantLevel);
			grid[x][y].grass->setFoodLevel(currentPlantLevel);
			return;
		}

		int foodUpTo = 20;
		int extraFood = 0;

		while (currentPlantLevel > 0) {

			if (currentPlantLevel == 100) {
				extraFood++;
			}

			else if (currentPlantLevel >= 80) {
				extraFood++;
			}

			else if (currentPlantLevel >= 60) {
				extraFood++;
			}

			else if (currentPlantLevel >= 40) {
				extraFood++;
			}

			else if (currentPlantLevel >= 20) {
				extraFood++;
			}

			currentPlantLevel -= 20;
		}

		// Add any extra food if possible 
		foodUpTo += extraFood;

		// Rabbit will not eat if it goes over its max health 
		if (grid[x][y].animal->getFoodLevel() + foodUpTo > 100) {
			return;
		}

		// At this point eats the plant level
		grid[x][y].animal->setFoodLevel(foodUpTo);
		grid[x][y].grass->setFoodLevel(20);

	}



}

void Deer::setFoodLevel(int change) {
	this->foodLevel += change;
}

void Deer::spawnAnimal(int currX, int currY, int prevX, int prevY, SquareYard **& grid, int maxX, int maxY) {

	srand(time(NULL));

	// Randomize probability 
	int probTarget = rand() % 100 + 1;

	int i = currX;
	int j = currY;
	bool wolfPresent = false;
	
	// Deer will be able to reproduce. Since it did not evade 
	if (grid[currX][currY].animal->getAction() == false) {

		// Check up 
		if ((j - 1 >= 0 && j - 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j - 1].animal != NULL) {
			Creature *up = grid[currX][currY - 1].animal;

			if (dynamic_cast<Wolf*>(up) != 0) {
				wolfPresent = true;
			}

		}

		if ((j >= 0 && j < maxY) && (i + 1 >= 0 && i + 1 < maxX) && grid[i + 1][j].animal != NULL) {
			Creature *right = grid[currX + 1][currY].animal;

			if (dynamic_cast<Wolf*>(right) != 0 && wolfPresent != true) {
				wolfPresent = true;
			}

		}

		if ((j + 1 >= 0 && j + 1 < maxY) && (i >= 0 && i < maxX) && grid[i][j + 1].animal != NULL) {
			Creature *down = grid[currX][currY + 1].animal;

			if (dynamic_cast<Wolf*>(down) != 0 && wolfPresent != true) {
				wolfPresent = true;
			}

		}

		if ((j >= 0 && j < maxY) && (i - 1 >= 0 && i - 1 < maxX) && grid[i - 1][j].animal != NULL) {
			Creature *left = grid[currX - 1][currY].animal;

			if (dynamic_cast<Wolf*>(left) != 0 && wolfPresent != true) {
				wolfPresent = true;
			}

		}


		// Reproduce if no carnivores found in its surroundings
		if (wolfPresent == false && grid[currX][currY].animal->getProb() == probTarget && grid[prevX][prevY].animal == NULL && grid[currX][currY].animal->getAge() >= 10 && grid[currX][currY].animal->getFoodLevel() >= 40) {

			// Create new Deer :). Has Age 1 
			grid[prevX][prevY].animal = new Deer(30, 6, 1, false, false, 30);
			grid[prevX][prevY].SetInnerSquare(sf::Color::White);
			grid[prevX][prevY].SetOuterSquare(sf::Color::White);
		}

	}

}

bool Deer::huntAction(int, int, int, int, SquareYard **&) {
	// Do Nothing 
	return false;
}