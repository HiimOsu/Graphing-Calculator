#include "translate_cords.h"
#include "../../constants.h"
sf::Vector2f winCord_to_xyCords(sf::Vector2f winCord, Graph_info* info){
    sf::Vector2f camera_Origin_onScr(info->get_camera_info()->_camera_origin_onWind),
    domain_x = info->get_domain() ,
    range_y = info->get_range() ,
    camera_dim = info->get_camera_info()->_camera_dimension,
    graph_origin_onScr;

    double y_perPixel = ((range_y.y - range_y.x)) / camera_dim.y;
    double x_perPixel = (domain_x.y - domain_x.x) / camera_dim.x;
    graph_origin_onScr.y = camera_Origin_onScr.y + info->get_camera_info()->_pan_camera.y / y_perPixel;
    graph_origin_onScr.x = camera_Origin_onScr.x - info->get_camera_info()->_pan_camera.x * x_perPixel ;

    double winY_atGraph = -y_perPixel * (winCord.y - graph_origin_onScr.y);
    double winX_atGraph = x_perPixel * (winCord.x - graph_origin_onScr.x);


    return sf::Vector2f(winX_atGraph,winY_atGraph);
}

sf::Vector2f xyCord_to_winCords(sf::Vector2f xyCord, Graph_info* info){
    // sf::Vector2f camera_Origin_onScr(info->get_camera_info()->_camera_origin_onWind),
    sf::Vector2f camera_Origin_onScr(info->get_camera_info()->_camera_origin_onWind),
    domain_x = info->get_domain() ,
    range_y = info->get_range() ,
    camera_dim = info->get_camera_info()->_camera_dimension,
    graph_origin_onScr;

    double pixel_perY = camera_dim.y / ((range_y.y - range_y.x) );
    graph_origin_onScr.y = camera_Origin_onScr.y + info->get_camera_info()->_pan_camera.y * pixel_perY  ;
    // * info->get_camera_info()->_zoom_factor ;

    double y_atScr = -pixel_perY * xyCord.y + graph_origin_onScr.y ;
    //  + camera_Origin_onScr.y + info->get_camera_info()->_pan_camera.y * pixel_perY;
    
    //if the point is out of the camera (out of Bound)
    if(y_atScr > camera_Origin_onScr.y + CAMERA_WIDTH /2
    || y_atScr < camera_Origin_onScr.y - CAMERA_WIDTH /2){
        return sf::Vector2f(-1,-1);
    }

    double pixel_perX = camera_dim.x / ( (domain_x.y - domain_x.x));
    
    graph_origin_onScr.x = camera_Origin_onScr.x - info->get_camera_info()->_pan_camera.x * pixel_perX ;
    // * info->get_camera_info()->_zoom_factor;

    double x_atScr = pixel_perX * xyCord.x + graph_origin_onScr.x;
    // + camera_Origin_onScr.x - info->get_camera_info()->_pan_camera.x * pixel_perX ;



    return sf::Vector2f(x_atScr, y_atScr);
    
}


// sf::Vector2f xyCord_to_polCords(sf::Vector2f xyCord){
//     Matrix<float> transform(2,2,0);
    
//     float x = xyCord.x, y = xyCord.y;
//     transform[1][1] = (x) / sqrt(pow(x, 2) + pow(y, 2));
//     transform[1][2] = (y) / sqrt(pow(x, 2) + pow(y, 2));
//     transform[2][1] = -(y) / (pow(x, 2) + pow(y, 2));
//     transform[2][2] =  (x) / (pow(x, 2) + pow(y, 2));

//     for(int j = 1; j <= 2; j++){
//         for(int i = 1; 1 <=2; i++){
//             if(isnan(transform[j][i]))
//                 return sf::Vector2f(transform[j][i],transform[j][i]);
//         }
//     }

//     Matrix<float> coord(2,1,0);
//     coord[1][1] = x;
//     coord[2][1] = y;

//     coord = transform * coord; 
//     return sf::Vector2f((coord[1][1]),coord[1][2]);
// }



sf::Vector2f winCord_to_polCords(sf::Vector2f winCord, Graph_info* info){
    return sf::Vector2f();
}

sf::Vector2f polCord_to_winCords(sf::Vector2f polCord, Graph_info* info){
    float rx, ry;

    rx = polCord.y * cos(polCord.x);
    ry = polCord.y * sin(polCord.x);

    return xyCord_to_winCords(sf::Vector2f(rx,ry),info);
}
