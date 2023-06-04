#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include "system.h"
#include "sidebar.h"
#include "../Vector_class/vector/vector_class.h"
#include "graph/_info/graph_info.h"

#include "object/box/button.h"
#include "object/list/list_buttons.h"
#include "object/input_box/input_box.h"
#include "object/help_menu/help_menu.h"
class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    
    Vector<string> export_StoredEquation();
    void  import_Equation(Vector<string> eq);

private:
    string get_Input();                                     //Open the inputBox
    void help_menu();                                       //Open help_menu
    
    Graph_info* get_GInfo_from_GHistoryList(int index);      //get the graph_info from vecotr
    void add_Graph(string equation);                         //add graph 
    
    void resizeWidnow(sf::Event event);
    int getCommand_EventPanding(sf::Event event);           //Proccess mutiple keypress for panding
    //Entity
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    System system;                      //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar
    List_Button history_list;           //History List to draw on the screen
    Button _button_polarMode, _button_helperMenu;


    //Variable
    int command;                        //command to send to system
    bool mouseIn;                       //mouse is in the screen
    sf::Font font;                      //font to draw on main screen
    sf::Clock clock;                    //Clock for calculating elapsed time
    sf::Time elapsed1;                  //Elapsed time1
    Vector<Graph_info *> _graph_vector; //Place to hold graphs_info

    bool _up = false,_down = false, _left= false, _right= false; //Toogle of arrow key
};

//Init input Box base on the window size
Input_box initbox(sf::Vector2u window_size);

//Return the helping Menu base on window size
//And given the font, to set text font
Help_menu init_helpMenu(float width, float height, sf::Font* font_ptr);

//init the polarMode button given window size
Button initButton_polarMode(sf::Vector2u window_size);

//init the helpMenu button given window size
Button initButton_helperMenu(sf::Vector2u window_size);

//Take a floating number, then rount it up to [digit] decimal point
float roundTo(float num, int digit);

//Take a floating number, then rount it up to [digit] decimal point
//Then return it as a string
string roundTo_String(float num, int digit);


int  try_userInput(string str, string& part);
#endif // GAME_H
