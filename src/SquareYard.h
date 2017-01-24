//
//  Yard.h
//	Programmer: Jonathan alvan
//  Copyright © 2016 UIC. All rights reserved.
//

#ifndef Yard_H
#define Yard_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Creature; // Foward Declaration 


class SquareYard {

public:
	SquareYard();
	~SquareYard();
	
	// Two Creatures exists in the map cocunrrently. Animal and a Grass
	Creature* animal;
	Creature* grass;

	//Initial setup of the object
	void set(float xpos, float ypos, float xsize, float ysize);


	//Set and get outer colors
	void SetOuterSquare(sf::Color);
	sf::Color getOuterSquare();

	//Set and get inner
	void SetInnerSquare(sf::Color);
	sf::Color getInnerSquare();

	//Draw simply draws both the square and inner square.
	void draw(sf::RenderWindow &);


	//Square is for the entire shape and also has the border.
	sf::RectangleShape square;
	//inner Square is the color inside of the main square.
	sf::RectangleShape innerSquare;


};

#endif /* Yard_H */