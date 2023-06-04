#ifndef CAMERA_INFO_H
#define CAMERA_INFO_H

#include    <SFML/Graphics.hpp>
struct Camera_info{
    Camera_info();  
    sf::Vector2f _camera_dimension,         //The dimension of the camera/the inner window that holds the graph
                 _camera_origin_onWind,     //The origin of the camera in Window coordinate.
                _workPanel_dimension,       //The dimension of the WorkPanel
                _pan_camera;                //Unit of _pan_camera is in x-y coordinate system, instead of Window coordinate
                                                    //(It sounds weird, but it works)
    float _zoom_factor;                     //Factor of zooming in, and zooming out

    void set_NewWindow(sf::Vector2f new_scr);       //Each time the main window (now the camera) resizes
    void set_NewWindow(float width, float height);  //,call this functions to update artributes
    void pan_dir(float x, float y);                 //Panding the camera to vector2f dir(x,y)
                                                    //,positive: to the right/up, negative to the left/down
    void zoom_InOut(float delta);                   //Zoom in or Out by changing the _zoom_factor, imagine default zoom factor is 1.0x
                                                    //By giving delta, it change factor = factor + delta
                                                        //Least (/Greates) zoom factor can be chang in the animate/constants.h, [ZOOM_FACTOR_IN/OUT] 

    void reset_zoom_factor();                       //reset zoom factor to default value 1.0x
    void reset_pan_camera();                        //reset pan_camerat to default value (0,0)
};



#endif