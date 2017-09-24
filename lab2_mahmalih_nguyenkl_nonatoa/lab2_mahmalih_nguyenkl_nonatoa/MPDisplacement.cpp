#include "MPDisplacement.h"
#include "Helpers.h"
#include <vector>
#include <SFML\Graphics.hpp>

#include <iostream>

// http://www.somethinghitme.com/2013/11/11/simple-2d-terrain-with-midpoint-displacement/
/*
* width and height are the overall width and height we have to work with, displace is
* the maximum deviation value. This stops the terrain from going out of bounds if we choose
*/

void mpDisplacement(double roughness, sf::Image &img, bool isBound) {
	double width = img.getSize().x;
	double height = img.getSize().y;
	double displace = height;
	
	// Gives us a power of 2 based on our width
	double power = pow(2, log(width) / log(2)) - 1;
	std::vector<double> points(power + 1);

	// Set the initial left point
	points[0] = height / 2 + (randomize(0, displace) * 2) - displace;
	if (isBound) {
		points[0] = clamp(points[0], 0, height - 1);
	}
	// set the initial right point
	points[power] = height / 2 + (randomize(0, displace) * 2) - displace;
	if (isBound) {
		points[power] = clamp(points[power], 0, height - 1);
	}
	displace *= roughness;

	int leftIndex;
	int rightIndex;

	// Increase the number of segments
	for (double i = 1; i < power; i *= 2) {
		
		// Iterate through each segment calculating the center point
		for (double j = (power / i) / 2; j < power; j += power / i) {
			leftIndex = j - (power / i) / 2;
			rightIndex = j + (power / i) / 2;
			points[j] = (points[leftIndex] + points[rightIndex]) / 2;
			points[j] += (randomize(0, displace) * 2) - displace;
			// ensures terrain stays in bounds
			if (isBound) {
				points[j] = clamp(points[j], 0, height - 1);
			}
		}
		// reduce our random range
		displace *= roughness;
	}

	int incrValX = img.getSize().x / (points.size() - 1);
	std::cout << img.getSize().x << " x size" << std::endl;
	std::cout << points.size() << " points size" << std::endl;
	std::cout << incrValX << " increment" << std::endl;
	if (isBound) {
			
		for (int i = 0; i < (points.size() - 1); i++) {
			drawLine(i*incrValX, points[i], (i + 1)*incrValX, points[i + 1], img);
			//std::cout << i << " Found" << std::endl;
		}
	}
	else {
		int smallest = *std::min_element(points.begin(), points.end());
		int biggest = *std::max_element(points.begin(), points.end());
		double range = biggest - smallest;

		for (int i = 0; i < points.size() - 1; i++) {
			int scaledPoint1 = clamp(((points[i] - smallest) / range) * height, 0, height - 1);
			int scaledPoint2 = clamp(((points[i + 1] - smallest) / range) * height, 0, height - 1);

			drawLine(i*incrValX, scaledPoint1, (i + 1)*incrValX, scaledPoint2, img);
		}
		std::cout << smallest << " smallest" << std::endl;
		std::cout << biggest << " biggest" << std::endl;
		std::cout << range << " range" << std::endl;
	}
}
