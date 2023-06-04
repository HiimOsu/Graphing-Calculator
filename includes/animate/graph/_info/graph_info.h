#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

#include <string>
#include <SFML\Graphics.hpp>
using namespace std;

#include "..\..\..\shuntingYard_RPN\shunting_yard\shunting_yard.h"
#include "..\..\..\shuntingYard_RPN\token\tk_string.h"
#include "..\..\..\shuntingYard_RPN\token\token.h"
#include "camera_info.h"

//Graph_info affects what points would be plotted, and How would the points be plotted
//And these information usually were used by the Graph object in Update(int command) function.  
    //In updating the graph
    //Or altered by the the type of command, such as zoom in would increase the scaling of the graph

/*Fields in graph_info:
    _camera_info*:
        pointer pointing to current _camera_info
    _eq_infixString:
        it is the equation of the Graph in pre/infix
    _domain_x:
        Domain X affects the (X_n) value to be evaluated by graph objects,
        And it is the end points of X-axis.
    _range_y:
        Domain Y affects the points which to be shown/plot on the screen
        And it is the end points of Y-axis.
        only  abs(f(x)) < Range is shown. 
   
    _scale:
        scaling factor scale the whole graph of f(x)
        scaling factor(a,b) would turn f(x) into b* f(a*x);
    _num_points:
        # of Points
        The maximum points that will be plotted onto the screen 

*/
//Notice the center of the screen is always the middle of the Working_Panel in the window
//It might be changed, if I add another info that records the global coordinate
    //Ideas:
    //  adding screen_info 1.(might be a pointer) 2.(might be created by System, and manage by System);
    //      screen_info:
                //vector2f: screen_dimension, screen_origin
class Graph_info
{
public:
    Graph_info();
    Graph_info(string equation);
    
    
    // Graph_info(const Graph_info& copy_me);
    // Graph_info& operator =(const Graph_info& copy_me);
    // ~Graph_info();
    // void Delete_graph_info();


    void set_points(int num_p);
    void set_equation(string eq);
    void set_scaling_factor(sf::Vector2f scale);
    void set_domain(sf::Vector2f dom_x);
    void set_range(sf::Vector2f ran_y);
    void set_camera_info(Camera_info* _cam_info);
    void set_PolarDomain(float theta1, float theta2);
   
    int get_points() const;
    string get_string_eq() const;
    // Queue<Token*> get_postfix() const;
    Camera_info* get_camera_info() const;
    sf::Vector2f get_scaling_factor() const;
    sf::Vector2f get_domain() const;
    sf::Vector2f get_range() const;
    sf::Color   get_Color() const;
    sf::Vector2f get_PolarDomain() const;

private:
    int _num_points;
    string _eq_infixString;
    // Queue<Token*> _eq_postfixQueue;
    sf::Vector2f _scale,
                _domain_x,
                _polarDomain_x;
    sf::Color   _graph_color;
    Camera_info* _camera_info;
};

#endif