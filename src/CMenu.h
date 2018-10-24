/*!
 \file declaration part of class CMenu
 */
#ifndef CMENU_H
#define CMENU_H
#include <string>
#include <vector>
#include <fstream>
#include <ncurses.h>
#include "CComand.cpp"



/*!
	\brief Parent class for menus

	that class manage hashing, reed from consolem, print into file, prepares commands by pressed keys
*/
class CMenu
{
    public:
//-----------------------------------------------------------------------------------------------------------------------------    
    CMenu (){}
//-----------------------------------------------------------------------------------------------------------------------------    
    ~CMenu (){}
//-----------------------------------------------------------------------------------------------------------------------------    
    virtual     void                        DrawMenu                                        ( void ) = 0;
//-----------------------------------------------------------------------------------------------------------------------------      
    virtual     void                        DelMenu                                         ( void ) = 0;
//-----------------------------------------------------------------------------------------------------------------------------     
    std::string                             GoHash                                          ( std::string & ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    bool                                    FilePrint                                       ( std::string &, std::ofstream & ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    MenuCommand                             ChooseAction                                    ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             ScanLabel                                       ( int , int, int, bool );
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             FillPassword                                    ( void );
//-----------------------------------------------------------------------------------------------------------------------------    

    protected:
        int
            m_width             , /// width of window 
            m_height            , /// height of window
            m_menuSize          , /// value of labels in item
            m_isSelected        , /// selected item
            m_topLabel          , /// top labels in window
            m_bottomLabel       ; /// bottom label in window

            const std::string m_QuizPassword             = "Please write quiz password"; /// message to user

};
#endif