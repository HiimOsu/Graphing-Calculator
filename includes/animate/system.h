#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/Graphics.hpp>
using namespace std;

#include "graph/graph.h"
#include "graph/_info/graph_info.h"
#include "graph/axis/axis.h"
#include "../shuntingYard_RPN/queue/MyQueue.h"
#include "../Vector_class/vector/vector_class.h"

class System
{
public:
    System();                                   //Create an empty screen, no axis and no _graph
    void Step(int command);                     //Step by command
    void Draw(sf::RenderWindow& widnow);        //Draw depends on window
    
    Camera_info* get_camera_info();             //return _camera_info [good for modifying the camera] 
    void    set_graph(Graph_info* new_info);    //set the current graph to draw (axis would also be set)
    void    clear();                            //clear all _axis and _graph
                                                    //After clear _axis and _graph is empty, and will not draw anything

    sf::Vector2f getXY(sf::Vector2f windCord);  //Turn Window Coordinate to XY Cartesian Coordinate
    Graph_info* get_GraphInfo();
    bool  is_polar(){return _graph.is_Polar();}
private:
    Camera_info _camera_info;       
    Graph _graph;                               //Graph object draws current holding _Graph_info
                                                    //if it holds nothing, it is an empty graph
    Axis _axis;                                 //Axis is dependent on _graph. If _graph is empty, axis is also empty
};

#endif // SYSTEM_H
