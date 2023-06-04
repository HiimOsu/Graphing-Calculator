#ifndef TRANSLATE_CORDS_H
#define TRANSLATE_CORDS_H

#include <SFML\Graphics.hpp>
#include <cmath>
using namespace  std;

#include "../_info/graph_info.h"
#include "..\..\..\Matrix_Class\matrix\matrix.h"
#include "..\..\..\shuntingYard_RPN\rpn\rpn.h"


sf::Vector2f winCord_to_xyCords(sf::Vector2f winCord, Graph_info* info);
sf::Vector2f xyCord_to_winCords(sf::Vector2f xyCord, Graph_info* info);

// sf::Vector2f xyCord_to_polCords(sf::Vector2f xyCord);
sf::Vector2f winCord_to_polCords(sf::Vector2f winCord, Graph_info* info);
sf::Vector2f polCord_to_winCords(sf::Vector2f polCord, Graph_info* info);

#endif