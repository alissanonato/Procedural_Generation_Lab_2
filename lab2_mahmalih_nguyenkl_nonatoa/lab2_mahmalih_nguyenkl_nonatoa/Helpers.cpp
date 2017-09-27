#include "Helpers.h"
#include <iostream>
#include <SFML\Graphics.hpp>

// http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
// This version of drawLine uses bresenham's algorithm but accounts for all octants
void drawLine(int x, int y, int x2, int y2, sf::Image &img)
{
	int w = x2 - x;
	int h = y2 - y;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w<0) dx1 = -1; else if (w>0) dx1 = 1;
	if (h<0) dy1 = -1; else if (h>0) dy1 = 1;
	if (w<0) dx2 = -1; else if (w>0) dx2 = 1;
	int longest = abs(w);
	int shortest = abs(h);
	if (!(longest>shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h<0) dy2 = -1; else if (h>0) dy2 = 1;
		dx2 = 0;
	}
	int numerator = longest >> 1;
	for (int i = 0; i <= longest; i++) {

		// ensures x never goes past the edge	
		if (x >= img.getSize().x) {
			img.setPixel(img.getSize().x - 1, y, sf::Color::Green);
		}
		else {
			img.setPixel(x, y, sf::Color::Green);
		}
		
		numerator += shortest;
		if (!(numerator<longest)) {
			numerator -= longest;
			x += dx1;
			y += dy1;
		}
		else {
			x += dx2;
			y += dy2;
		}
	}
}

// Make all pixels below a green one also green
void fillTerrain(sf::Image &img) {
	bool isTerrain;
	for (int x = 0; x < img.getSize().x; x++) {
		isTerrain = false;
		for (int y = 0; y < img.getSize().y; y++) {
			if (isTerrain) {
				img.setPixel(x, y, sf::Color::Green);
			}
			if (img.getPixel(x, y) == sf::Color::Green) {
				isTerrain = true;
			}
		}
	}
}

// generate a random double between min and max inclusive
double randomize(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return f * (max - min) + min;
}

// Standard clamp
// return a value within the bounds [lo..hi]
// forces it to be lo if lower than lo, hi if higher than hi
// otherwise give back the same value since it is in bounds
int clamp(int val, int lo, int hi) {
	if (lo > val) {
		return lo;
	}
	else if (hi < val) {
		return hi;
	}
	return val;
}

// usage statement conventions: https://en.wikipedia.org/wiki/Usage_message
void usageMsg() {
	std::cout << "Usage: generate.exe -g g_arg [-s s_arg] -f f_arg\n\t[[-d d_arg] -r r_arg\t|\n\t" << 
		"-n n_arg [-C] \t\t|\n\t-m m_arg \t\t|\n\t[-a a_arg] -e e_arg -p p_arg]\n" << std::endl;
}

// explains how to use the program
// called when -h is used
void helpMsg() {
	std::cout << "\n--------------------\n\tHELP\n--------------------\n" << std::endl;

	usageMsg();

	std::cout << "\nGeneral Options\n---------------\n" << std::endl;

	std::cout << "-g: selects a generation algorithm option between [1..4]\n" <<
		"-s: use a fixed seed (default seed is system time)\n" <<
		"-f: filename ending in .png or .bmp\n" << std::endl;

	std::cout << "\n[-g 1] Dice Rolling Algorithm\n-----------------------------\n" << std::endl;

	std::cout << "-d: number of dice sides (default number is 6)\n" <<
		"-r: number of rolls\n" << std::endl;

	std::cout << "\n[-g 2] Midpoint Displacement Algorithm\n--------------------------------------\n" << std::endl;

	std::cout << "-n: roughness value between [0..1]\n" <<
		"-C: when set, rescales generated values to fit bounds (default caps height)\n" << std::endl;

	std::cout << "\n[-g 3] Noise Algorithm\n----------------------\n" << std::endl;

	std::cout << "-m: mode (red or sin)\n" << std::endl;

	std::cout << "\n[-g 4] Cellular Automata Algorithm\n----------------------------------\n" << std::endl;

	std::cout << "-a: ruleset (1 or 2) (default ruleset is 1)\n" <<
		"-e: number of generations to run the algorithm\n" <<
		"-p: percentage chance to be a terrain" << std::endl;
}