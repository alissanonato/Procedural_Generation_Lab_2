#define _USE_MATH_DEFINES

#include "Noise.h"
#include "Helpers.h"
#include <SFML\Graphics.hpp>
#include <random>
#include <iostream>
#include <math.h>
//#include <string>
void noise(sf::Image &img, std::string &mode) {
// http://www.cplusplus.com/reference/random/uniform_real_distribution/

	if (mode == "red") {
		std::vector<double> noise;

		// put in the first point to be able to average with the next generated
		// scale these values back to make it look "nice"
		float scaleFactor = 0.5;
		noise.emplace_back(scaleFactor * randomize(-200, 199) + 200);

		// generate points in a range between [-200..200)
		// then add 200 to get a distribution of amplitudes around the middle of the map
		for (int i = 1; i < img.getSize().x; i++) {
			noise.emplace_back(0.5 * (noise[i -1] + (scaleFactor * randomize(-200, 199) + 200)));
		}

		double incrValX = img.getSize().x / (double)(noise.size() - 1);

		for (int i = 0; i < (noise.size() - 1); i++) {
			drawLine(i* incrValX, noise[i], (i + 1)*incrValX, noise[i + 1], img);
		}
	}
	
	if (mode == "sin") {
		// scale up the generated sin values relative to the map height
		float sinScaleUp = img.getSize().y / 5;
		double freq = randomize(1.0, 5.0); // [1..5] periods of sin
		freq = randomize(1.0, 5.0);		// dumb fix for the previous randomize call not being random
		double phase = randomize(0.0, 2 * M_PI); //randomize what "frame" of the sin curve to show
		for (double i = 0; i < img.getSize().x - 1; i++) {
			//generate points along the sin curve and center them as amplitudes
			//around the middle of the map
			drawLine(i, sin(2 * M_PI * freq * i / img.getSize().x + phase) * sinScaleUp  + 200, i+1, sin(2 * M_PI * freq*(i+1) / img.getSize().x + phase) * sinScaleUp + 200, img);
		}
	}
}
