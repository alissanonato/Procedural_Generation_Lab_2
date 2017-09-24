#define _USE_MATH_DEFINES

#include "Noise.h"
#include "Helpers.h"
#include <SFML\Graphics.hpp>
#include <random>
#include <iostream>
#include <math.h>
void noise(sf::Image &img) {
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


	/*std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);
	std::vector<double> noise;
	
	for (int i = 0; i < img.getSize().x; i++) {
		noise.emplace_back(distribution(generator));
		std::cout << i << " " << noise[i] << std::endl;
		
	}
	std::cout << noise.size() << std::endl;

	int incrValX = img.getSize().x / (noise.size() - 1);

	for (int i = 0; i < noise.size() - 2; i++) {
		drawLine(i*incrValX, 0.5*(noise[i] + noise[i + 1]), (i + 1)*incrValX, 0.5*(noise[i + 1] + noise[i + 2]), img);
	}*/


	// sine
	/*def noise(freq) :
		phase = random.uniform(0, 2 * math.pi)
		return[math.sin(2 * math.pi * freq*x / mapsize + phase)
		for x in range(mapsize)]*/

	/*for i in range(3) :
		random.seed(i)
		print_chart(i, noise(1))*/

	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 2.0 * M_PI);
	double freq = 0.5;
	double phase = 0;
	std::cout << phase << std::endl;
	for (double i = 0; i < img.getSize().x - 1; i++) {
		phase = distribution(generator);
		drawLine(i, sin(2 * M_PI * freq*i / img.getSize().x + phase) * 99 + 200, i+1, sin(2 * M_PI * freq*(i+1) / img.getSize().x + phase) * 99 + 200, img);
		//drawLine(i, sin(2 * M_PI * i * freq / img.getSize().x) * 199 + 200, i + 1, sin(2 * M_PI * (i + 1) * freq / img.getSize().x) * 199 + 200, img);
	}

}
