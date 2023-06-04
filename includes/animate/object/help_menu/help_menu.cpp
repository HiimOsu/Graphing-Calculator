#include "help_menu.h"


Help_menu::Help_menu(float width, float height): _box_window(width, height, sf::Color::Black)
{
    _text.setCharacterSize(24);
    _text.setColor(sf::Color::Green);
}

Help_menu::Help_menu(const Help_menu& copy_me){
    _box_window = copy_me._box_window;
    _font_ptr = copy_me._font_ptr;
    _text = copy_me._text;
    _line = copy_me._line;
    _top  = copy_me._top;
    _left = copy_me._left;
    _text.setFont(*_font_ptr);
    
}


void Help_menu::Draw(sf::RenderWindow& window){
    float LEFT_MARGIN = 5;
    float VERTICAL_LINESPACING = 5;
    float height = 1;
    for(Vector<string>::Iterator it = _line.begin();
     it != _line.end(); it++){
        
        if(it->size() == 0){
            _text.setString("Blank");
        }else{
            _text.setString(*it);
        }
        _text.setPosition(_left + LEFT_MARGIN, height);
        window.draw(_text);
        
        height += _text.getLocalBounds().height + VERTICAL_LINESPACING;
    }

}
void Help_menu::addText(string text){
    _line.push_back(text);
}
void Help_menu::setFont(sf::Font* font){
    _font_ptr = font;
    _text.setFont(*font);
}