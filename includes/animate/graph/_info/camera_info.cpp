#include "camera_info.h"
#include "..\..\constants.h"
Camera_info::Camera_info(){
    _workPanel_dimension        = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);
    _camera_dimension           = CAMERA_DIMENSION;
    _camera_origin_onWind       = sf::Vector2f(_workPanel_dimension.x /2, _workPanel_dimension.y /2);
    _pan_camera                 = PAN_CAMERA;
    _zoom_factor                = 1;
} 

void Camera_info::set_NewWindow(sf::Vector2f new_scr){
    _workPanel_dimension        = sf::Vector2f(new_scr.x * 4/5, new_scr.y);
    _camera_dimension           = _workPanel_dimension;
    _camera_origin_onWind       = sf::Vector2f(_workPanel_dimension.x /2, _workPanel_dimension.y /2);
}
void Camera_info::set_NewWindow(float width, float height){
    set_NewWindow(sf::Vector2f(width,height));
}

void Camera_info::pan_dir(float x, float y){
    _pan_camera = sf::Vector2f(_pan_camera.x + x, _pan_camera.y + y);
}
void Camera_info::zoom_InOut(float delta){

    
    if(_zoom_factor + delta < ZOOM_FACTOR_EPSILON){
        return;
    }
    _zoom_factor = _zoom_factor + delta;
}

void Camera_info::reset_pan_camera(){
    _zoom_factor = 1;
}
void Camera_info::reset_zoom_factor(){
    _pan_camera = PAN_CAMERA;
}