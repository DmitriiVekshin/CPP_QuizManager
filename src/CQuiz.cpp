/*!
 \file implementation part of class CQuiz
 */
#include "CQuiz.h"
#include <ncurses.h>

//=============================================================================================================================
/*!
    constructor
*/
                                            CQuiz::CQuiz                                    ( int pageSize )
                                            {
                                                m_actualPage = 0;
                                                m_pageSize = pageSize;
                                                m_bottomQuestion = 0 ;
                                                m_actualCursorPosition = 0 ;
                                                m_topQuestion  = 0    ;

                                                affordableCursorPos.resize (pageSize);

                                                getmaxyx(stdscr, m_height, m_width);

                                            }
//=============================================================================================================================
/*!
    destructor
*/
                                            CQuiz::~CQuiz                                   ( void )
                                            {
                                                Clean();
                                            }
//=============================================================================================================================
/*!
    Add question into quiz instance
    \param strings question and aswer
*/
    void                                    CQuiz::AddTask                                  ( const std::string & quaere  ,
                                                                                                    std::string & answer  )
    {
        std::string tmpAnswer = "";
        std::string tmpRightAnswer = "";
        std::vector < std::string > m_answers;
        int wordsInAswer=0;
        bool charType = false;
        for( int i = 0; i < (int)answer.size(); i++)
        {
            if( answer[i] < 48 || answer[i] > 57)
                charType = true;
            if( answer[i] == 32 )
            {
                if( answer[i-1] == 33 )
                {
                    tmpAnswer.pop_back();
                    tmpRightAnswer += (char)(97 + wordsInAswer);
                }
            m_answers.push_back( tmpAnswer );
            tmpAnswer = "";
            wordsInAswer++;    
            }
            else
                tmpAnswer += answer[i];

        }

        m_answers.push_back( tmpAnswer );
        
    if( !charType )
    {
        int numbericAnswer = 0;
        for ( int i = 0; i < (int)tmpAnswer.size(); i++)
            {
                numbericAnswer *= 10;
                numbericAnswer += tmpAnswer[i];
                numbericAnswer -= 48;              

            }
        CQuestionTypeTwo newQuestion ( quaere, numbericAnswer );
        if( (int)m_pages.size() == 0 || (int)m_pages.back().size() == m_pageSize )
            m_pages.emplace_back();   
        m_pages.back().push_back( newQuestion.Clone());
            }
    else
    {
        if( m_answers.size() == 1)
        {

            CQuestionTypeOne newQuestion ( quaere, m_answers[0] );

        if( (int)m_pages.size() == 0 || (int)m_pages.back().size() == m_pageSize )
            m_pages.emplace_back();   
        m_pages.back().push_back( newQuestion.Clone());
        }
        else
        {
            CQuestionTypeThree newQuestion ( quaere, tmpRightAnswer, m_answers );
                if( (int)m_pages.size() == 0 || (int)m_pages.back().size() == m_pageSize )
            m_pages.emplace_back();   
        m_pages.back().push_back( newQuestion.Clone());
        }
    }
        
    }
//=============================================================================================================================
/*!
    Draw page
    \param int page number
*/
    void                                    CQuiz::DrawPage                                 ( int pageNumber )
    {
        std::vector < std::string > allQuestionOnPage;
        int questionID = 0;
            for( auto question : m_pages[pageNumber] )
            {
                std::string quaere = std::to_string(questionID) +  ") " + (*question).printQuestion();
                allQuestionOnPage.push_back( quaere );
                questionID ++;    
            }
        refresh();        
        getmaxyx(stdscr, m_height, m_width);
        int y = m_height/20 + 4 ,
            x = m_width / 20 + 4;
        for( int i = m_topQuestion; i < (int)allQuestionOnPage.size(); i++ )
        {
            move( y, x);
            for( int l = 0; l < (int)allQuestionOnPage[i].size(); l++ )
            {
                move( y, x);
                if( allQuestionOnPage[i][l] == 10 )
                {
                     y++;
                     x = m_width / 20 + 4;
                }   
                else    
                {
                    addch( allQuestionOnPage[i][l]);
                    refresh();
                    x++;
                }
            }
            affordableCursorPos[i] = (y + 1);
            y+=3;
            x = m_width / 20 + 4;
            m_bottomQuestion = i;
            if( y + 4  >= m_height ) 
                break;

        }
        move(affordableCursorPos[m_actualCursorPosition], m_width/20 + 2 );
        addch ( 62 );
        refresh();
        
    }
