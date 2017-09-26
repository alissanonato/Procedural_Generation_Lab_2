#pragma once
namespace sf { class Image; }
void drawLine(int x, int y, int x2, int y2, sf::Image &img);
void fillTerrain(sf::Image &img);
// int randomize(int min, int max);
double randomize(double min, double max);
int clamp(int val, int lo, int hi);
void usageMsg();
void helpMsg();