#ifndef SFML_INPUT_BOX
#define SFML_INPUT_BOX

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#include "../box/box.h"
#include "../../constants.h"

class Input_box
{
public:
    Input_box();
    ~Input_box(){
        _is_open = false;
    }
    void input(sf::Event wordTyped);
    void set_size(float width, float height);
    void set_font(sf::Font* font);
    void set_text(sf::Text text);

    void set_position(sf::Vector2f winCord);
    string getInput();
    void clearInput();
    void hideShow_underScore();

    bool is_open();
    bool underscore();
    bool close();
    bool Open(float width, float height, sf::Color filled = sf::Color::Black, sf::Color outline = sf::Color::Green);
    void Draw(sf::RenderWindow& window);

private:
    string playerInput, _u_str;
    sf::Text playerText;
    Box _inputBox = Box(0, 0, sf::Color::Black, sf::Color::Green);
    bool _is_open = false;
    bool _underscore = false;

};

#endif