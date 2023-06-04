#include <iostream>
#include <fstream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include <cmath>
using namespace std;

#include "includes\animate\animate.h"
#include "includes\animate\graph\_info\graph_info.h"
#include "includes\shuntingYard_RPN\queue\MyQueue.h"
#include "includes\shuntingYard_RPN\token\token.h"
#include "includes\Matrix_Class\matrix\matrix.h"
#include "includes\Vector_class\vector\vector_class.h"
int main(int argc, char *argv[])
{  
  ifstream fin;
  ofstream fout;
  Vector<string> eq;
  string temp;
  char buff[50];
  animate game;
  fin.open("equation.txt");
  if(!fin.is_open()){
    assert(false && "Fail to read file from \"equation.txt\"");
  }

  while(!fin.eof()){//read equation from file
    fin.getline(buff,50,'\n');
    temp = buff;
    cout << "Loaded: " << temp << endl; 
    eq.push_back(temp);
  }
  fin.close();
  
  //import equations
  if(!eq.empty()){
    game.import_Equation(eq);
  }


  
  game.run();



  eq = game.export_StoredEquation();
  fout.open("equation.txt");
  if(!fout.is_open()){
    assert(false && "Fail to output to file\"equation.txt\"");
  }
  while(!eq.empty()){
    temp = eq.pop_back();
    fout << temp << endl;
  }


}


