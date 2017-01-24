//
//  Yard.cpp
//	Programmer: Jonathan Galvan
//  Copyright © 2016 UIC. All rights reserved.
//

#include "SquareYard.h"
#include <SFML/Graphics.hpp>

SquareYard::SquareYard(){

}
SquareYard::~SquareYard(){

}

//Sets the Posisition of the middle and regular boxes.
void SquareYard::set(float x, float y, float sizeX, float sizeY){

	square.setSize(sf::Vector2f(sizeX, sizeY));
	square.setPosition(sf::Vector2f(x, y));

	float sizeXforth = sizeX / 4;
	float sizeYforth = sizeY / 4;

	sizeX = sizeX / 2;
	sizeY = sizeY / 2;

	innerSquare.setPosition(sf::Vector2f((x + sizeXforth), (y + sizeYforth)));
	innerSquare.setSize(sf::Vector2f(sizeX, sizeY));

	// Paints tile Greens
	square.setFillColor(sf::Color::Green);
	square.setOutlineColor(sf::Color::Black);
	square.setOutlineThickness(1.0f);
	innerSquare.setFillColor(sf::Color::Green);
}

//Simply draw the squares in order to the output window.
void SquareYard::draw(sf::RenderWindow &w){
	w.draw(square);
	w.draw(innerSquare);
}

//Outer colors
void SquareYard::SetOuterSquare(sf::Color c){
	square.setFillColor(c);
}
sf::Color SquareYard::getOuterSquare(){
	return square.getFillColor();
}

//Inner colors
void SquareYard::SetInnerSquare(sf::Color c){
	innerSquare.setFillColor(c);
}
sf::Color SquareYard::getInnerSquare(){
	return innerSquare.getFillColor();
}
