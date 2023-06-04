#ifndef OBJECT_HELP_MENU
#define OBJECT_HELP_MENU

#include <SFML/Graphics.hpp>
#include "../box/box.h"
#include "../../../Vector_class/vector/vector_class.h"

class Help_menu
{
public:
    Help_menu(float width, float height);
    Help_menu(const Help_menu& copy_me);

    void Draw(sf::RenderWindow& window);
    void addText(string text);
    void setFont(sf::Font *font);
    void setPosition(float left, float top){_left = left; _top = top;}
private:
    float _left = 0, _top = 0;
    
    Box _box_window;    //Where the text will be drawn on
    sf::Text _text;     //Object control drawing text
    sf::Font* _font_ptr = nullptr;
    Vector<string> _line;   //store the line of text
};



#endif