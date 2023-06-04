#ifndef GRAPH_AXIS_H
#define GRAPH_AXIS_H

#include "SFML/Graphics.hpp"
#include "../_info/graph_info.h"

class Axis{
public:
    Axis();
    Axis(Graph_info* _info);

    void Update(int command);
    void Draw(sf::RenderWindow& window);
    
    
    void set_graph(Graph_info*);
    void clear();                               //Clear the current graph, have to set the graph again afterwards
    void refresh_axis();
private:
    Graph_info* _graph_info;
    sf::RectangleShape _x_axis;
    sf::RectangleShape _y_axis;
};

#endif