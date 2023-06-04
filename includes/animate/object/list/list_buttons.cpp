#include "list_buttons.h"



List_Button:: List_Button(sf::Vector2f size): _headLabel("Change Label Name Here", size.x, size.y / 8, sf::Color::Red, sf::Color::Red)
{
    _headLabel.set_TextColor(sf::Color::Yellow);
    _size = size;
}



void List_Button::Draw(sf::RenderWindow& window){
    _headLabel.Draw(window);

    if(!_hidden){
        int count = 0;
        for( Vector<Button>::Iterator it = _listButton.at(_currentIndex -1);
            it != _listButton.end(); it++)
            {
                count++;
                if(count > _numberOfButton){
                    break;
                }
                it->Draw(window);
            }
    }
}

void List_Button::setFont(sf::Font* font){
    _font_ptr = font;
    _headLabel.set_Font(_font_ptr);

    if(!_listButton.empty()){
        for( Vector<Button>::Iterator it = _listButton.begin(); //Check on which index
        it != _listButton.end(); it++)
        {
            it->set_Font(font);
        }
    }
}
void List_Button:: setSize(sf::Vector2f size){
    _size = size;

    sf::Vector2f head_size = sf::Vector2f(_size.x, _size.y / 8);
    if(_hidden){
        head_size.y /= 2;
    }
    _headLabel.set_Size(head_size);


    if(!_listButton.empty()){
        float height_button     = _size.y * 7/8 / _numberOfButton;
        sf::Vector2f _size_button( _size.x /4 * 3, height_button);
        for( Vector<Button>::Iterator it = _listButton.begin(); //Check on which index
        it != _listButton.end(); it++)
        {
            it->set_Size(_size_button);
        }
    }
}

void List_Button::setPosition(sf::Vector2f winCor){
    _headLabel.set_Position(winCor);
    if(!_listButton.empty()){
        
        int count = 0;
        float gap = 2;
        float height_button     = _size.y * 7/8 / _numberOfButton;          //Height of each button
        float offset_button     = (height_button +  gap);  //The distance between each button
        sf::Vector2f head_pos   = _headLabel.get_Position();
        
        for( Vector<Button>::Iterator it = _listButton.at(_currentIndex -1); //Starting at the current index
        it != _listButton.end() && count < _numberOfButton; it++)
        {
            it->set_Position(sf::Vector2f(head_pos.x, head_pos.y +  _size.y /8 + offset_button * count));
            count ++;
        } 
    }
}
void List_Button::setLabel_String(string str){
    _headLabel.set_String(str);
}
void List_Button::setLabel_FillColor(sf::Color color){
    _headLabel.set_Fill_Color(color);
}
void List_Button::setLabel_OutlineColor(sf::Color color){
    _headLabel.set_Outline_Color(color);
}

void List_Button::setList_FillColor(sf::Color color, int index, int to_index){
    assert(index < to_index && "[Error] setList_FillColor: incorrect index");
    if(to_index > 1){

        assert(index <= _listButton.size()&& "[Error] setList_FillColor: incorrect index");
        assert(to_index <= _listButton.size()&& "[Error] setList_FillColor: incorrect index");

        for( Vector<Button>::Iterator it = _listButton.at(index -1); //Starting at the current index
        it != _listButton.at(to_index -1); it++)
        {   
            if(it == _listButton.end()){
                return;
            }
            it->set_Fill_Color(color);
        } 
        return;
    }   

    if(index > 0){

        assert(index <= _listButton.size() && "[Error] setList_FillColor: incorrect index");
        _listButton[index -1].set_Fill_Color(color);

        return;
    }

    for( Vector<Button>::Iterator it = _listButton.begin(); //Starting at the current index
    it != _listButton.end(); it++)
    {   
        it->set_Fill_Color(color);
    } 
    return;
}
void List_Button::setList_OutlineColor(sf::Color color, int index, int to_index){
    assert(index < to_index && "[Error] setList_OutlineColor: incorrect index");
    if(to_index > 1){

        assert(index <= _listButton.size()&& "[Error] setList_OutlineColor: incorrect index");
        assert(to_index <= _listButton.size()&& "[Error] setList_OutlineColor: incorrect index");

        for( Vector<Button>::Iterator it = _listButton.at(index -1); //Starting at the current index
        it != _listButton.at(to_index -1); it++)
        {   
            it->set_Outline_Color(color);
        } 
        return;
    }   

    if(index > 0){

        assert(index <= _listButton.size() && "[Error] setList_OutlineColor: incorrect index");
        _listButton[index -1].set_Outline_Color(color);

        return;
    }

    for( Vector<Button>::Iterator it = _listButton.begin(); //Starting at the current index
    it != _listButton.end(); it++)
    {   
        it->set_Outline_Color(color);
    } 
}
void List_Button:: setList_CharacterSize(int size, int index, int to_index){
    assert(index < to_index && "[Error] setList_CharacterSize: incorrect index");
    if(to_index > 1){
        assert(index <= _listButton.size()&& "[Error] setList_CharacterSize: incorrect index");
        assert(to_index <= _listButton.size()&& "[Error] setList_CharacterSize: incorrect index");

        for( Vector<Button>::Iterator it = _listButton.at(index -1); //Starting at the current index
        it != _listButton.at(to_index -1); it++)
        {   
            it->set_CharacterSize(size);
        } 
        return;
    }   

    if(index > 0){

        assert(index <= _listButton.size() && "[Error] setList_CharacterSize: incorrect index");
        _listButton[index -1].set_CharacterSize(size);

        return;
    }

    for( Vector<Button>::Iterator it = _listButton.begin(); //Starting at the current index
    it != _listButton.end(); it++)
    {   
        it->set_CharacterSize(size);
    } 
}
void List_Button:: setList_String(string str, int index){
    assert(index <= _listButton.size()&& "[Error] setList_CharacterSize: incorrect index");
    assert(index > 0 && "[Error] setList_String: incorrect index");

    _listButton[index -1].set_String(str);
}


