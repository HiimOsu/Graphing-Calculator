#include "axis.h"

#include "../../constants.h"
#include "../translate_cords/translate_cords.h"
Axis::Axis(){
    _graph_info = nullptr;
    
//     _x_axis.setFillColor(sf::Color::White);
//     _x_axis.setSize(sf::Vector2f(CAMERA_DIMENSION.x, 1.f));
//     _x_axis.setOrigin(0, 1.f/2.f);
//     _x_axis.setPosition(0, CAMERA_DIMENSION.y * 1/2.f);

//     _y_axis.setFillColor(sf::Color::White);
//     _y_axis.setSize(sf::Vector2f(1.f, CAMERA_DIMENSION.y));
//     _y_axis.setOrigin(1/2.f, 0);
//     _y_axis.setPosition(CAMERA_DIMENSION.x /2, 0);
}

Axis::Axis(Graph_info* _info){
    _graph_info = _info;
    if(_graph_info == nullptr){
        return;
    }

    sf::Vector2f temp;
    
    _x_axis.setFillColor(sf::Color::White);
    _y_axis.setFillColor(sf::Color::White);
    _x_axis.setOrigin(0, 1.f/2.f);
    _y_axis.setOrigin(1/2.f, 0);


    refresh_axis();
    
}

void Axis::Update(int command){
    if(command){
        refresh_axis();
    }
}
void Axis::Draw(sf::RenderWindow& window){
    if(_graph_info != nullptr){
        window.draw(_x_axis);
        window.draw(_y_axis);
    }
}

void Axis::refresh_axis(){
    if(_graph_info != nullptr){
        sf::Vector2f temp;
        
        _x_axis.setSize(sf::Vector2f(_graph_info->get_camera_info()->_camera_dimension.x, 1.f));

        temp = xyCord_to_winCords(
        sf::Vector2f(_graph_info->get_domain().x + _graph_info->get_camera_info()->_pan_camera.x,
            0)
        ,_graph_info);

        if(temp != sf::Vector2f(-1,-1)){
            _x_axis.setPosition(temp);
        }else _x_axis.setPosition(0,0);


        _y_axis.setSize(sf::Vector2f(1.f, _graph_info->get_camera_info()->_camera_dimension.y));
        
        temp = xyCord_to_winCords(
        sf::Vector2f(0,
            _graph_info->get_range().y + _graph_info->get_camera_info()->_pan_camera.y)
        ,_graph_info);
        
        if(temp != sf::Vector2f(-1,-1)){
            _y_axis.setPosition(temp);
        }else _y_axis.setPosition(0,0);
    }
}
void Axis::set_graph(Graph_info* new_info){
    if(_graph_info == nullptr)
        clear();
    _graph_info = new_info;

}
void Axis::clear(){
    _graph_info = nullptr;
}