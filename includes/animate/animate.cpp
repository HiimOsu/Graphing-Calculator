#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

#include "animate.h"
#include "constants.h"
#include "system.h"

animate::animate():sidebar(WORK_PANEL, SIDE_BAR), history_list(sf::Vector2f(SIDE_BAR, SCREEN_HEIGHT *4/5))
{
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graping Calculator");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    system = System();
    window.setFramerateLimit(60);

    mouseIn = true;




    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout<<"Geme CTOR. preparing to load the font."<<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }


    //---ListButton-----------
    history_list.setLabel_String("History List");
    history_list.setFont(&font);
    history_list.setPosition(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT * 1/5));
    

    //---_graph_vector




    system.set_graph(nullptr);

    //---_button...
        //PolarMode
        _button_polarMode = initButton_polarMode(window.getSize());
        _button_polarMode.set_Outline_Color(sf::Color::Red);
        _button_polarMode.set_Font(&font);
        //HelperMenu
        _button_helperMenu = initButton_helperMenu(window.getSize());
        _button_helperMenu.set_Font(&font);
    //---Debug Log-----------
    // cout << "_graph_vector info: " << endl;
    // cout << "   Capacity: " << _graph_vector.capacity() << endl;
    // cout << "   Size: " << _graph_vector.size() << endl;
    // for(Vector<Graph_info*>::Iterator it = _graph_vector.begin();
    //     it != _graph_vector.end(); it++)
    // {
    //     cout << "New Graph added: " << (*it)->get_string_eq() << endl;
    // }

    // cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    sidebar.draw(window); 
    _button_polarMode.Draw(window);
    _button_helperMenu.Draw(window);
    history_list.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);

    }

    
    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    // window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command);
    command = 0;
    if (mouseIn){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                               sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        if(system.get_GraphInfo() != nullptr){

            sf::Vector2f winCoord = sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
            sf::Vector2f XYCoord = system.getXY(winCoord);

            sidebar[SB_MOUSE_POSITION] = "(x,y) = (" + roundTo_String(XYCoord.x,3) + ", "+ roundTo_String(XYCoord.y,3) + ")";
        }else
        {
            sidebar[SB_MOUSE_POSITION] = "(x,y) = ?";
        }

    }

    if(system.is_polar()){
        _button_polarMode.set_Outline_Color(sf::Color::Green);
    }else{
        _button_polarMode.set_Outline_Color(sf::Color::Red);
    }

}

void animate::render(){
    window.clear();
    Draw();
    window.display();
    elapsed1 = clock.getElapsedTime();
}



void animate::processEvents()
{
   sf::Event event;
   float mouseX, mouseY;
   string input;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
            case sf::Event::Resized:
                    resizeWidnow(event);
                    command = COMMAND_RESIZE_WINDOW;
                break;  
           // window closed
           case sf::Event::Closed:
               window.close();
               break;
            // key released
           case sf::Event::KeyReleased:
                command = getCommand_EventPanding(event);
                break;
           // key pressed
           case sf::Event::KeyPressed:
               command = getCommand_EventPanding(event);
               if(command == 0)
                    switch(event.key.code){
                    case sf::Keyboard::Escape:
                        sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                        window.close();
                        break;
                    case sf::Keyboard::Add:
                    case sf::Keyboard::Z:
                        command = COMMAND_GRAPH_ZOOM_IN;
                        break;
                    case sf::Keyboard::Subtract:
                    case sf::Keyboard::X:
                        command = COMMAND_GRAPH_ZOOM_OUT;
                        break;
                    case sf::Keyboard::Backspace:
                        command = COMMAND_RESET_CAMERA;
                        break;
                    case sf::Keyboard::Tab:
                        input = get_Input();
                        if(input != ""){
                            add_Graph(input);
                        }
                        break;
                    case sf::Keyboard::P:
                        command = COMMAND_GRAPH_TOGGLE_PLOTPOLAR;
                        break;
                    case sf::Keyboard::F1:
                        help_menu();
                        break;
                    case sf::Keyboard::PageUp:
                        history_list.scrollUp();        //Update history list
                            break;
                    case sf::Keyboard::PageDown:
                        history_list.scrollDown();      //Update history list
                    }
               
               break;
           case sf::Event::MouseEntered:
               mouseIn = true;
               break;

           case sf::Event::MouseLeft:
               mouseIn = false;
               break;
           case sf::Event::MouseWheelMoved:
                    if(event.mouseWheel.delta < 0){
                        command = COMMAND_GRAPH_ZOOM_OUT;
                    }else{
                        command = COMMAND_GRAPH_ZOOM_IN;
                    }
                
           case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                //Do something with it if you need to...
               break;
           case sf::Event::MouseButtonReleased:
                   if (event.mouseButton.button == sf::Mouse::Left)
                   {
                        sf::Vector2f mouse_pos(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                        
                        if(_button_polarMode.is_Inside(mouse_pos)){
                            command = COMMAND_GRAPH_TOGGLE_PLOTPOLAR;
                        }else if(_button_helperMenu.is_Inside(mouse_pos)){
                            help_menu();
                        }            
                        else{
                            int on_HistList = history_list.isOnTheList(mouse_pos);      //return the index of list,  if mouse clicked on the list
                            Graph_info* _info = get_GInfo_from_GHistoryList(on_HistList);
                            if(_info != nullptr){
                                system.set_graph(_info);
                                command = COMMAND_GRAPH_REFRESH;
                            }    
                        } 
                   }
                   break;

               default:
                   break;
           }
       }
}

