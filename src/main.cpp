/*!
  \main.cpp
  \author Dmitrii Vekshin (vekshdmi)
  \version 1.0
  \date May 2018
  
  \section info_sec General info
  Welcom to Easy-quizy - simple and 	
  handy quizzes manger. That program can help
  with creat, manage and run your quizzes
  For further information read "zadani.txt". 
  
  \section controls_sec quiz control
  Back - esc
  Choose option - enter
  Up, Down, Right, Left
  Delete char - backspace 
 */

#include "CMainMenu.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdint>
#include <ncurses.h>



/*!
 *   \brief main function of project
 *   initialisation of keypad,
 *   delay for pres keys,
 *   console writing 
*/
int main(int argc, char **argv)
{
    

    initscr();
    nodelay(stdscr,true);   
    keypad(stdscr,true);    
    noecho();               
    curs_set(0);                         

        CMainMenu m_menu       ;
        m_menu.Run()           ;
                         
    endwin();

    return 0;
}