//=============================================================================================================================
/*!
    delete page ( visual )
    \param int number of page
*/
    void                                    CQuiz::DelPage                                  ( int pageNumber )
    {
        std::vector < std::string > allQuestionOnPage;
        int questionID = 0;
            for( auto question : m_pages[pageNumber] )
            {
                std::string quaere = std::to_string(questionID) +  ") " + (*question).printQuestion();
                allQuestionOnPage.push_back( quaere );
                questionID ++;    
            }
        
        int y = m_height/20 + 4 ,
            x = m_width / 20 + 4;
        for( int i = m_topQuestion; i < (int)allQuestionOnPage.size(); i++ )
        {
            move( y, x);
            for( int l = 0; l < (int)allQuestionOnPage[i].size(); l++ )
            {
                move( y, x);
                if( allQuestionOnPage[i][l] == 10 )
                {
                     addch( 32 );
                     y++;
                     x = m_width / 20 + 4;
                }   
                else    
                {
                    addch( 32 );
                    refresh();
                    x++;
                }
            }
            y+=3;
            x = m_width / 20 + 4;
        if( y + 4  >= m_height ) 
                break;    
        }
        move(affordableCursorPos[m_actualCursorPosition], m_width/20 + 2 );
        addch ( 32 );
        refresh();
    }
//=============================================================================================================================
/*!
    Catch user action and implement them
	\return next command
*/
    MenuCommand                             CQuiz::ChooseAction                             ( void )
    {
        MenuCommand command;
        nodelay(stdscr,false);
            
                    int inputChar = getch();
                    switch (inputChar)
                    {
                    case KEY_UP     :
                        if( m_actualCursorPosition > m_topQuestion )
                            {
                            DelPage( m_actualPage ) ;
                            m_actualCursorPosition--;
                            command = MenuCommand::Up;
                            }
                        else if ( m_actualCursorPosition == m_topQuestion && m_topQuestion > 0)
                            {
                            DelPage(m_actualPage);
                            m_topQuestion --;
                            m_bottomQuestion --;
                            command = MenuCommand::Down;
                            }
                        else   
                            command = MenuCommand::MissClick;
                                                                                break;
                    case KEY_DOWN   :  
                        if( m_actualCursorPosition < m_bottomQuestion )
                            {
                            DelPage(m_actualPage);                                
                            m_actualCursorPosition++;
                            command = MenuCommand::Down;
                            }
                        else if ( m_actualCursorPosition == m_bottomQuestion && m_bottomQuestion < (int)m_pages[m_actualPage].size()-1)
                            {
                            DelPage(m_actualPage);                                
                            m_topQuestion ++;
                            m_bottomQuestion ++;
                            command = MenuCommand::Up;
                                    
                            }
                        else   
                            command = MenuCommand::MissClick;
                                                                            break;
                    case KEY_LEFT   :  
                        if( m_actualPage > 0 )
                        {
                            DelPage(m_actualPage);                            
                            m_actualPage--;
                            m_bottomQuestion = 0 ;
                            m_topQuestion  = 0 ;
                            m_actualCursorPosition = 0 ;
                            command = MenuCommand::Left;         
                        }
                        else
                            command = MenuCommand::MissClick;
                        break;
                    case KEY_RIGHT  :
                        if( m_actualPage < (int)m_pages.size() - 1 )
                        {   
                            DelPage(m_actualPage);
                            m_actualPage++;
                            m_bottomQuestion = 0 ;
                            m_topQuestion  = 0 ;
                            m_actualCursorPosition = 0 ;
                            command = MenuCommand::Right;
                        }
                        else
                            command = MenuCommand::MissClick;
                        break;
                    case 27         :  command = MenuCommand::Escape;       break;
                    case 10         :  command = MenuCommand::Enter;        break;
                    default         :
                                nodelay(stdscr,true);
                        std::vector <int> answer;
                        answer.push_back(inputChar);
                        move( affordableCursorPos[m_actualCursorPosition], m_width/20 + 2);
                        addch ( inputChar );
                        refresh();
                        
                        while ( true )
                        {
                            nodelay(stdscr,false);
                            int inputChar = getch();
                            if( inputChar == 10 )
                            {
                                std::string finalAnswer = "";
                                for( int i = 0; i < (int)answer.size(); i++)
                                    finalAnswer += answer[i];
                            m_userAnswers[m_actualPage][m_actualCursorPosition] = finalAnswer;    
                                move( affordableCursorPos[m_actualCursorPosition], m_width/20 + 2 );
                                for( int i = 0; i <= (int)m_userAnswers[m_actualPage][m_actualCursorPosition].size() * 2; i++)
                                {
                                    addch ( 32 );
                                    refresh();
                                }    
                                    break;
                            }
                            else if( inputChar == KEY_BACKSPACE)
                            {
                                if( answer.size() == 0)
                                    continue;
                                    
                                answer.pop_back();
                                move( affordableCursorPos[m_actualCursorPosition], m_width/20 + 2 + answer.size() );
                                addch( 32 );
                                refresh();
                                move( affordableCursorPos[m_actualCursorPosition], m_width/20 + 2 + answer.size() );
                            }
                            else
                            {
                            answer.push_back(inputChar);
                            addch ( inputChar );
                            refresh();
                            }
                            
                        
                        }        
                        command = MenuCommand::MissClick;
                        break; 
                    }
            nodelay(stdscr,true);                    
    return command;  
//=============================================================================================================================
/*!
    Quiz run function, 
*/
    }
    void                                    CQuiz::Run                                      ( void )
    {
        AnswerInicial();
        while(true)
        {
            DrawPage(m_actualPage);

            if( ChooseAction() == MenuCommand::Escape)
                {
                DelPage( m_actualPage ) ;
                ShowResult();
                break;   
                }
        }
    }
