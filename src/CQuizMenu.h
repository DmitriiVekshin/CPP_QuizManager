/*!
 \file declaration part of class CQuizMenu
 */
#ifndef CQUIZMENU_H
#define CQUIZMENU_H
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <ncurses.h>
#include "CMenu.h"
#include "CFrame.h"
#include "CCursor.h"
#include "CQuiz.h"


/*!
	\brief Child class for quiz menu

    class represent quiz menu, quiz controller for choosing action, generation quizzes
*/
class CQuizMenu : public CMenu
{
    public:
                                            CQuizMenu                                       ( std::string & );
//-----------------------------------------------------------------------------------------------------------------------------                                            
    void                                    AddQuestion                                     ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    AddQuestionFromFile                             ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    PrintRule                                       ( void ) const;    
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    DelQuiz                                         ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    DrawMenu                                        ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    Run                                             ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    DelMenu                                         ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    bool                                    Inicialisation                                  ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    CQuiz                                   GeneratQuiz                                     ( bool ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    StartQuiz                                       ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    PrintQuiz                                       ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    ViewQuiz                                        ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    LogIn                                           ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    bool                                    GetDeleteState                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    LoginRequester                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    BadFailMessage                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------

    private:
    int 
        m_AmoutQustions     ,  /// amout of questions into quiz instance
        m_id                ;  /// quiz id
    std::string 
        m_password          ,  /// quiz password
        m_quizName          ;  /// quiz name
    bool isLogin;              /// flag detected quiz administrator
    bool toDelte;              /// flag for deleting


    CFrame m_frame;            /// menu frame
    CCursor m_cursor;          /// menu cursor

    std::vector < std::string > m_label                                 /// program mesanges
    {           
                                            "Start"                   ,
                                            "Create question"         ,
                                            "Add question from file"  ,
                                            "Delete quiz"             ,
                                            "View quiz"               ,   
                                            "Print quiz"              ,
                                            "Login"          
                                                             };
    const std::string m_InicialErrorLabel              = "Bad quiz fail";                   /// program mesange
    const std::string m_badPassword                    = "Bad quiz password";               /// program mesange
    const std::string m_addQuestion                    = "Please write your question";      /// program mesange
    const std::string m_addQuestionFail                = "Please write fail name";          /// program mesange
    const std::string m_addAnswer                      = "Please write answer";             /// program mesange
    const std::string m_logoutError                    = "You need login for change quiz";  /// program mesange
    const std::string m_failError                      = "Quiz fail is invalid";            /// program mesange

    
    std::vector < std::string > m_rule                                                      /// add question rules
    {
                                                "Answer can be a single word"                                ,
                                                "Answer can be a single number"                              ,
                                                "Answer can be a several word, corrects must have suffix '!'",
                                                "example: FIT! FEL FA FD"
    };
    const std::string m_quizProgrammName;                                                   /// quiz name in program
    

    
};

#endif