void animate::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
   cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}





//Control the clicking event on History List
Graph_info* animate::get_GInfo_from_GHistoryList(int index){
    Graph_info* return_me = nullptr;
    if(index != -1 ){
        if(index != 0 ){
            return_me = (*_graph_vector.at(index -1));
        } else{ 
            history_list.HideShow_List();
        }
    }

    return return_me;
}

//Responsible for adding graph
void animate::add_Graph(string equation){//Max Graph 20
    Graph_info* new_info = new Graph_info(equation);
    
    if(_graph_vector.size() == 20){
        Graph_info* delete_me   = _graph_vector.pop_back();
        delete delete_me;
    }
    
    _graph_vector.insert(0, new_info);

    history_list.removeAllButton();
    for(Vector<Graph_info*>::Iterator it = _graph_vector.begin();
        it != _graph_vector.end(); it++)
    {
        history_list.addButton((*it)->get_string_eq());
    }

    history_list.setLabel_FillColor(sf::Color::Black);
    history_list.setLabel_OutlineColor(sf::Color::Green);
    history_list.setList_FillColor(sf::Color::Black);
    history_list.setList_OutlineColor(sf::Color::Green);
}

//Responsible for running the input page
string animate::get_Input(){//Open a input Box on the Window, halt when user press enter and return string 
    clock.restart();
    sf::Time elapsed2 = clock.getElapsedTime();
    string rt_me, errorPart = "";
    Input_box inBox = initbox(window.getSize());
    Button error_msg("Hi Please Enter the equation directly, for example: x + 1", window.getSize().x * 4 /5, window.getSize().y * 1/ 5, sf::Color::Black, sf::Color::Green);



    inBox.set_font(&font);
    error_msg.set_Position(sf::Vector2f(window.getSize().x * 1/10, window.getSize().y * 1/10 + window.getSize().y * 1/ 5 + 20));
    error_msg.set_Font(&font);
    

    sf::Event event;
    while(inBox.is_open())
    {
        elapsed1 = clock.getElapsedTime();
        
        if(window.pollEvent(event)){
            switch (event.type)
            {
            case sf::Event::Resized:
                resizeWidnow(event);
                command = COMMAND_RESIZE_WINDOW;                                                    //command = resizing window
                update();                                                                           //Taking the command, sidebar, system, and member in system would update its state

                inBox.set_size(event.size.width * 4 /5, event.size.height * 1/ 5);                  //Setting the new size and position for input_Box
                inBox.set_position(sf::Vector2f(event.size.width * 1/10, event.size.height * 1/10));
                error_msg.set_Size(sf::Vector2f( window.getSize().x * 4 /5, window.getSize().y * 1/ 5));
                error_msg.set_Position(sf::Vector2f(event.size.width * 1/10, event.size.height * 1/10 + window.getSize().y * 1/ 5 + 20));
                break;
            case sf::Event::Closed:
                window.close();
                return "";
                break;

            case sf::Event::KeyPressed:
                switch(event.key.code){
                case sf::Keyboard::Delete:
                    inBox.clearInput();
                    break;
                case sf::Keyboard::Tab:
                    if(elapsed1.asMilliseconds() < 50){//Guarding
                        break;
                    }
                case sf::Keyboard::Escape:
                    return "";
                case sf::Keyboard::Enter:   
                    rt_me = inBox.getInput();
                    int type = try_userInput(rt_me, errorPart);
                    switch (type)
                    {
                    case 0:
                        inBox.close();
                        break;
                    case 1:
                        error_msg.set_String("[Error]: Empty input is not allow! Press Tab/Esc again could close the input window");
                        break;
                    case 2:
                        if(errorPart == ""){
                            error_msg.set_String("[Error]: Missing Operands! Forget variable/number at the end?");
                        }
                        else{
                            error_msg.set_String("[Error]: Missing Operands! Forget variable/number after: \"" + errorPart + "\" ?");
                        }
                        break;
                    case 3:
                        if(errorPart == ""){
                            error_msg.set_String("[Error]: Missing Operator! Forget operator/functions at the end?");
                        }
                        else{
                            error_msg.set_String("[Error]: Missing Operator! Forget operator/functions after: \"" + errorPart + "\"  ?");
                        }
                        break;
                    }
                    errorPart = "";
                }
                break;
            case sf::Event::TextEntered:
                    inBox.input(event);
                break;
            }

        }
            // cout << "E1: " << elapsed1.asMilliseconds() << "ms E2: " << elapsed2.asMilliseconds() << "ms" << endl;
        
        
        if((elapsed1 - elapsed2).asMilliseconds() > 500){
            elapsed2 = elapsed1;
            inBox.hideShow_underScore();
        }

        window.clear();
        Draw();
        inBox.Draw(window);
        error_msg.Draw(window);
        window.display();
    }
    StrToken strTk(rt_me);

    rt_me = "";
    while(!strTk.is_empty()){
        rt_me += strTk.get_token() + " ";
    }
    return rt_me;
}

