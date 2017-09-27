#include "CellularAutomata.h"
#include "Helpers.h"
#include <SFML\Graphics.hpp>
#include <iostream>

// https://gamedevelopment.tutsplus.com/tutorials/generate-random-cave-levels-using-cellular-automata--gamedev-9664
void initialiseMap(sf::Image &img, double percChance) {
	const int width = img.getSize().x;
	const int height = img.getSize().y;

	double percChanceToStartAsTerrain = percChance;

	std::cout << randomize(0, 100) << std::endl;
	for (int x = 0; x < width; x++) {		
		for (int y = 0; y < height; y++) {
			if (randomize(0, 100) < percChanceToStartAsTerrain) {
				//map[x][y] = true;

				img.setPixel(x, y, sf::Color::Green);
			}
			else {
				img.setPixel(x, y, sf::Color::Blue);
			}
		}
	}
}

//Returns the number of cells in a ring around (x,y) that are green
int countAliveNeighbours(sf::Image &img, int x, int y) {
	int count = 0;
	for (int i = -1; i<2; i++) {
		for (int j = -1; j<2; j++) {
			int neighbour_x = x + i;
			int neighbour_y = y + j;
			//If we're looking at the middle point
			if (i == 0 && j == 0) {
				//Do nothing, we don't want to add ourselves in!
			}
			//In case the index we're looking at is off the edge of the map
			else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= img.getSize().x || neighbour_y >= img.getSize().y) {
				count = count + 1;
			}
			//Otherwise, a normal check of the neighbour
			else if (img.getPixel(neighbour_x, neighbour_y) == sf::Color::Green) {
				count = count + 1;
			}
		}
	}
	return count;
}

void doSimulationStep(sf::Image &oldMap, sf::Image &newMap, int ruleSet) {
	// Rule Set 1: 
	//		1. if a green pixel has more than 5 green neighbours, turn it blue
	//		2. if a blue pixel has more than 1 green neighbour, turn it green
	// Rule Set 1: 
	//		1. if a green pixel has less than 4 green neighbours, turn it blue
	//		2. if a blue pixel has more than 4 green neighbour, turn it green

	//Loop over each row and column of the map
	for (int x = 0; x<oldMap.getSize().x; x++) {
		for (int y = 0; y<oldMap.getSize().y; y++) {
			int nbs = countAliveNeighbours(oldMap, x, y);
			//The new value is based on our simulation rules

			//use different conditions based on ruleset
			switch (ruleSet) {
			case 1:
				// green -> blue if green_neighbours < 5
				if (oldMap.getPixel(x, y) == sf::Color::Green) {
					if (nbs > 5) {
						newMap.setPixel(x, y, sf::Color::Blue);
					}
					else {
						newMap.setPixel(x, y, sf::Color::Green);
					}
				} 
				// blue -> green if green_neighbours > 1
				else {
					if (nbs > 1) {
						newMap.setPixel(x, y, sf::Color::Green);
					}
					else {
						newMap.setPixel(x, y, sf::Color::Blue);
					}
				}
				break;
			case 2:
				// green -> blue if green_neighbours < 4
				if (oldMap.getPixel(x, y) == sf::Color::Green) {
					if (nbs < 4) {
						newMap.setPixel(x, y, sf::Color::Blue);
					}
					else {
						newMap.setPixel(x, y, sf::Color::Green);
					}
				}
				// blue -> green if green_neighbours > 4
				else {
					if (nbs > 4) {
						newMap.setPixel(x, y, sf::Color::Green);
					}
					else {
						newMap.setPixel(x, y, sf::Color::Blue);
					}
				}
				break;
			}
		}
	}
}
