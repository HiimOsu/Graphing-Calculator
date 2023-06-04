#ifndef SFML_GRAPHICS_FUNCTIONS
#define SFML_GRAPHICS_FUNCTIONS

#include <SFML\Graphics.hpp>




//Detect is the here position lay inside a rectangular box object
//Pre:  Suppose origin of the box is the top left corner
//      And suppose coordinate  system is same as sfml system:              |----->x
//                                                                          |
//                                                                         \|/
//                                                                          y 
//Post: Return true if it is inside else return false
bool    is_hereInside_TheBox(sf::Vector2f here_position, sf::Vector2f box_position, sf::Vector2f box_size);

#endif