//Responsible for running the helpMenu page
void animate::help_menu(){
    clock.restart();
    bool is_open = true;

    Button button_close("X", 80,80, sf::Color(36, 34, 34), sf::Color(158, 6, 49));
    Help_menu help_menu = init_helpMenu(window.getSize().x, window.getSize().y, &font);
    
    button_close.set_Position(sf::Vector2f(window.getSize().x - 80, 0));
    button_close.set_Font(&font);
    button_close.set_TextColor(sf::Color(233, 245, 2));
    button_close.set_OutLineThikness(3.f);
    //Draw the first time
    window.clear();
    help_menu.Draw(window);
    button_close.Draw(window);
    window.display();
    sf::Event event;


    while(is_open){
        if(window.pollEvent(event)){
            elapsed1 = clock.getElapsedTime();
            if(event.type == event.KeyReleased){
                if(elapsed1.asMilliseconds() > 400){//Guarding
                    if(event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::Escape){
                        is_open = false;
                    }
                }
            }else if(event.type == event.Resized){            
                resizeWidnow(event);
                command = COMMAND_RESIZE_WINDOW;
                
                help_menu = init_helpMenu(event.size.width, event.size.height, &font);
                button_close.set_Position(sf::Vector2f(window.getSize().x - 80, 0));

                window.clear();
                help_menu.Draw(window);
                button_close.Draw(window);
                window.display();

            }else if(event.type == event.Closed){
                window.close();
                is_open = false;
            }else if(event.type == event.MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2f mouse_pos(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                    if(button_close.is_Inside(mouse_pos)){
                        is_open = false;
                    }
                    
                }
            }
        }
    }
}

