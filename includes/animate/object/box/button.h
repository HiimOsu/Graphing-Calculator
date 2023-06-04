#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "box.h"
#include "../../../Vector_class/vector/vector_class.h"
class Button: public Box{
public:
    Button(string text = "", float width = SB_BOX_WIDTH - 10, float height = SB_BOX_HEIGHT, sf::Color fill_color = SB_BOX_FILL_COLOR, sf::Color outline_color = SB_BOX_OUTLINE_COLOR);
    
    void Draw(sf::RenderWindow& window);
    void set_Position(sf::Vector2f position);
    void set_CharacterSize(int newSize);
    void set_String(string str, int index = 0);
    void set_Font(sf::Font* font);
    void set_TextColor(sf::Color color);
    
    void add_string(string str);
    void remove_lastString();
private:
    sf::Text _box_text;
    Vector<string> _item;
    float _pos_x = 0, _pos_y = 0;
};

#endif