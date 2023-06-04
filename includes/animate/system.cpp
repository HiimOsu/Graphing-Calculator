#include "system.h"
#include <iostream>

#include "constants.h"
System::System()
{}



//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command){
    bool update_graph = false;
    if(_graph.get_GraphInfo() == nullptr){
        return;
    }
    if(command){
        update_graph = true;
    }
    switch (command)
    {
    case COMMAND_RESIZE_WINDOW:
        break;
    case COMMAND_GRAPH_PAN_DOWN_LEFT:
        _camera_info.pan_dir(-3 * _graph.getDomain() / _camera_info._camera_dimension.x,0);
        _camera_info.pan_dir(0,-3* _graph.getRange() / _camera_info._camera_dimension.y);

        break;
    case COMMAND_GRAPH_PAN_DOWN_RIGHT:
        _camera_info.pan_dir(3 * _graph.getDomain() / _camera_info._camera_dimension.x ,0);
        _camera_info.pan_dir(0,-3* _graph.getRange() / _camera_info._camera_dimension.y);
        break;
    case COMMAND_GRAPH_PAN_UP_RIGHT:
        _camera_info.pan_dir(3 * _graph.getDomain() / _camera_info._camera_dimension.x ,0);
        _camera_info.pan_dir(0,3 * _graph.getRange() / _camera_info._camera_dimension.y);
        break;
    case COMMAND_GRAPH_PAN_UP_LEFT:
        _camera_info.pan_dir(-3 * _graph.getDomain() / _camera_info._camera_dimension.x,0);
        _camera_info.pan_dir(0,3 * _graph.getRange() / _camera_info._camera_dimension.y);
        break;
    case COMMAND_GRAPH_PAN_DOWN:
        _camera_info.pan_dir(0,-3* _graph.getRange() / _camera_info._camera_dimension.y);
        break;
    case COMMAND_GRAPH_PAN_UP:
        _camera_info.pan_dir(0,3 * _graph.getRange() / _camera_info._camera_dimension.y);
        break;
    case COMMAND_GRAPH_PAN_LEFT:
        _camera_info.pan_dir(-3 * _graph.getDomain() / _camera_info._camera_dimension.x,0);
        break;
    case COMMAND_GRAPH_PAN_RIGHT:
        _camera_info.pan_dir(3 * _graph.getDomain() / _camera_info._camera_dimension.x ,0);
        break;
    case COMMAND_GRAPH_ZOOM_IN:
        _camera_info.zoom_InOut(-ZOOM_FACTOR_DELTA);
        break;
    case COMMAND_GRAPH_ZOOM_OUT:
        _camera_info.zoom_InOut(ZOOM_FACTOR_DELTA);
        break;
    case COMMAND_CLEAR_CAMERA:
        clear();
        break;
    case COMMAND_RESET_CAMERA:
        _camera_info.reset_pan_camera();
        _camera_info.reset_zoom_factor();
        break;
    }

    if(update_graph){
        _graph.Update(command);
        _axis.Update(command);
    }
}
void System::Draw(sf::RenderWindow& window){
    _axis.Draw(window);
    _graph.Draw(window);
}

void System::set_graph(Graph_info* new_info){
    if(new_info == nullptr){
        clear();
        return;
    }
    new_info->set_camera_info(&_camera_info);
    _graph.set_info(new_info);
    _axis.set_graph(new_info);
    _axis.refresh_axis();
    
    _graph.Update(COMMAND_GRAPH_REFRESH);
}
void System::clear(){
    _graph.clear();
    _axis.clear();
}
Camera_info* System::get_camera_info(){
    return &_camera_info;
}
Graph_info* System::get_GraphInfo(){
    return _graph.get_GraphInfo();
}

sf::Vector2f System::getXY(sf::Vector2f windCord){
    
     return _graph.winCordToXy(windCord);
}