//Control the toggles base on event And Return the command base on toggle
int animate::getCommand_EventPanding(sf::Event event){
    int command = 0;
    switch (event.type)
    {
    case event.KeyPressed:
        switch(event.key.code){
        case sf::Keyboard::Up:
            _up = true;
            break;
        case sf::Keyboard::Down:
           _down = true;
           break;
        case sf::Keyboard::Left:
            _left = true;
            break;
        case sf::Keyboard::Right:
            _right = true;
        }
        break;
    case event.KeyReleased:
        switch(event.key.code){
        case sf::Keyboard::Up:
            _up = false;
            break;
        case sf::Keyboard::Down:
           _down = false;
           break;
        case sf::Keyboard::Left:
            _left = false;
            break;
        case sf::Keyboard::Right:
            _right = false;
        }
        break;
    }

    if((_up && _down) || (!_up && !_down)){
        if((!_left && !_right) || ( _left && _right)){
            command = 0;
        }
        else if(_left && !_right){
            command = COMMAND_GRAPH_PAN_LEFT;
        }
        else if(!_left && _right){
            command = COMMAND_GRAPH_PAN_RIGHT;
        }
    }
    else if(_up && !_down){
        if((!_left && !_right) || ( _left && _right)){
            command = COMMAND_GRAPH_PAN_UP;
        }
        else if(_left && !_right){
            command = COMMAND_GRAPH_PAN_UP_LEFT;
        }
        else if(!_left && _right){
            command = COMMAND_GRAPH_PAN_UP_RIGHT;
        }
    }
    else if(!_up && _down){
        if((!_left && !_right) || ( _left && _right)){
            command = COMMAND_GRAPH_PAN_DOWN;
        }
        else if(_left && !_right){
            command = COMMAND_GRAPH_PAN_DOWN_LEFT;
        }
        else if(!_left && _right){
            command = COMMAND_GRAPH_PAN_DOWN_RIGHT;
        }
    }

    return command;
}

//Update all inform when resizing window
void animate::resizeWidnow(sf::Event event){
    window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    sidebar.setSize(event.size.width * 4/5, event.size.width * 1/5,event.size.height);
    system.get_camera_info()->set_NewWindow(event.size.width, event.size.height);
    history_list.setSize(sf::Vector2f(event.size.width * 1/5, event.size.height * 4/5));              
    history_list.setPosition(sf::Vector2f(event.size.width * 4/5, event.size.height * 1/5));
    _button_polarMode = initButton_polarMode(window.getSize());
    _button_polarMode.set_Font(&font);
    _button_helperMenu = initButton_helperMenu(window.getSize());
    _button_helperMenu.set_Font(&font);
}


Vector<string> animate::export_StoredEquation(){
    Vector<string> rtme;

    for(Vector<Graph_info*>::Iterator it = _graph_vector.begin();
    it != _graph_vector.end(); it++){
        rtme.push_back((*it)->get_string_eq());
    }

    return rtme;
}
void  animate::import_Equation(Vector<string> eq){
    int type = 1;
    string temp;
    for(Vector<string>::Iterator it = eq.begin();
    it != eq.end(); it++){
        
        type = try_userInput(*it,temp);
        if(type != 0){
            cout << "Animate::[Error]:Failing to import equation:" << *it << endl;
        }else {
            add_Graph(*it);
        }
    }

}

Input_box initbox(sf::Vector2u window_size){
    Input_box inBox;
    inBox.Open(window_size.x * 4 /5, window_size.y * 1/ 5, sf::Color::Black, sf::Color::Green);
    
    sf::Text text;
    text.setColor(sf::Color::Green);

    if(window_size.x > SCREEN_WIDTH * 3/2 && window_size.y > SCREEN_HEIGHT * 3/2){
        text.setCharacterSize(64);   
    }else text.setCharacterSize(32);
    inBox.set_text(text);
    inBox.set_position(sf::Vector2f(window_size.x * 1/10, window_size.y * 1/ 10));
    
    return inBox;
}

Help_menu init_helpMenu(float width, float height, sf::Font* font_ptr){
    Help_menu help_menu(width, height);
    help_menu.setFont(font_ptr);
/*
    - Key :
    - Key :
          1. (+/-) or (,/.) : zooming in/out
          2. arrow keys: panding camera up, down, left, right
          3. backspace: reset the graph 
          4. Tab: Open input window
          5. F1: Open Guide
          6. p: Turn on/off Polar mode
          7. Esc: Exit Program
    - Mouse:
          1. wheel: scroll up is zoom in, down is zoom out
    - Buttons:
          1. History List: open/close the history list
          2. ?: open instruction menu
          3. PolarMode: plot polar version of the equation
*/
    help_menu.addText("Press F1/Esc to close Help Menu");
    help_menu.addText("Keys:");
    help_menu.addText(" 1. (+/-) or (z/x) : zooming in/out");
    help_menu.addText(" 2. arrow keys: panding camera up, down, left, right");
    help_menu.addText(" 3. backspace: Reset Graphs");
    help_menu.addText(" 5. P/p: Turn on/off Polar mode");
    help_menu.addText(" 6. F1: Open Guide");
    help_menu.addText(" 7. Esc: Exit Program");

    help_menu.addText("Mouse:");
    help_menu.addText(" 1. wheel scroll up/down: zoom in/out");
    help_menu.addText("Buttons:");
    help_menu.addText(" 1. History List: click on label to open/close the history list");
    help_menu.addText(" 2. PolarMode: plot polar version of the equation");
    help_menu.addText(" 3. ?: open instruction menu");
    
    return help_menu;
}

