#ifndef ANIMATE_GRAPH_H
#define ANIMATE_GRAPH_H

#include <iostream>
#include <SFML\Graphics.hpp>
using   namespace std;

//Constants
#include "..\constants.h"

//Used Functions From
#include "..\..\shuntingYard_RPN\rpn\rpn.h"
#include "_info\graph_info.h"
#include "plot\plot.h"


//Graph Object recieves a pointer of Graph_info, and plot the graph based of Graph_info 
class Graph{
public:
    Graph();                                //Empty Graph
    Graph(Graph_info*); 
    
    Graph(const Graph& copyMe);
    ~Graph();
    Graph& operator =(const Graph& copy_me);

    //Draw
    void Draw(sf::RenderWindow& window);    //Draw the graph
    //Update:
    void Update(int command);               //Update the graph [by calling Plotter::update to update the points in the graph]
    
    //Modifier
    void set_info(Graph_info*);
    void  toggle_plotPolar();
    void clear();                           //Clear all graphs [set _graph_info to nullptr, also clear _plotter]
    
    //Accessor
    float getRange();
    float getDomain();
    Graph_info* get_GraphInfo();
    //return true if plotting polar, else false;
    bool  is_Polar();
    sf::Vector2f winCordToXy(sf::Vector2f windCord);
private:    
    sf::Font        _stuff;
    Plot*            _plotter;
    Graph_info*      _graph_info;
    bool             _is_polar;
};

#endif