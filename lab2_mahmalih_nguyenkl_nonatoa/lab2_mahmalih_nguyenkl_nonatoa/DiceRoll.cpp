#include "Helpers.h"
#include "DiceRoll.h"
#include <SFML\Graphics.hpp>
void diceRoll(sf::Image &img, int numRolls, int numSides)
{
	// the x distance between each point generated depends on the number of rolls
	int incrValX = img.getSize().x / numRolls;
	// the size of the y step each point of the die roll is worth
	int incrValY = img.getSize().y / numSides;

	// generate a starting point
	int prevX = 0;
	int prevY = (int)randomize(0, numSides) * incrValY;

	int newX;
	int newY;

	for (int i = 1; i <= numRolls; i++)
	{
		// generate a new point
		newX = i * incrValX;
		newY = (int)randomize(0, numSides) * incrValY;

		// draw from the previous point to the new point
		drawLine(prevX, prevY, newX, newY, img);
		
		// the new point is now the previous point
		prevX = newX;
		prevY = newY;
	}
}
