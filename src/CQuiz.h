/*!
 \file declaration part of class CQuiz
 */
#ifndef CQUIZ_H
#define CQUIZ_H
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "CComand.cpp"
#include "CCursor.h"
#include "CQuestion.h"
#include "CFrame.h"


/*!
	\brief quiz class

    class represent quiz 
*/
class CQuiz
{
    public:
                                            CQuiz                                           ( int );
//-----------------------------------------------------------------------------------------------------------------------------
                                            ~CQuiz                                          ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    AddTask                                         ( const std::string &   ,
                                                                                                    std::string &   );
//-----------------------------------------------------------------------------------------------------------------------------
    void                                    DrawPage                                        ( int );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    DelPage                                         ( int );    
//-----------------------------------------------------------------------------------------------------------------------------
    MenuCommand                             ChooseAction                                    ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    Run                                             ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    MakeTxtFile                                     ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    ShowResult                                      ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    AnswerInicial                                   ( void );
//-----------------------------------------------------------------------------------------------------------------------------    
    void                                    Clean                                           ( void );
//-----------------------------------------------------------------------------------------------------------------------------
    private:
        std::vector  < std::vector  < CQuestion *  > >  m_pages;       /// pages into quiz
        std::vector  < std::vector  < std::string  > >  m_userAnswers; /// users answers
        std::vector < int > affordableCursorPos;                       /// cursors positions
        int m_pageSize      ,
            m_height        ,
            m_width         ,
            m_bottomQuestion,
            m_topQuestion   ,
            m_actualPage    ,
            m_actualCursorPosition;
    
    const std::string m_finalLabe                      = "Congratulations your score : "; /// program mesage
        
};

#endif