void List_Button::scrollDown(){
    if(_currentIndex != _listButton.size()){
        _currentIndex += 1;
        refresh();
    }
}

void List_Button::scrollUp(){
    if(_currentIndex != 1){
        _currentIndex -=1;
        refresh();
    }
}
void List_Button:: addButton(string buttonLabel){
    Vector<Button>::Iterator it;
    float height_button     = _size.y * 7/8 / _numberOfButton;      //Height of each button

    it =_listButton.push_back(Button(buttonLabel , _size.x /4 * 3, height_button,  
     SB_BOX_FILL_COLOR,sf::Color::Green));
    it->set_Font(_font_ptr);


    if(_listButton.size() - _currentIndex < _numberOfButton){
        float gap = 2;
        float offset_button     = ( height_button +  gap) * (_listButton.size() - _currentIndex) + _size.y /8 ;   //The OFFSET from the top(current_index)

        sf::Vector2f head_pos   = _headLabel.get_Position();
        
        it->set_Position(sf::Vector2f(head_pos.x, head_pos.y  + offset_button));
     }
    
}
void List_Button::removeButton(int index){
    assert(index <= _listButton.size()&& "[Error] removeButton: incorrect index");
    assert(index > 0 && "[Error] removeButton: incorrect index");
    _listButton.erase(index -1);

    if(index > _currentIndex && index < _currentIndex + _numberOfButton){   //Update position if it affect the List
        setPosition(_headLabel.get_Position());
    }
}
void List_Button::removeAllButton(){
    _listButton.clear();
    _currentIndex = 1;
}
void List_Button:: HideShow_List(){
    sf::Vector2f head_size = sf::Vector2f(_size.x, _size.y / 8);

    if(_hidden){
        _hidden = false;
    }
    else {
        _hidden =  true;
        head_size.y = head_size .y / 2;
    }
    _headLabel.set_Size(head_size);
}                         

sf::Vector2f List_Button::getSize(){
    return _size;
}
sf::Vector2f List_Button::getPosition(){
    return _headLabel.get_Position();
}
bool List_Button::is_hidden(){
    return _hidden;
}
int List_Button::isOnTheList(sf::Vector2f winCor){
    if(! is_hereInside_TheBox(winCor, _headLabel.get_Position(), _size)){
        return -1;
    }
    if(_hidden){    //If the list is hidden return -1
        if(_headLabel.is_Inside(winCor)){   //If it is on the head label
            return 0;
        }
        return -1;     
    }


    int count = 0;
    for( Vector<Button>::Iterator it = _listButton.at(_currentIndex -1); //Check on which index
    it != _listButton.end(); it++)
    {
        if(count > _numberOfButton){
            break;
        }
        if(it->is_Inside(winCor)){
            return _currentIndex + count;
        }
        count++;    
    }
    
    if(_headLabel.is_Inside(winCor)){   //If it is on the head label
        return 0;
    }
    return -1;
}