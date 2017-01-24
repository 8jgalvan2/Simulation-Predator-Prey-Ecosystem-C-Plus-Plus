/*
	Programmer: Jonathan Galvan
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Windows.h"

#include <cstdlib>

#include "Land.h"
#include "SquareYard.h"

using namespace std;

// Global Variables
int day = 0;


int main() {

	// Hold Max X,Y
	int x;
	int y;
	
	sf::RenderWindow window(sf::VideoMode(1000, 700), "CS 474 project 3");
	window.setVerticalSyncEnabled(true);

	Land land = Land(40, 30, window, day);//50 cell by 50 cell grid.

	while (window.isOpen()){
		// Process events
		sf::Event event;
		while (window.pollEvent(event)){
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();// Clear screen

		// Test to see the Creature *grass objects
		x = land.maxX();
		y = land.maxY();

		cout << "Current Day is " << day << endl;

		land.update(x,y,day);
		
		land.draw(window);

		// Update the window
		window.display();
		
		// Update the days by one every iteration
		day++;
		
		Sleep(500);
	}
	
	return 0;
}

//Built in colors
//sf::Color::Black
//sf::Color::White
//sf::Color::Red
//sf::Color::Green
//sf::Color::Blue
//sf::Color::Yellow
//sf::Color::Magenta
//sf::Color::Cyan
//sf::Color::Transparent