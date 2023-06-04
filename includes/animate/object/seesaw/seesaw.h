#ifndef OBJECT_SEESAW
#define OBJECT_SEESAW

#include <string>
#include <SFML/Graphics.hpp>
#include "../box/button.h"
class Seesaw : public Box
{
public:
    Seesaw(float width, float height);

    void Draw(sf::RenderWindow& window);

    void setSize(float width, float height);
    void setPosition(float x, float y);
    
    void set_Font(sf::Font* font_ptr);

    void setRight_string(string str);
    void setLeft_string(string str);

    bool is_OnRight(sf::Vector2f winCord);
    bool is_OnLeft(sf::Vector2f winCord);

    //if right is on, turn it off, and then turn left on
    //else toggle left
    //return int tell which button is on, left = 1, right = 2, none = 0
    int toggle_left();

    //if left is on, turn it off, and then turn right on
    //else toggle right;
    //return int tell which button is on, left = 1, right = 2, none = 0
    int toggle_right();
    
    //Turn off both button
    int balanceBoth();

private:
    bool _left_toggle, _right_toggle;
    string _left_str, _right_str;
    Button _button;
};


#endif