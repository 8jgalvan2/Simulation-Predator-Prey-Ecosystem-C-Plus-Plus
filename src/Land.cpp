//
//  Land.cpp
//	Programmer: Jonathan Galvan
//	Copyright © 2016 UIC. All rights reserved.
//

#include "Land.h"

// Include every Header Creature 
#include "Grass.h"
#include "Rabbit.h"
#include "Deer.h"
#include "Wolf.h"
#include "Eagle.h"
#include "Lion.h"
#include "Windows.h"

using std::cout;
using std::endl;

// Default Constructor
Land::Land(){

}
Land::~Land(){
	if (Y>0) {
		for (int j = 0; j<X; j++) {
			delete[] Yard[j];
		}
	}
	delete[] Yard;
}

// Constructor for Land object
Land::Land(int horizontalSquares, int VerticalSquares, sf::RenderWindow &w, int initialDay){
	X = horizontalSquares;
	Y = VerticalSquares;
	float xOffset = 0;
	float yOffset = 0;

	float dx = (float(w.getSize().x) / float(horizontalSquares));
	float dy = (float(w.getSize().y) / float(VerticalSquares));

	
	//Allocate the array
	Yard = new SquareYard*[X];
	for (int i = 0; i < X; ++i){
		Yard[i] = new SquareYard[Y];
	}


	// Initialize all the Creature objects here with rand

	//Setup the default state.
	for (int j = 0; j<Y; j++) {
		xOffset = 0;
		for (int i = 0; i<X; i++) {
			
			// Sets the square tiles to Green but does not draw them yet. Look at Main.cpp 
			Yard[i][j].set(xOffset, yOffset, dx, dy);
			Yard[i][j].grass = new Grass(20,1);
			Yard[i][j].animal = NULL;
			xOffset += dx;
		}
		yOffset += dy;
	}
	

	// Setup Animal Objects on board 

	// Initialize random seed
	srand(time(NULL));
	
	int randomX = 0;
	int randomY = 0;
	
	// 20 Total Herbivores
	int numberRabbits = 0;
	
	// Add carnivores later
	int numberWolfs = 0;

	int numberDeers = 0;

	int numberEagles = 0;

	int numberLions = 0;
	
	// Create and insert 15 bunnies
	while (numberRabbits < 15) {

		randomX = rand() % 40;
		randomY = rand() % 30;
		
		// Check to see if the available spot is NUll. Insert Rabbit
		if (Yard[randomX][randomY].animal == NULL) {


			// Initialize Rabbit object that hasnt moved 
			Yard[randomX][randomY].animal = new Rabbit(10, 3, initialDay, false, false, 50);
			Yard[randomX][randomY].SetInnerSquare(sf::Color::Blue);
			Yard[randomX][randomY].SetOuterSquare(sf::Color::Blue);
		}

		else {
			continue;
		}

		numberRabbits++;
	}

	// Create and insert five deers
	while (numberDeers < 5) {

		randomX = rand() % 40;
		randomY = rand() % 30;

		// Check to see if the available spot is NUll. Insert Rabbit
		if (Yard[randomX][randomY].animal == NULL) {

			// Initialize Rabbit object that hasnt moved 
			Yard[randomX][randomY].animal = new Deer(30, 6, initialDay, false, false, 30);
			Yard[randomX][randomY].SetInnerSquare(sf::Color::White);
			Yard[randomX][randomY].SetOuterSquare(sf::Color::White);
		}

		else {
			continue;
		}

		numberDeers++;
	}


	// Create and insert three wolfs
	while(numberWolfs < 3) {

		randomX = rand() % 40;
		randomY = rand() % 30;

		// Check to see if the available spot is NUll. Insert Rabbit
		if (Yard[randomX][randomY].animal == NULL) {


			// Initialize Rabbit object that hasnt moved 
			Yard[randomX][randomY].animal = new Wolf(150, 2, initialDay, false, false, 40, false);
			Yard[randomX][randomY].SetInnerSquare(sf::Color::Red);
			Yard[randomX][randomY].SetOuterSquare(sf::Color::Red);
		}

		else {
			continue;
		}

		numberWolfs++;
		
	}
	
	// Create and insert one eagle
	while (numberEagles < 1) {

		randomX = rand() % 40;
		randomY = rand() % 30;

	
		// Check to see if the available spot is NUll. Insert Rabbit
		if (Yard[randomX][randomY].animal == NULL) {


			// Initialize Rabbit object that hasnt moved 
			Yard[randomX][randomY].animal = new Eagle(100, 4, initialDay, false, false, 40, false);
			Yard[randomX][randomY].SetInnerSquare(sf::Color::Red);
			Yard[randomX][randomY].SetOuterSquare(sf::Color::Red);
		}

		else {
			continue;
		}

		numberEagles++;

	}

	// Create and insert one lion
	while (numberLions < 1) {

		randomX = rand() % 40;
		randomY = rand() % 30;

		
		// Check to see if the available spot is NUll. Insert Rabbit
		if (Yard[randomX][randomY].animal == NULL) {


			// Initialize Rabbit object that hasnt moved 
			Yard[randomX][randomY].animal = new Lion(300, 5, initialDay, false, false, 30, false);
			Yard[randomX][randomY].SetInnerSquare(sf::Color::Yellow);
			Yard[randomX][randomY].SetOuterSquare(sf::Color::Yellow);
		}

		else {
			continue;
		}

		numberLions++;

	}

}

