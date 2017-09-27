// lab2_mahmalih_nguyenkl_nonatoa.cpp : Defines the entry point for the console application.
//
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>

#include "getopt.h"
#include "Helpers.h"
#include "DiceRoll.h"
#include "MPDisplacement.h"
#include "Noise.h"
#include "CellularAutomata.h"

// getopt code: https://github.com/skandhurkat/Getopt-for-Visual-Studio
// getting getopt working: http://www.cplusplus.com/forum/general/141573/

enum eGenerator {
	DICE_ROLL,
	MP_DISPLACEMENT,
	NOISE,
	CELL_AUTO,
	COUNT,
	INVALID = -1
};

int main(int argc, char* argv[])
{
	std::srand(time(NULL));
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image img;
	img.create(600, 400, sf::Color::Blue);
	
	int currGenState = eGenerator::INVALID;
	
	// general options
	bool hFound = false;
	bool gFound = false;
	bool fFound = false;

	// dice roll
	bool dFound = false;
	bool rFound = false;
	
	// mp displacement
	bool nFound = false;
	bool cFound = false;

	// noise
	bool mFound = false;
	bool invalidMode = false;

	// cell auto
	bool aFound = false;
	bool eFound = false;
	bool pFound = false;
	
	std::string filename = ""; // for gen options -f

	int numSides = 6;	// for dice rolling -d
	int numRolls = 0;	// for dice rolling -r

	float roughness = 0;	// for mp displacement -n

	int ruleSet = 1;	//for cell auto -a
	int numGens = 0;	// for cell auto -e
	double percChance = 0.0;	// cell auto -p; todo: figure out float conversion

	std::string mode = "";	// for noise -m
	std::vector<std::string> validModes{"red", "sin"};	

	// "letter:" means arg required
	// "letter" means no arg required
	int c;
	while ((c = getopt(argc, argv, "hg:s:f:d:r:n:Cm:a:e:p:")) != -1)
	{
		switch (c)
		{
		case 'h':
			hFound = true;
			break;
		case 'g':
			gFound = true;
			if (optarg) {
				switch (std::atoi(optarg)) {
				case 1:
					currGenState = eGenerator::DICE_ROLL;				
					break;
				case 2:
					currGenState = eGenerator::MP_DISPLACEMENT;
					break;
				case 3:
					currGenState = eGenerator::NOISE;
					break;
				case 4:
					currGenState = eGenerator::CELL_AUTO;
					break;
				default:
					std::cout << "Please use a number between [1..4]" << std::endl;
					break;
				}
			}
			break;
		case 's':
			if (optarg) {
				std::srand(std::atoi(optarg));
			}
			break;
		case 'f':
			fFound = true;
			if (optarg) {
				filename = optarg;
			}
			break;
		case 'd':
			dFound = true;
			if (optarg) {
				numSides = std::atoi(optarg);
			}
			else {
				usageMsg();
			}			
			break;
		case 'r':
			rFound = true;
			if (optarg) {
				numRolls = std::atoi(optarg);
			}
			else {
				usageMsg();
			}
			break;
		case 'n':
			nFound = true;
			if (optarg) {
				roughness = strtof(optarg, NULL);
			}
			break;
		case 'C':
			cFound = true;
			break;
		case 'm':
			mFound = true;
			if (optarg) {
				// error checking
				if (std::find(validModes.begin(), validModes.end(), optarg) != validModes.end())
				{
					mode = optarg;
				}					
				else 
				{
					invalidMode = true;
					std::cout << "Error: invalid mode" << std::endl;
					usageMsg();
				}
			}
			break;
		case 'a':
			aFound = true;
			if (optarg) {
				ruleSet = std::atoi(optarg);
			}
			break;
		case 'e':
			eFound = true;
			if (optarg) {
				numGens = std::atoi(optarg);
			}
			break;
		case 'p':
			pFound = true;
			if (optarg) {
				percChance = std::atof(optarg);
			}
			break;
		}
	}

	if (fFound)
	{
		switch (currGenState) {
		case eGenerator::DICE_ROLL:
			if (rFound)
			{
				if (nFound || cFound || mFound || aFound || eFound || pFound || hFound)
				{
					std::cout << "Error: extra options" << std::endl;
					usageMsg();
				}
				else
				{
					diceRoll(img, numRolls, numSides);
				}
			}
			else
			{
				std::cout << "Error: Missing argument or -r not found" << std::endl;
				usageMsg();
			}
			break;
		case eGenerator::MP_DISPLACEMENT:
			if (nFound)
			{
				if (rFound || dFound || mFound || aFound || eFound || pFound || hFound)
				{
					std::cout << "Error: extra options" << std::endl;
					usageMsg();
				}
				else
				{
					mpDisplacement(roughness, img, !cFound);
				}
			}
			else
			{
				std::cout << "Error: Missing argument or -n not found" << std::endl;
				usageMsg();
			}
			break;
		case eGenerator::NOISE:
			if (mFound)
			{
				if (dFound || rFound || nFound || cFound || aFound || eFound || pFound || hFound)
				{
					std::cout << "Error: extra options" << std::endl;
					usageMsg();
				}
				else
				{
					if (!invalidMode) {
						noise(img, mode);
					}					
				}
			}
			else
			{
				std::cout << "Error: Missing argument or -m not found" << std::endl;
				usageMsg();
			}
			break;
		case eGenerator::CELL_AUTO:
			if (eFound)
			{
				if (pFound)
				{
					if (dFound || rFound || nFound || cFound || mFound || hFound)
					{
						std::cout << "Error: extra options" << std::endl;
						usageMsg();
					}
					else
					{
						sf::Image tempImg;
						tempImg.create(600, 400, sf::Color::Blue);
						initialiseMap(tempImg, percChance);

						for (int i = 0; i < numGens; i++) {
							doSimulationStep(tempImg, img, ruleSet);
							tempImg = img;
						}
					}
				}
				else
				{
					std::cout << "Error: Missing argument or -p not found" << std::endl;
					usageMsg();
				}
			}
			else
			{
				std::cout << "Error: Missing argument or -e not found" << std::endl;
				usageMsg();
			}
			break;
		default:
			usageMsg();
			break;
		}

		if (currGenState != eGenerator::CELL_AUTO) {
			fillTerrain(img);
		}
		
		if (!invalidMode) {
			texture.loadFromImage(img);

			sprite.setTexture(texture, true);

			// Save the image to a file
			if (!img.saveToFile(filename))
				return -1;
		}	
	}
	else 
	{
		if (!hFound) {
			std::cout << "Error: Missing argument or -f not found" << std::endl;
			usageMsg();
		}
		else if (argc == 2) {
			helpMsg();
		}		
	}
}