Button initButton_polarMode(sf::Vector2u window_size){
    Button p("Polar", window_size.x * 1/15, window_size.x * 1/15);
    p.add_string("Mode");
    p.set_Fill_Color(sf::Color(168,100,50));
    p.set_TextColor(sf::Color::Yellow);
    p.set_Position(sf::Vector2f(window_size.x  * 4/5, window_size.y * 1/5 - window_size.x * 1/15));


    return p;
}

Button initButton_helperMenu(sf::Vector2u window_size){
    Button h("?", window_size.y * 1/25, 
    window_size.y * 1/25);

    h.set_Fill_Color(sf::Color(36, 34, 34));
    h.set_Outline_Color(sf::Color(1, 133, 39));
    h.set_OutLineThikness(3.f);
    h.set_TextColor(sf::Color(233, 245, 2));
    h.set_Position(sf::Vector2f(window_size.x  -(window_size.y * 1/50) , 0));
    return  h;
}   

float roundTo(float num, int digit){
    assert(digit > 0);
    float Rnumber = round(num * pow(10, digit));
    Rnumber = Rnumber / pow(10, digit);

    return Rnumber;
}

string roundTo_String(float num, int digit){
    num = roundTo(num, digit);

    string str = to_string(num), ret_me;
    string::iterator it;
    for(it = str.begin(); *it != '.'; it++){
        ret_me += *it;
    }
    for(int i = 0; i <= digit; i++, it++){
        ret_me += *it;
    }
    return ret_me;
}

int try_userInput(string str, string& part)
{   
    //rtme = 
    //      1. Empty
    //      2. Missing Operands
    //      3. Missing Operators
    int rtme = 0;
    Queue<Token*> qTK, infix;
    Tk_String tokenizer(str);
    try{
        qTK = tokenizer.getQueue_Token();
    }
    catch(Exception_MissingOperands e){
        if(e._ptr != nullptr){
            // part += (*e._ptr).str_tok();
        }
        rtme = 2;
        while(!qTK.empty()){
            delete qTK.pop();
        }
        return rtme;
    }
    catch(Exception_MissingOperator e){
        if(e._ptr != nullptr){
            // part += (*e._ptr).str_tok();
        }
        rtme = 3;
        while(!qTK.empty()){
            delete qTK.pop();
        }
        return rtme;
    }
    infix = qTK;
    ShuntingYard sy(qTK);
    qTK = sy.postfix();

    RPN rpn(qTK);

    try{
        rpn(0);
    }
    catch(Exception_EmptyExpression e){
        rtme = 1;
    }
    catch(Exception_MissingOperands e){
        Queue<Token*>::Iterator it = infix.begin();
        while(it != infix.end() && *it != e._ptr){
            it++;
        }

        for(;it != infix.end(); it++){
            part += (*it)->str_tok();
        }
        rtme = 2;
    }
    catch(Exception_MissingOperator e){
        Queue<Token*>::Iterator it = infix.begin();
        while(it != infix.end() && *it != e._ptr ){
            it++;
        }

        for(;it != infix.end(); it++){
            part += (*it)->str_tok();
        }
        rtme = 3;
    }

    while(!qTK.empty()){
        delete qTK.pop();
    }

    return rtme;
}

// Graph_info* animate::get_GraphInfo(int index){
//     assert(index >= 0 && "ERROR [get_Graph_info]: index must be positive");
//     assert(index < _graph_vector.size() && "ERROR [get_Graph_info]: index is out of bound, please add entry/ or reduce the index");
//     return _graph_vector[index];
// }