//=============================================================================================================================
/*!
    Print quiz into txt file
*/
    void                                    CQuiz::MakeTxtFile                              ( void )
    {
    std::ofstream f_output( "examples/New_Quiz.txt", std::ios::out );
    int questionID = 0;
    for( auto page : m_pages )
        for( auto question : page )
        {
            std::string quaere = std::to_string(questionID) +  ") " + (*question).printQuestion() + '\n' + '\n';
            for( int i = 0; i < (int)quaere.size(); i++)
                f_output.put(quaere[i]);
            questionID ++;    
        }
    f_output.close();
    }
//=============================================================================================================================
/*!
    Show user score
*/
    void                                    CQuiz::ShowResult                               ( void ) const
    {
        CFrame frame;
        frame.SetSize();
        frame.DrawFrame();
        int right = 0;
        move( m_height / 20 + 4, m_width / 2 - m_finalLabe.size() / 2);
        for( int i = 0; i < (int)m_pages.size(); i++ )
            for( int l = 0; l < (int)m_pages[i].size(); l++ )
            {
            if( m_userAnswers[i][l] == m_pages[i][l]->getRightAnswer())
                right++;
            }
        std::string score = std::to_string(right);
        for( int i = 0; i < (int)m_finalLabe.size(); i++)
            addch( m_finalLabe[i]);
        for( int i = 0; i < (int)score.size(); i++)
            addch( score[i]);
        refresh();    
            nodelay(stdscr,false);
            getch();    
            nodelay(stdscr,true);
        
        move( m_height / 20 + 4, m_width / 2 - m_finalLabe.size() / 2);

        for( int i = 0; i < (int)m_finalLabe.size(); i++)
            addch( 32 );
        for( int i = 0; i < (int)score.size(); i++)
            addch( 32 );
        refresh();             
        
        frame.DelFrame();
    }
//=============================================================================================================================
/*!
    Prepare place for user answers
*/
    void                                    CQuiz::AnswerInicial                            ( void )
    {
    std::string TMP = "";
    std::vector < std::string> TMPC;
    for ( int i = 0 ; i < m_pageSize; i++)
    TMPC.push_back(TMP);
    for( int l = 0; l < (int)m_pages.size(); l++)
    m_userAnswers.push_back(TMPC);
    }
//=============================================================================================================================    
/*!
    clean all alocated memory
*/
    void                                    CQuiz::Clean                                    ( void )
    {
        for( auto page : m_pages )
            for( auto question : page )
                delete question;
    }    
