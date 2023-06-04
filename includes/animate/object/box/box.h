#ifndef ANIMATE_BOX_H
#define ANIMATE_BOX_H

#include <string.h>
#include <SFML/Graphics.hpp>
using namespace std;

#include "../../constants.h"
#include "../../../sfml_graphics_functions/sfml_graphics_functions.h"

class Box{
public:
    Box(float width = SB_BOX_WIDTH - 10, float height = SB_BOX_HEIGHT, sf::Color fill_color = SB_BOX_FILL_COLOR, sf::Color outline_color = SB_BOX_OUTLINE_COLOR);


    void Draw(sf::RenderWindow& window);
    
    void set_Position(sf::Vector2f position);
    void set_Size(sf::Vector2f dimension);
    void set_Fill_Color(sf::Color fill_color);
    void set_Outline_Color(sf::Color outline_color);
    void set_OutLineThikness(float t);
    
    sf::Vector2f get_Size();
    sf::Vector2f get_Position();
    bool is_Inside(sf::Vector2f winCor);
private:
    sf::RectangleShape _box;
};

#endif