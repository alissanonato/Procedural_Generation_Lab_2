#define _USE_MATH_DEFINES

#include "Noise.h"
#include "Helpers.h"
#include <SFML\Graphics.hpp>
#include <random>
#include <iostream>
#include <math.h>
//#include <string>
void noise(sf::Image &img, std::string &mode) {
//todo: set corresponding sin and red
// http://www.cplusplus.com/reference/random/uniform_real_distribution/

	//def smoother(noise) :
	//	output = []
	//	for i in range(len(noise) - 1) :
	//		output.append(0.5 * (noise[i] + noise[i + 1]))
	//		return output

	//		for i in range(8) :
	//			random.seed(i)
	//			noise = [random.uniform(-1, +1) for i in range(mapsize)]
	//			print_chart(i, smoother(noise))

	if (mode == "red") {
		std::uniform_real_distribution<double> distribution(0, 400);
		std::vector<double> noise;

		// 50 is num points to generate
		// 5 is scale value
		/*for (int i = 0; i < img.getSize().x/2; i++) {
		noise.emplace_back(0.1*distribution(generator) + 200);
		}*/

		for (int i = 0; i < img.getSize().x / 2; i++) {
			if (i == 0) {
				//noise.emplace_back(0.1*distribution(generator) + 200);
				noise.emplace_back(0.1*randomize(0.0, 400.0) + 200);
			}
			else {
				//noise.emplace_back(0.5 * (noise[i - 1] + (0.1*distribution(generator) + 200)));
				noise.emplace_back(0.5 * (noise[i - 1] + (0.1*randomize(0.0, 400.0) + 200)));
			}

		}

		double incrValX = img.getSize().x / (double)(noise.size() - 1);

		for (int i = 0; i < (noise.size() - 1); i++) {
			//drawLine(i* incrValX,0.5*(noise[i] + noise[i + 1]), (i + 1)*incrValX, 0.5*(noise[i + 1] + noise[i + 2]), img);
			drawLine(i* incrValX, noise[i], (i + 1)*incrValX, noise[i + 1], img);
		}

		// to complete the terrain
		//drawLine((noise.size() - 1) * incrValX, noise[noise.size() - 2], noise.size() * incrValX, noise[noise.size() - 1], img);
		//drawLine((noise.size() - 2) * incrValX, noise[noise.size() - 2], (noise.size() - 1) * incrValX, noise[noise.size() - 1], img);
	}

	if (mode == "sin") {
		//std::uniform_real_distribution<double> distribution(0.0, 2 * M_PI);
		double freq = 1.5;
		//double phase = distribution(generator);
		double phase = randomize(0.0, 2 * M_PI);
		std::cout << phase << std::endl;
		for (double i = 0; i < img.getSize().x - 1; i++) {	
			drawLine(i, sin(2 * M_PI * freq*i / img.getSize().x + phase) * 10 + 200, i+1, sin(2 * M_PI * freq*(i+1) / img.getSize().x + phase) * 10 + 200, img);
			//drawLine(i, sin(2 * M_PI * i * freq / img.getSize().x) * 199 + 200, i + 1, sin(2 * M_PI * (i + 1) * freq / img.getSize().x) * 199 + 200, img);
		}
	}
	


	// sine todo: change te 10 magic number in drawline
	/*def noise(freq) :
		phase = random.uniform(0, 2 * math.pi)
		return[math.sin(2 * math.pi * freq*x / mapsize + phase)
		for x in range(mapsize)]*/

	/*for i in range(3) :
		random.seed(i)
		print_chart(i, noise(1))*/

	//std::default_random_engine generator;
	//std::uniform_real_distribution<double> distribution(0.0, 2 * M_PI);
	//double freq = 1.5;
	//double phase = distribution(generator);
	//std::cout << phase << std::endl;
	//for (double i = 0; i < img.getSize().x - 1; i++) {	
	//	drawLine(i, sin(2 * M_PI * freq*i / img.getSize().x + phase) * 10 + 200, i+1, sin(2 * M_PI * freq*(i+1) / img.getSize().x + phase) * 10 + 200, img);
	//	//drawLine(i, sin(2 * M_PI * i * freq / img.getSize().x) * 199 + 200, i + 1, sin(2 * M_PI * (i + 1) * freq / img.getSize().x) * 199 + 200, img);
	//}

}
