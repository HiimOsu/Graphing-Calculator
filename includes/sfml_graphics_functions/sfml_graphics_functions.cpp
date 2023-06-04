#include "sfml_graphics_functions.h"

bool    is_hereInside_TheBox(sf::Vector2f here_position, sf::Vector2f box_position, sf::Vector2f box_size){

    sf::Vector2f box_x(box_position.x, box_position.x + box_size.x),
                box_y(box_position.y, box_position.y + box_size.y);
    if(here_position.x < box_x.x || here_position.x > box_x.y){
        return false;
    }
    if(here_position.y < box_y.x || here_position.y > box_y.y){
        return false;
    }

    return true;
}