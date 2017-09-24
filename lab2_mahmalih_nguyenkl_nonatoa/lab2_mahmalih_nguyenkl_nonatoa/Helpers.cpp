#include "Helpers.h"
#include <iostream>
#include <SFML\Graphics.hpp>

// http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
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

void fillTerrain(sf::Image &img) {
	for (int x = 0; x < img.getSize().x; x++) {
		bool isTerrain = false;
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

double randomize(double min, double max)
{
	double f = (double)rand() / (RAND_MAX + 1);
	return f * (max - min + 1) + min;
}

int clamp(int val, int lo, int hi) {
	if (lo > val) {
		return lo;
	}
	else if (hi < val) {
		return hi;
	}
	return val;
}
//int randomize(int min, int max)
//{
//	return std::rand() % (max - min) + min;
//}
