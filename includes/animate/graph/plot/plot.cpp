#include "plot.h"
#include "../../constants.h"
#include "..\translate_cords\translate_cords.h"
#include "..\..\..\shuntingYard_RPN\rpn\rpn.h"
#include "..\..\..\shuntingYard_RPN\shunting_yard\shunting_yard.h"
#include "..\..\..\shuntingYard_RPN\token\tk_string.h"

Plot::Plot(Graph_info* graph_info){
    if(graph_info == nullptr){
        clear();
        return;
    }
    _graph_info = graph_info;
    Update(0);
}

void Plot::Draw(sf::RenderWindow& window){
    Vector<sf::CircleShape>::Iterator it = _lines.begin();
    while(it != _lines.end()){
        window.draw(*it++);
    }
}

void Plot::Update(bool is_polar){
    if(_graph_info == nullptr){
        return;
    }
    update_lines(is_polar);
}

void Plot::update_lines(bool is_polar){

    if(!_lines.empty()){
        _lines.clear();
    }

    Vector<sf::Vector2f> _points;
    Vector<sf::Vector2f>::Iterator points_it;
    sf::Vector2f winCord;
    sf::CircleShape temp(POINT_SIZE);
    sf::Vector2f domain;

    temp.setFillColor(POINT_COLOR);

    if(is_polar){
        domain =  _graph_info->get_PolarDomain();
        _points = compute_points(_graph_info->get_string_eq(), _graph_info->get_points(), domain);
        points_it = _points.begin();
        while(points_it != _points.end()){
            winCord = polCord_to_winCords(*points_it++, _graph_info);
            //Rejects if a point is outof bound 
            //eles push it into the line for later plotting 
            if(winCord != sf::Vector2f(-1,-1)){
                temp.setPosition(winCord);
                _lines.push_back(temp);
            } 
        }
    }
    else
    {
        domain =  _graph_info->get_domain();
        domain.x +=  _graph_info->get_camera_info()->_pan_camera.x;
        domain.y += _graph_info->get_camera_info()->_pan_camera.x;
        _points = compute_points(_graph_info->get_string_eq(), _graph_info->get_points(), domain);
        points_it = _points.begin();

        while(points_it != _points.end()){
            winCord = xyCord_to_winCords(*points_it++, _graph_info);
            //Rejects if a point is outof bound 
            //eles push it into the line for later plotting 
            if(winCord != sf::Vector2f(-1,-1)){
                temp.setPosition(winCord);
                _lines.push_back(temp);
            } 
        }
    }

    sf::Vector2f origin = xyCord_to_winCords(sf::Vector2f(0,0), _graph_info);
    temp.setRadius(5.f);
    temp.setOrigin(5/2.f, 5/2.f);
    temp.setPosition(origin);
    temp.setFillColor(sf::Color::Red);
    _lines.push_back(temp);

    origin = _graph_info->get_camera_info()->_camera_origin_onWind;
    temp.setRadius(5.f);
    temp.setOrigin(5/2.f, 5/2.f);
    temp.setPosition(origin);
    temp.setFillColor(sf::Color::Blue);
    _lines.push_back(temp);

}


void Plot::set_info(Graph_info* new_info){
    if(new_info == nullptr){
        clear();
    }
    _graph_info = new_info;
}

void Plot::clear(){
    if(!_lines.empty()){
        _lines.clear();
    }

    _graph_info = nullptr;
}

Graph_info* Plot::get_info(){
    return _graph_info;
}

Vector<sf::Vector2f> compute_points(string equation, int num_point, sf::Vector2f domain){               //get vector of points
    const bool debug = false;
    Vector<sf::Vector2f> _points;
    _points.set_min_capacity(num_point);

    Tk_String tokenizer(equation);  //get infix token
    ShuntingYard sy(tokenizer.getQueue_Token());        //get postfix token
    Queue<Token*> post_fix = sy.postfix();              
    RPN rpn(post_fix);                                  //create rpn object


    double delta_x = (domain.y - domain.x)/ num_point;  // get Delta X

    
    double points_x = domain.x ;                        //  get first (x,y)

    double points_y = rpn(points_x);

    sf::Vector2f coordinate(points_x , points_y );
    
    
    for(int i = 0; i < num_point;i++){
        _points.push_back(coordinate);
        points_x =  points_x + delta_x;                                             // Xn = X(n-1) + Delta_x
        points_y = rpn(points_x);
        if(debug){
            cout << "Debug: rpn(" << points_x << "): "  << rpn (points_x) << endl;
            cout << "Debug: y = " << points_y;
        }
        coordinate = sf::Vector2f(points_x , points_y);
    }

    //clean token*
    Queue<Token*>::Iterator it = post_fix.begin();
    while (it != post_fix.end())
    {
        delete *it;
        it++;
    }
    
    return _points;
}