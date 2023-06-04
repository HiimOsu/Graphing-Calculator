#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
#include "../Vector_class/vector/vector_class.h"


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    void setSize(float left, float width, float height); 
    string& operator [](int index);
private:
    sf::RectangleShape rect;            //sidebar rectangle
    Vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object

    float _left;
    float _width;

};

#endif // SIDEBAR_H
