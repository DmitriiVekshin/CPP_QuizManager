/*!
 \file declaration part of class CAinMenu
 */
#ifndef CMAINMENU_H
#define CMAINMENU_H
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <csignal>
#include <ncurses.h>
#include "CFrame.h"
#include "CCursor.h"
#include "CQuizMenu.h"
#include "CMenu.h"


#define HEADLIST "examples/quiz_head.bin"



/*!
	\brief general quiz info class 

    class represent head of quiz ( name and id)
*/
class  CQuizHead 
{   
    public:
                                            CQuizHead                                       ( int , std::string );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    SetName                                         ( std::string      & );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    SetID                                           ( int                );
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             GetName                                         ( void               ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    int                                     GetID                                           ( void               ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    

    private:
    std::string m_name;             /// quiz name
    int m_id;                       /// quiz ID
};





/*!
	\brief Child class for MainMenu

    class represent main menu, menu controller for choosing action
*/
class CMainMenu : public CMenu
{
    public:
                                            CMainMenu                                       ( void );
//-----------------------------------------------------------------------------------------------------------------------------                                            
                                            ~CMainMenu                                      ( void );
//-----------------------------------------------------------------------------------------------------------------------------                                            
    bool                                    CallQuizMenu                                    ( std::string & ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    DrawMenu                                        ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    DelMenu                                         ( void );    
//----------------------------------------------------------------------------------------------------------------------------- 
    std::string                             FillQuizName                                    ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    AddQuiz                                         ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    Run                                             ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    HeadlistInicialization                          ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    int                                     GetTopLabel                                     ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    SetTopLabel                                     ( int );
//-----------------------------------------------------------------------------------------------------------------------------
    int                                     GetBottomLabel                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    SetBottomLabel                                  ( int );
//-----------------------------------------------------------------------------------------------------------------------------
    std::string                             SetSizeQuiz                                     ( void );    
//-----------------------------------------------------------------------------------------------------------------------------

    
    private:
        int 
            m_nQuiz  ;
            
        

        std::vector < CQuizHead >       m_quizHead;                                                 /// all quiezzes
        const std::string m_mainMenuLabel               = "Add new quiz";                           /// program mesange
        const std::string m_NameErrorLabel              = "Name already exist";                     /// program mesange
        const std::string m_NewQuizLabel                = "Please write quiz name";                 /// program mesange
        const std::string m_NewQuizAmountQuestion       = "Please set amount of questions in quiz"; /// program mesange







        CFrame m_frame;                 /// quiz frame
        CCursor m_cursor;               /// quiz cursor
};
#endif
