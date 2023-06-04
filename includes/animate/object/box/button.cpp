#include <iostream>
using namespace std;

#include "button.h"

Button::Button(string text, float width, float height, sf::Color fill_color, sf::Color outline_color): Box::Box(width,height,fill_color,outline_color)
{   
    _box_text.setCharacterSize(26);
    add_string(text);
    _box_text.setColor(sf::Color::Green);
    // _box_text.setColor(sf::Color::Blue);
}


void Button::Draw(sf::RenderWindow& window){
    Box::Draw(window);


    float LEFT_MARGIN = 5;
    float VERTICAL_LINESPACING = 5;
    float height = 1;
    for(Vector<string>::Iterator it = _item.begin();
     it != _item.end(); it++){
        
        if(it->size() == 0){
            _box_text.setString("Blank");
        }else{
            _box_text.setString(*it);
        }
        _box_text.setPosition(_pos_x + LEFT_MARGIN, _pos_y + height);
        window.draw(_box_text);

        height += _box_text.getLocalBounds().height + VERTICAL_LINESPACING;
    
    }
    window.draw(_box_text);
}

void Button::set_Font(sf::Font* font){
    _box_text.setFont(*font);
}

void Button::set_String(string text, int index){
    _item[index] = text;
}

void Button::set_CharacterSize(int newSize){
    _box_text.setCharacterSize(newSize);
    
    string text =_box_text.getString();
}

void Button::set_Position(sf::Vector2f position){
    Box::set_Position(position);
    _pos_x = position.x;
    _pos_y = position.y;

}

void Button::set_TextColor(sf::Color color){
    _box_text.setColor(color);
}
  

void Button::add_string(string str){
    _item.push_back(str);
}

void Button::remove_lastString(){
    if(_item.size() != 0)
        _item.pop_back();
}