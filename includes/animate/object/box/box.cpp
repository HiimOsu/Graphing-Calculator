#include "box.h"


Box::Box(float width, float height, sf::Color fill_color, sf::Color outline_color){
    _box.setSize(sf::Vector2f(width, height));
    _box.setFillColor(fill_color);
    _box.setOutlineColor(outline_color);
    _box.setOutlineThickness(-2.f);

}

void Box::Draw(sf::RenderWindow& window){
    window.draw(_box);

}

void Box::set_Position(sf::Vector2f pos){
    _box.setPosition(pos);
}
void Box::set_Fill_Color(sf::Color fill_color){
    _box.setFillColor(fill_color);
}

void Box::set_Outline_Color(sf::Color outline_color){
    _box.setOutlineColor(outline_color);
}
void Box::set_OutLineThikness(float t){
    _box.setOutlineThickness(t);
}

void Box::set_Size(sf::Vector2f dimension){
    _box.setSize(dimension);
}

sf::Vector2f Box::get_Size(){
    return _box.getSize();
}

sf::Vector2f Box::get_Position(){
    return _box.getPosition();
}

bool Box::is_Inside(sf::Vector2f winCor){
    if(is_hereInside_TheBox(winCor, get_Position(), get_Size()))
    {
        return true;
    }
    else return false;
}