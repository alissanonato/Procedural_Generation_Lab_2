#include "Helpers.h"
#include "DiceRoll.h"
#include <SFML\Graphics.hpp>
void diceRoll(sf::Image &img, int numRolls, int numSides)
{
	int incrValX = img.getSize().x / numRolls;	// to complete the terrain
	int incrValY = img.getSize().y / numSides;
	int newX;
	int prevX = 0;
	int prevY = (int)randomize(0, numSides) * incrValY;
	int newY;

	for (int i = 1; i <= numRolls; i++)
	{
		newX = i * incrValX;

		//newY = (int)randomize(0, numSides) * incrValY;
		newY = randomize(0, numSides) * incrValY;

		drawLine(prevX, prevY, newX, newY, img);
		prevX = newX;
		prevY = newY;

	}
}
