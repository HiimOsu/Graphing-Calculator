#include "input_box.h"
#include <iostream>
using namespace std;

Input_box::Input_box(){
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::Green);
    playerInput.clear();

}
void Input_box::input(sf::Event wordTyped){
    if(wordTyped.type == sf::Event::TextEntered){

            if (wordTyped.text.unicode == '\b') { // handle backspace explicitly
                if(playerInput.size() != 0)
                    playerInput.erase(playerInput.size() - 1, 1);
            } else { // all other keypresses
                if(wordTyped.text.unicode < 128 && wordTyped.text.unicode != '\r' && wordTyped.text.unicode != '\n'){
                    
                    playerInput += static_cast<char>(wordTyped.text.unicode);
                    
                }
            }
        
        playerText.setString(playerInput + _u_str);
    }
}

void Input_box::set_font(sf::Font* font){
    playerText.setFont(*font);
}
void Input_box::set_size(float width, float height){
    _inputBox.set_Size(sf::Vector2f(width,height));
}

void Input_box::set_text(sf::Text text){
    const sf::Font* font = playerText.getFont();
    const sf::Vector2f windCord = playerText.getPosition();
    playerText = text;
    playerText.setFont(*font);
    playerText.setPosition(windCord);
}

void Input_box::set_position(sf::Vector2f windCord){
    _inputBox.set_Position(windCord);
    playerText.setPosition(sf::Vector2f(windCord.x + _inputBox.get_Size().x * 1/20, windCord.y));
}




void Input_box::hideShow_underScore(){
    if(_underscore){
        _underscore = false;
        _u_str = "";
    }else{
        _underscore = true;
        _u_str = "_";
    }

    playerText.setString(playerInput + _u_str);
}
bool Input_box::underscore(){
    return _underscore;
}


string Input_box::getInput(){
    
    return playerInput;
}

void Input_box::clearInput(){
    playerInput.clear();
    playerText.setString(playerInput);
}
bool Input_box::is_open(){
    return _is_open;
}

bool Input_box::close(){
    _is_open = false;
}
bool Input_box::Open(float width, float height, sf::Color filled, sf::Color outline){
    _is_open = true;
    clearInput();

    sf::Vector2f windCord = _inputBox.get_Position();
    _inputBox = Box(width, height, filled, outline);
    _inputBox.set_Position(windCord);
}

void Input_box::Draw(sf::RenderWindow& window){
    if(_is_open){
        _inputBox.Draw(window);
        window.draw(playerText);
    }
}

