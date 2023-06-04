#include "graph_info.h"
#include "../../constants.h"
#include <iostream>
using namespace std;
Graph_info::Graph_info(){
    set_points(NUMBER_OF_POINTS);
    set_domain(DOMAIN_X);
    set_scaling_factor(SCALE_GRAPH);
    set_camera_info(nullptr);
    set_equation(""); // Empty graph;
    set_PolarDomain(POLAR_DOMAIN_X.x, POLAR_DOMAIN_X.y);
 
}

Graph_info::Graph_info(string equation){
    set_points(NUMBER_OF_POINTS);
    set_domain(DOMAIN_X);
    set_scaling_factor(SCALE_GRAPH);
    set_camera_info(nullptr);
    set_equation(equation); // Equation y = x;
    set_PolarDomain(POLAR_DOMAIN_X.x, POLAR_DOMAIN_X.y);
}


// Graph_info::~Graph_info(){
//     Delete_graph_info();
// }
// void Graph_info::Delete_graph_info(){
//     // Token* ptr;
//     // while(!_eq_postfixQueue.empty()){
//     //     ptr = _eq_postfixQueue.pop();
//     //     if(ptr != nullptr);
//     //         delete ptr;
//     // }
// }
// Graph_info::Graph_info(const Graph_info& copy_me){
//     set_points(copy_me.get_points());
//     set_domain(copy_me.get_domain());
//     set_range(copy_me.get_range());
//     set_scaling_factor(copy_me.get_scaling_factor());
//     set_camera_info(copy_me.get_camera_info());
//     set_equation(copy_me.get_string_eq()); 
// }
// Graph_info& Graph_info::operator =(const Graph_info& copy_me){
//     set_points(copy_me.get_points());
//     set_domain(copy_me.get_domain());
//     set_range(copy_me.get_range());
//     set_scaling_factor(copy_me.get_scaling_factor());
//     set_camera_info(copy_me.get_camera_info());
//     set_equation(copy_me.get_string_eq());
// }

//====settler
void Graph_info::set_equation(string eq){
    _eq_infixString = eq;
}

void Graph_info::set_points(int num_p){
    _num_points = num_p;
}

void Graph_info::set_scaling_factor(sf::Vector2f scale){
    _scale = scale;
}

void Graph_info::set_domain(sf::Vector2f dom_x){
    _domain_x = dom_x;    
}

void Graph_info::set_PolarDomain(float theta1, float theta2){
    _polarDomain_x.x = theta1;
    _polarDomain_x.y = theta2;
}


void Graph_info::set_camera_info(Camera_info* cam_info){
    _camera_info = cam_info;    
}

//===Getter
 int Graph_info::get_points() const{
    return _num_points;
}

 string Graph_info::get_string_eq() const{
    return _eq_infixString;
}

//  Queue<Token*> Graph_info::get_postfix() const{
//     return _eq_postfixQueue;
// }

 sf::Vector2f Graph_info::get_scaling_factor() const{
    return _scale;
}

 sf::Vector2f Graph_info::get_domain() const{

    sf::Vector2f domain_x =  _domain_x;                                     //Grab the vanlila domain
    domain_x = sf::Vector2f( domain_x.x ,     //Panding x
                        domain_x.y);     
    domain_x = domain_x * _camera_info->_zoom_factor;                      //Zooming out    

    return domain_x;
}   

 sf::Vector2f Graph_info::get_range() const{
    float wOh = _camera_info->_camera_dimension.x / _camera_info->_camera_dimension.y;
    float xOhOw = 1/wOh * (( _domain_x.y - _domain_x.x));
    sf::Vector2f range_y =  sf::Vector2f(-xOhOw/2,xOhOw/2) ;                                     //Grab the vanlila domain
    range_y = range_y * _camera_info->_zoom_factor;                      //Zooming out    

    return range_y;
}

 Camera_info* Graph_info::get_camera_info() const{
    return _camera_info;
}

 sf::Vector2f Graph_info::get_PolarDomain() const{
    return _polarDomain_x;
 }
