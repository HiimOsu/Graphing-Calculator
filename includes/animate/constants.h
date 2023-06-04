#ifndef ANIMATE_CONSTANTS_H
#define ANIMATE_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>
const float SCREEN_WIDTH    = 1400;
const float SCREEN_HEIGHT   = 800;
const float WORK_PANEL      = SCREEN_WIDTH*4/5;
const float SIDE_BAR        = SCREEN_WIDTH*1/5;


const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;

//Box
    const float SB_BOX_WIDTH = SIDE_BAR;
    const float SB_BOX_HEIGHT = SCREEN_HEIGHT / 20;
    const sf::Color SB_BOX_FILL_COLOR(sf::Color(105,105,105));
    const sf::Color SB_BOX_OUTLINE_COLOR(sf::Color(0,255,0));
//Enum
    enum COMMAND_TYPE{
        COMMAND_DEFAULT,
        COMMAND_RESET_CAMERA,
        COMMAND_CLEAR_CAMERA,
        COMMAND_RESIZE_CAMERA,
        COMMAND_RESIZE_WINDOW,
        COMMAND_GRAPH_RESET,
        COMMAND_GRAPH_ZOOM_OUT,
        COMMAND_GRAPH_ZOOM_IN,
        COMMAND_GRAPH_PAN_UP,
        COMMAND_GRAPH_PAN_DOWN,
        COMMAND_GRAPH_PAN_LEFT,
        COMMAND_GRAPH_PAN_RIGHT,
        COMMAND_GRAPH_PAN_DOWN_LEFT,
        COMMAND_GRAPH_PAN_DOWN_RIGHT,
        COMMAND_GRAPH_PAN_UP_RIGHT,
        COMMAND_GRAPH_PAN_UP_LEFT,
        COMMAND_GRAPH_REFRESH,
        COMMAND_GRAPH_TOGGLE_PLOTPOLAR
    };

//Plot:
        const float POINT_SIZE = 1.0f;
        const sf::Color POINT_COLOR = sf::Color::Green;
//Camera_info

    //Panding factor (in x-y coordinate)
    const float PAND_VERTICAL = 0;
    const float PAND_HOIZONTAL = 0;
    const float ZOOM_FACTOR_DELTA = 1e-2;
    const float ZOOM_FACTOR_EPSILON = 1e-3;
    const sf::Vector2f PAN_CAMERA(PAND_HOIZONTAL, PAND_VERTICAL);
//Graph_info:
        
        //Affects the size of the Screen
        //Screen size: Length x Width
        const float CAMERA_WIDTH        = WORK_PANEL;
        const float CAMERA_HEIGHT       = SCREEN_HEIGHT;

        const sf::Vector2f CAMERA_DIMENSION(CAMERA_WIDTH,CAMERA_HEIGHT);
        //Domain And Range
        //Domain X affects the value to be evaluated by graph objects,
        //And it is the end points of X-axis.
        //Domain Y affects the points which to be shown/plot on the screen
            //And it is the end points of Y-axis.
            //only  abs(f(x)) < Range is shown. 
        const double _X = 20;
        const sf::Vector2f DOMAIN_X(-_X,_X); 
        const double _POLAR_X = 20;
        const sf::Vector2f POLAR_DOMAIN_X(0, _POLAR_X);
    
        //Scaling the Graph directly, change of Domain & Range
        const double SCALE_DOMAIN_X     = 1;
        const double SCALE_RANGE_Y     = 1;
        const sf::Vector2f SCALE_GRAPH(SCALE_DOMAIN_X,SCALE_RANGE_Y);

        //# of Points
        //The maximum points that will be plotted onto the screen 
        const int NUMBER_OF_POINTS      = 10000;


//Predefined Graphs...
    //...
//"x ^ 3 - 3 * x ^ 2 + 3"
    const std::string EQUATION = "tan x";
#endif // CONSTANTS_H