void Land::update(int x, int y, int currentDay){
	
	int maxHorizontal = x;
	int maxVertical = y;

	// Perform all necessary operations to each grass object on the board

	for (int i = 0; i < maxHorizontal; i ++) {

		for (int j = 0; j < maxVertical; j++) {

			if (Yard[i][j].grass != NULL) {

				// Adds food level to grass each day 
				if (currentDay > 0) {
					Yard[i][j].grass->changeFoodLevel();
				}
			}

		}
	}

	// Iterate through the whole 2D array. Perform operations for Animals  
	for (int i = 0; i < x; i++) {

		for (int j = 0; j < y; j++) {

			// Can be either a rabbit or wolf// AND IS A RABBIT 
			if (Yard[i][j].animal != NULL) {


				if (currentDay > 0) {
						
					Yard[i][j].animal->increaseAge();
					 
					Yard[i][j].animal->changeFoodLevel();

					
					// Kill Creature then iterates to the next square 
					
					if (Yard[i][j].animal->checkToKillCreature(i, j, Yard, Yard[i][j].animal->getAge()) == true) {
						continue;
					}
					
					// Evade && Spawn are inside of move function 
					Yard[i][j].animal->move(i, j, maxHorizontal, maxVertical, Yard);

				}

							
			}

							
		}

	}

	// Reset each animal to be able to move next iteration. ?And has not perform any actions eg.(evaded, hunted)? 
	
	for (int i = 0; i < maxHorizontal; i++) {

		for (int j = 0; j < maxVertical; j++) {
			
			// If animal Exists. Reset moved and action to false;
			if (Yard[i][j].animal != NULL) {
				Yard[i][j].animal->resetMove();
				Yard[i][j].animal->resetAction();
				
			}

		}

	}
	

}

void Land::draw(sf::RenderWindow &w){
	for (int j = 0; j<Y; j++) {
		for (int i = 0; i<X; i++) {
			Yard[i][j].draw(w);
		}
	}
}


//Get Maxes
int Land::maxX(){
	return X;
}
int Land::maxY(){
	return Y;
}



//Get and Set inner color.
void Land::setInnerColor(int x, int y, sf::Color c){
	Yard[x][y].SetInnerSquare(c);
}
sf::Color Land::getInnerValue(int x, int y){
	return Yard[x][y].getInnerSquare();
}
//Get and set outer color.
void Land::setOuterColor(int x, int y, sf::Color c){
	Yard[x][y].SetOuterSquare(c);
}
sf::Color Land::getOuterValue(int x, int y){
	return Yard[x][y].getOuterSquare();
}

void Land::setAllColor(int x, int y, sf::Color c){
	Yard[x][y].SetInnerSquare(c);
	Yard[x][y].SetOuterSquare(c);
}
