//
//  Land.h
//  Programmer: Jonathan Galva
//
//  Copyright © 2016 UIC. All rights reserved.
//

#ifndef Land_H
#define Land_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SquareYard.h"


class Land{

public:
	Land(); // Initial constructor
	Land(int, int, sf::RenderWindow &w, int); // Constructor 
	~Land(); // Destructor

	void update(int,int,int);//Update code /could be put in here.
	
	void draw(sf::RenderWindow &w);


	//Returns the max X and Y nodes.
	int maxX();
	int maxY();

	
	//Get and Set inner color.
	void setInnerColor(int, int, sf::Color);
	sf::Color getInnerValue(int, int);

	//Get and set outer color.
	void setOuterColor(int, int, sf::Color);
	sf::Color getOuterValue(int, int);

	void setAllColor(int, int, sf::Color);

private:
	
	SquareYard ** Yard;

	//Holds the max X and Y values.
	int X;
	int Y;

};



#endif /* Land_H */