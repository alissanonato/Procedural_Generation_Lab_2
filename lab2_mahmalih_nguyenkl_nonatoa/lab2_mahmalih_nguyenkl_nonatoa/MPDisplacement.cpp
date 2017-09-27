#include "MPDisplacement.h"
#include "Helpers.h"
#include <vector>
#include <SFML\Graphics.hpp>

#include <iostream>

// http://www.somethinghitme.com/2013/11/11/simple-2d-terrain-with-midpoint-displacement/

void mpDisplacement(double roughness, sf::Image &img, bool isBound) {
	//
	// isBound is set by the -C flag from command line
	//

	double width = img.getSize().x;
	double height = img.getSize().y;
	double displace = height;
	
	// Gives us a power of 2 based on our width
	double power = pow(2, log(width) / log(2)) - 1;
	std::vector<double> points(power + 1);

	// Set the initial left point
	points[0] = height / 2 + (randomize(0, displace) * 2) - displace;
	// clamp if needed
	if (isBound) {
		points[0] = clamp(points[0], 0, height - 1);
	}
	// set the initial right point
	points[power] = height / 2 + (randomize(0, displace) * 2) - displace;
	// clamp if needed
	if (isBound) {
		points[power] = clamp(points[power], 0, height - 1);
	}
	// reduce the random range
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
			// clamp if needed
			if (isBound) {
				points[j] = clamp(points[j], 0, height - 1);
			}
		}
		// reduce the random range
		displace *= roughness;
	}

	int incrValX = img.getSize().x / (points.size() - 1);

	// Since the points generated are clamped here, no need to scale the map to show all
	if (isBound) {
		for (int i = 0; i < (points.size() - 1); i++) {
			drawLine(i*incrValX, points[i], (i + 1)*incrValX, points[i + 1], img);
		}
	}
	// Points generated here were not clamped so some scaling is done to show them in the map
	else {
		// Find the largest and smallest points to determine the range we need to show
		int smallest = *std::min_element(points.begin(), points.end());
		int biggest = *std::max_element(points.begin(), points.end());
		double range = biggest - smallest;

		for (int i = 0; i < points.size() - 1; i++) {
			// clamped the scaled values to account for some cases of numeric inaccuracy after divisions
			// i.e. negative values and values larger than the height
			int scaledPoint1 = clamp(((points[i] - smallest) / range) * height, 0, height - 1);
			int scaledPoint2 = clamp(((points[i + 1] - smallest) / range) * height, 0, height - 1);

			drawLine(i*incrValX, scaledPoint1, (i + 1)*incrValX, scaledPoint2, img);
		}
	}
}