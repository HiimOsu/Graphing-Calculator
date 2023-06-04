#include "seesaw.h"


Seesaw::Seesaw(float width, float height): Box(width, height)
{
    float MARGIN = 5;
    _button.set_Size(sf::Vector2f(width * 1/3 - MARGIN, height - MARGIN));
}

void Seesaw::Draw(sf::RenderWindow& window){
    
}

void Seesaw::setSize(float widht, float height){
    
}
void Seesaw::setPosition(float x, float y){
    
}

void Seesaw::set_Font(sf::Font* font_ptr){
    
}

void Seesaw::setRight_string(string str){
    
}
void Seesaw::setLeft_string(string str){
    
}

bool Seesaw::is_OnRight(sf::Vector2f winCord){
    
}
bool Seesaw::is_OnLeft(sf::Vector2f winCord){
    
}

//if right is on, turn it off, and then turn left on
//else toggle left
//return int tell which button is on, left = 1, right = 2, none = 0
int Seesaw::toggle_left(){
    if(_right_toggle){
        _right_toggle = false;
        _left_toggle = true;
        return 1;
    }else if(_left_toggle){
        _left_toggle = false;
        return 0;
    }else {
        _left_toggle = true;
        return 1;
    }
}

//if left is on, turn it off, and then turn right on
//else toggle right;
//return int tell which button is on, left = 1, right = 2, none = 0
int Seesaw::toggle_right(){
    if(_left_toggle){
        _left_toggle = false;
        _right_toggle = true;
        return 2;
    }else if(_right_toggle){
        _right_toggle = false;
        return 0;
    }else {
        _right_toggle = true;
        return 2;
    }
}

//Turn off both button
int Seesaw::balanceBoth(){
    _left_toggle = false;
    _right_toggle = false;
    return 0;
}