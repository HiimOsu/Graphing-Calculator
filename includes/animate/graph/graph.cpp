#include "graph.h"

#include "../../shuntingYard_RPN/rpn/rpn.h"
#include "translate_cords/translate_cords.h"
//Experimental
Graph::Graph(){
    _graph_info = nullptr;
    _plotter = new Plot(_graph_info);
    _is_polar = false;
}
Graph::Graph(Graph_info* graph_info){
    _graph_info = graph_info;
    _plotter = new Plot(_graph_info);
    _is_polar = false;
}


Graph::Graph(const Graph& copyMe){
    _graph_info = copyMe._graph_info;
    _plotter = new Plot(_graph_info);
}
Graph::~Graph(){
    delete _plotter;
}
Graph& Graph::operator =(const Graph& copyMe){
    _graph_info = copyMe._graph_info;
    _plotter = new Plot(_graph_info);
}

void Graph::Draw(sf::RenderWindow& window){
    if(_graph_info != nullptr)
        _plotter->Draw(window);
}
void Graph::Update(int command){
        
    if(command == COMMAND_GRAPH_TOGGLE_PLOTPOLAR){
        toggle_plotPolar();
    }

    if(_graph_info != nullptr)
        _plotter->Update(_is_polar);
    
}

void Graph::set_info(Graph_info* new_info){
    if(new_info == nullptr){
        clear();
    }
    _graph_info = new_info;
    _plotter->set_info(new_info);
}
void Graph::clear(){
    _plotter->clear();
}
void Graph::toggle_plotPolar(){
    if(_is_polar){
        _is_polar = false;
    }else _is_polar = true;

}

float Graph::getRange(){
    return _graph_info->get_range().y - _graph_info->get_range().x;
}
float Graph::getDomain(){
    return _graph_info->get_domain().y -_graph_info->get_domain().x;
}

bool Graph::is_Polar(){
    return _is_polar;
}
Graph_info* Graph::get_GraphInfo(){
    return _graph_info;
}
sf::Vector2f Graph::winCordToXy(sf::Vector2f windCord){
    if(_graph_info != nullptr)
        return winCord_to_xyCords(windCord,_plotter->get_info());
    else return sf::Vector2f(-99999,-99999);
}