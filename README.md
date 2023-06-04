
# Work Report

## Name: <ins> ChungYin </ins>


<br><br>

# Graphing Calculator

## Demonstration
 
  - Buttons
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Buttons.gif)
 
  - Input
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Input.gif)

  - Panding
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Panding.gif)

  - Save and Loading old equation
  - 1
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Save_1st.png)
  - 2
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Save_2nd.png)
  - 3
![](https://github.com/barkeshli-CS003A-classroom/99_00_final_project-HiimOsu/blob/main/picture/Save_3rd.png)


## 2.02:
  - add:
    Now calculator would save/load equation from a txt file called "equation.txt"
  - Instructions:
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

  - ToDo: (descending)
  1. Exception handling of Input_Box;
  2. Add a way to change Polar Domain
  3. Linear Transfomation
  4. add button to : 
      2. Delete/Modify one of the history button
      3. Animation to button
  6. Clean up excess debug text
          
     
  - Ideas yet not implemented:
    3. Composite funcitons in rpn_sy: Create a functions class/ SetOf_Functions class to handle all user defined functions.



<details>
<summary>Description:</summary>
<p>

    a.
    
      This Graphing calculator will plot the graph on to the screen by creating hundreds of points
               |--------------------------|------|
               |                          |   S  |
               |     W O R K              |   I  |
               |                          |   D  |
               |         P A N E L        |   E  |
               |                          |      |
               |                          |   B  |
               |                          |   A  |
               |                          |   R  |
               |                          |      |
               |--------------------------|------|
     
         
    b. 

      This Program have 3 seperate part, a window, a side bar, and a Box.
               |--------------------------|------|
               |                          |   S  | 
               |     W O R K    P A N E L |   I  | 
               |    ~~~~~~~~~~~~~~~~~~    |   D  | 
               |    |                |    |   E  |  
               |    |                |    |      |  
               |    |                |    |   B  | 
               |    |      B O X     |    |   A  |
               |    ~~~~~~~~~~~~~~~~~~    |   R  | 
               |                          |      | 
               |--------------------------|------| 

      
     c. 

      In the design, the main system would holds all the objects: box, the window, and the side bar, the graph.
      The SideBar is lay on the Window, and the Work Panel is just the remaining space of the window,
      where the side bar does not cover.
               {  L E N G T H                    }
               |--------------------------|------| }
               |                          |      | }
               |     W O R K    P A N E L |      | } W
               |    ~~~~~~~~~~~~~~~~~~    |      | } I
               |    |                |    |      | } D
               |    |                |    |      | } T
               |    |                |    |      | } H
               |    |      B O X     |    |      | }
               |    ~~~~~~~~~~~~~~~~~~    |      | }
               |                          |      | }
               |--------------------------|------| }
    d.
    
      However, all the Box objects can only spawn on the work panel, and all the graph are plot inside the Box.
               {  L E N G T H                    }
               |--------------------------|------| }
               |                          |      | }
               |     W O R K    P A N E L |      | } W
               |    ~~~~~~~~~~~~~~~~~~    |      | } I
               |    |                |    |      | } D
               |    |                |    |      | } T
               |    |                |    |      | } H
               |    |      B O X     |    |      | }
               |    ~~~~~~~~~~~~~~~~~~    |      | }
               |                          |      | }
               |--------------------------|------| }

      Here is a routh Psuedocode of how the graph is plotted onto the screen:

          1.    System create a box object, and a graph object
          2.    Determine where is the box, and its bound.
          3.    Caculate the x-y coordinate of all of the points within the Domain X
          4.    Determine which points were laying outside the box
          5.    Plot the points.
            
  
</details>
  

## Phase 0:
  #### 0.01:
  - added folder:
      - shuntingYard_rpn, animate
  #### 0.02:
  - added folder:
    - graph:
      - adding stubs .h .cpp
    - translate_cords:
      - adding stubs .h .cpp
  #### 0.03:
  - Hard code 5 points in Plot Objects:
    -   Now program would draw 5 points on to the screen
    -   Screen: 600 x 600 
    -   Origin: middle of the WorkPan
    -   Points: origin, and 4 corners of the screen
    
  - added folder
  - include\Animate:
      - info
      - plot
      - graph
      
  #### 0.04
  - added:
    - implementation for graph_info class
    - test case for graph_info in TestB:
  - result:
  - | Default , 1 argument Constructors success
  - | get_postfix() succes;
  - | other functions not tested yet. 

  #### 0.05
  - added implementation:
    - +for translate_functions winCor_to_xyCords()
    - +Update() and Draw() in Plot class
    - +HardCode Input for _plotter
  - added Folder & Files:
    - axis (Folder)
        - | xy_axis.h
        - | xy_axis.cpp
  - new Feature:
      - +now running animate objects will plot the graph of y = x.
#### 0.06
  - added class:
    1. Axis
    2. Camera_info
  - Implemented Feature:
    - Now You can manually add graph into the system, by calling `system.add_graph(Graph_info*)` functions
    - But System would plot the first graph it dectected (The first graph be added)
    - To add a graph create a Graph_info object by calling 1 argument constructor `Graph_info(string equation)` 
    - To change the status of the camera and the graph, You can go to \includes\animate\constants.h

## Phase 1:
#### 1.01
  - Fixed Bug:
    1. Unary Operator is finished

#### 1.02
  - added Feature:
    - Key :
          1. +/- : zooming in/out
          2. arrow keys: panding camera up, down, left, right
          3. backspace: reset the graph 
    - Mouse:
          1. wheel: scroll up is zoom in, down is zoom out

#### 1.03:
  - Changes:
    1. Chaging from using std::vector to using myVectorClass
#### 1.04: 
  - Add:
    1. object folder: 
        - a class Box
        - b. class Button
        - c. class List_Button
    2.  History List, by clicking the option on the history change the graph to be plotted

#### 1.05:
   - Add:
      1. Object folder:
        1. Input Class
      2. Feature:
        1. Press Tab to: open input window, and user can type their grapgh (just the equation: no " y = ")
#### 1.06:
   - BugFixed:
      1. Input Box, HistoryList Position after resizing window
      2. Zooming in/out, Pend UpDownLeftRight
### 1.07:
   - Add Folder:
    1. Matrix
### 1.08:
  - Add:
    - added helping Menu(Press F1 to Enter, and Press F1/Esc to Leave);
    - added Polar Vision: Press 'p' to view the polar graph, as the variable in the equation turns into THETA;
### 2.00:
  - Add:
    - added 2 Buttons: helper button, polarMode
### 2.01:
  - Add:
    - added throw invalid input
<br><br>

