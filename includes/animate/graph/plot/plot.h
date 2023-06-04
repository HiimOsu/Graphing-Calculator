#ifndef GRAPH_PLOT_H
#define GRAPH_PLOT_H

#include <SFML\Graphics.hpp>
using namespace std;

#include "..\_info\graph_info.h"
#include "..\..\..\Vector_class\vector\vector_class.h"


class Plot{
public:
    Plot(Graph_info* graph_info);

    void Draw(sf::RenderWindow& window);
    void Update(bool is_polar);
    
    
    void update_lines(bool is_polar);                            //updating the points on screen-coordinate
    void set_info(Graph_info* graph_info);          //Set a new graph to draw: call whenever needed to set a new graph
    void clear();                                   //Clear the current graph, have to set the graph again afterwards
    
    
    Graph_info* get_info();
private:
    Graph_info* _graph_info;
    Vector<sf::CircleShape>  _lines;

};
    Vector<sf::Vector2f> compute_points(string equation ,int num_point, sf::Vector2f domain);               //get vector of points

    
#endif