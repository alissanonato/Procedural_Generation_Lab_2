#pragma once
namespace sf { class Image; }
void initialiseMap(sf::Image &img, double percChance);
int countAliveNeighbours(sf::Image &img, int x, int y);
void doSimulationStep(sf::Image &oldMap, sf::Image &newMap, int ruleSet);