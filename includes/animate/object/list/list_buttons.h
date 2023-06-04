#ifndef LIST_OF_BUTTONS
#define LIST_OF_BUTTONS
#include <SFML/Graphics.hpp>
#include <string>

#include "..\box\button.h"


#include "../../../Vector_class/vector/vector_class.h"

const int MAX_NUMB_OF_BUTTON_IN_A_LIST = 20;
class List_Button
{
public:
    List_Button(sf::Vector2f dimension);
    
    void Draw(sf::RenderWindow& window);
    
    void setFont(sf::Font* font);

    //Chaning the Size of the List
    void setSize(sf::Vector2f dimension);
    //Setting the position of the List
    void setPosition(sf::Vector2f winCor);
    void setLabel_String(string str);
    void setLabel_FillColor(sf::Color color);
    void setLabel_OutlineColor(sf::Color color);
    
    void setList_FillColor(sf::Color color, int index = -1, int to_index = 0);
    void setList_OutlineColor(sf::Color color, int index = -1, int to_index = 0);
    void setList_CharacterSize(int size, int index = -1, int to_index = 0);
    void setList_String(string str, int index);


    void scrollUp();
    void scrollDown();

    void addButton(string buttonLabel);
    void removeButton(int index);
    void removeAllButton();
    void HideShow_List();                                
    
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    bool is_hidden();
    int isOnTheList(sf::Vector2f winCor);           //return the index of which button you were in, ListLabel is 0
                                                    //The content _listButton starting at 1.
                                                        // -1 means is not on the list;
    
private:
    Button _headLabel;
    Vector<Button> _listButton;
    bool _hidden = false;
    sf::Vector2f _size;             //The size of the List: Width x Height
    sf::Font* _font_ptr = nullptr;  //The font

    int _currentIndex = 1;          //Show the index of the first buttom to show
    int _numberOfButton = 7;       //Max # of buttons shown in one time
    int _MaxNumbOfButton = MAX_NUMB_OF_BUTTON_IN_A_LIST;    // Max # of buttons could be stored in list
    void refresh(){setPosition(_headLabel.get_Position());} //refresh the list whenever the headlabel moved, or scrolling the list
};


#endif