/*!
 \file implementation part of class CQuizMenu
 */
#include "CQuizMenu.h"




//=============================================================================================================================
/*!
	Fist Inicialisation
	\return bool flag Inicialisation is ok
*/
    bool                                    CQuizMenu::Inicialisation                       ( void )
    {
        std::ifstream f_input( m_quizProgrammName, std::ios::binary | std::ios::in );
                if(!f_input.is_open()) 
                    {
                       return false;
                    }

        while ( true )
                    {
                        char inputChar = f_input.get();

                            if( inputChar == 10 || inputChar == EOF )
                                break;
                                
                        m_password    += inputChar;
                    } 
        while ( true )
                    {
                        char inputChar = f_input.get();

                            if( inputChar == 10 || inputChar == EOF )
                            {
                                break;
                            }

                        m_quizName += inputChar;
                    }
        while ( true )
                    {
                        char inputChar = f_input.get();

                            if( inputChar == 10 || inputChar == EOF )
                                break;
                                
                        m_AmoutQustions    *= 10;
                        m_AmoutQustions    += (int)inputChar - 48;
        
                    }  
        f_input.close();                              
        return true;                    
    }
//=============================================================================================================================
/*!
    constructor
    \param string  program name
*/

                                            CQuizMenu::CQuizMenu                            ( std::string & quizName )
                                            :
                                            m_quizProgrammName  (quizName)
                                            {   
                                                toDelte = false;
                                                m_menuSize = (int)m_label.size() - 2;
                                                m_quizName = quizName ;
                                                getmaxyx(stdscr, m_height, m_width);
                                                m_isSelected = -1;
                                                m_topLabel = -1;
                                                isLogin = false;
                                                m_cursor.SetX( m_width / 20 + 2);
                                                m_cursor.SetY( m_height / 20 + 2 );
                                                m_password = "";
                                                m_quizName = "";
                                                m_AmoutQustions = 0;
                                                if(Inicialisation())
                                                    Run();
                                                else
                                                {
                                                            int x = m_width / 2 - m_InicialErrorLabel.size()/2;
                                                            int y = m_height / 2;
                                                            move( y, x);
                                                            for( int i = 0 ; i < (int)m_InicialErrorLabel.size(); i++)
                                                                {
                                                                addch( (int)m_InicialErrorLabel[i] );
                                                                refresh();
                                                                }
                                                }
                                            }
//=============================================================================================================================
/*!
    draw menu
*/
    void                                    CQuizMenu::DrawMenu                             ( void )
    {
        int pos_Y = m_height / 20 + 2;
        int pos_X = m_width / 20 + 4;
        int actualLabel = 0;

        for ( pos_Y = pos_Y ; pos_Y <  m_height - 4; pos_Y +=2 )
        {
        if( actualLabel < (int)m_label.size())
            {
            move ( pos_Y , pos_X );
            for( int l = 0; l < (int)m_label[actualLabel].size(); l++ )
                {
                    addch ( (int)m_label[actualLabel][l]);
                    refresh();

                }
            }    
        else
            break;
        m_bottomLabel = actualLabel-1;        
        actualLabel++;
        }
        if( m_bottomLabel != (int)m_label.size() - 2 )
        m_frame.SetIsBottom(false);
    else
        m_frame.SetIsBottom(true);    
    if( m_topLabel > -1 )
        m_frame.SetIsTop(false);
    else
        m_frame.SetIsTop(true);
    m_frame.SetSize();           
    m_frame.DrawFrame();
    m_cursor.SetX( m_width / 20 + 2 );
    m_cursor.SetY( m_height / 20 + 2 + (m_isSelected - m_topLabel) * 2);
    m_cursor.DrawCursor();

    refresh();
    
    }
//=============================================================================================================================
/*!
	delete menu ( visual )
*/
    void                                    CQuizMenu::DelMenu                              ( void )
    {
        int pos_Y = m_height / 20 + 2;
        int pos_X = m_width / 20 + 4;
        int actualLabel = 0;
        char menuDelChar=(char) 32;


        for ( pos_Y = pos_Y ; pos_Y <  m_height - 4; pos_Y +=2 )
        {
        if( actualLabel < (int)m_label.size())
            {
            move ( pos_Y , pos_X );
            for( int l = 0; l < (int)m_label[actualLabel].size(); l++ )
                {
                    addch ( menuDelChar );
                    refresh();

                }
            }    
        else
            break;
        m_bottomLabel = actualLabel -1;        
        actualLabel++;
        }
        m_cursor.DelCursor();
        m_frame.DelFrame();
        
    }
//=============================================================================================================================
/*!
	run fucntion for menu, manage actions and evets
*/  
    void                                    CQuizMenu::Run                                  ( void )
    {
        DrawMenu();
        while(true)
        {
        MenuCommand action = ChooseAction();
        
        if( action == MenuCommand::Enter )   
        {
            switch (m_isSelected)
            {
            case -1:
                    DelMenu();
                    StartQuiz();
                break;
            case  0:
                AddQuestion();
                break;
            case  1:
                AddQuestionFromFile();
                break;
            case  2:
                if( !isLogin)
                {
                    DelMenu();
                    m_frame.DrawFrame();
                    LoginRequester();
                    m_frame.DelFrame();
                    DrawMenu();      
                }
                else
                {
                    DelQuiz();
                    DelMenu();
                    return;
                }
                break;
            case  3:
                if( !isLogin)
                {
                    DelMenu();
                    m_frame.DrawFrame();
                    LoginRequester();
                    m_frame.DelFrame();
                    DrawMenu();      
                }
                else
                {
                    DelMenu();
                    ViewQuiz();
                }
                break;
            case  4:
                if( !isLogin)
                {
                    DelMenu();
                    m_frame.DrawFrame();
                    LoginRequester();
                    m_frame.DelFrame();
                    DrawMenu();      
                }
                else
                {
                    DelMenu();
                    PrintQuiz();
                }
                break;
            case  5:
                LogIn();
                break;
            default:
                return;
                break;
            }
        }  
            else if( action == MenuCommand::Escape) 
            {
                DelMenu();

                return;
                break;
            }
            else if( action == MenuCommand::MissClick)    
                     continue;

            else if( action == MenuCommand::Left )    
                     continue;

            else if( action == MenuCommand::Right )    
                     continue;                                            
            else
            {

                    DelMenu();
                    m_cursor.MoveCursor(action);
            }
                    m_frame.DelFrame();          
                    DrawMenu();
        }
        DelMenu();
    }
//=============================================================================================================================
/*!
	User Inicialisation for manage quiz
*/
    void                                    CQuizMenu::LogIn                                ( void )
    {
    DelMenu();
    m_frame.DrawFrame();
    std::string password = FillPassword();
    password = GoHash(password);
    if( password == m_password)
        {
            isLogin = true;
        }
    else
        {
        move( m_height / 2, m_width / 2 - m_badPassword.size());
        
        for( int i = 0; i < (int)m_badPassword.size(); i++)
                addch( m_badPassword[i]);
                        
        nodelay(stdscr,false);
        getch();
        nodelay(stdscr,true);
        move( m_height / 2, m_width / 2 - m_badPassword.size());

        for( int i = 0; i < (int)m_badPassword.size(); i++)
                addch( 32 );

        }
        m_frame.DelFrame();
        DrawMenu();
    }

//=============================================================================================================================
/*!
	Add new question
*/
    void                                    CQuizMenu::AddQuestion                          ( void )
    {

        std::ofstream f_output( m_quizProgrammName, std::ios::binary | std::ios::out | std::ios::app );
                if(!f_output.is_open()) 
                    {
                       return;
                    }    
        DelMenu();
        m_frame.DrawFrame();
        int y = m_height / 20 + 2,
            x = m_width / 20 + 2;
        move( y, x);
        if( !isLogin)
            {
                LoginRequester();
                m_frame.DelFrame();
                DrawMenu();
                f_output.close();
                return;      
            }
        for( int i = 0; i < (int)m_addQuestion.size(); i++)
                addch( m_addQuestion[i]);
        
        std::string newQuestion = ScanLabel( y, x, (int)m_addQuestion.size(), false ) + '\n';
        FilePrint( newQuestion, f_output);

        PrintRule();
        move( y, x);

        for( int i = 0; i < (int)m_addAnswer.size(); i++)
                addch( m_addAnswer[i]);
                    
        std::string newAnswer = ScanLabel( y, x, (int)m_addAnswer.size(), false ) + '\n';
        FilePrint( newAnswer, f_output);

            m_frame.DelFrame();
            DrawMenu();
        f_output.close();
    }

//=============================================================================================================================
/*!
	Add several questions from quiz fail ( marge several quizzes )
*/
    void                                    CQuizMenu::AddQuestionFromFile                  ( void )
    {
        std::ofstream f_output( m_quizProgrammName, std::ios::binary | std::ios::out | std::ios::app );
        if(!f_output.is_open()) 
            {
               return;
            }    
        DelMenu();
        m_frame.DrawFrame();
        int y = m_height / 20 + 2,
            x = m_width / 20 + 2;
        move( y, x);
        if( !isLogin)
            {
                LoginRequester();
                m_frame.DelFrame();
                DrawMenu();
                f_output.close();
                return;      
            }
            for( int i = 0; i < (int)m_addQuestionFail.size(); i++)
                    addch( m_addQuestionFail[i]);
                    
        std::string questionFail = ScanLabel( y, x, (int)m_addQuestionFail.size(), false );
        std::ifstream f_input( questionFail, std::ios::binary | std::ios::in);
        
        if(!f_input.is_open()) 
            {
               return;
            }    
        
        for( int i = 0; i < 3; i++)
            while ( true )
                {
                    char inputChar = f_input.get();
                    if( inputChar == EOF )
                            break;
                }
                    
    while ( true )
    {
        char inputChar = f_input.get();

            if( inputChar == EOF )
                break;
        f_output.put(inputChar);
    }
    f_output.close();
    f_input.close();
        
    }

//=============================================================================================================================
/*!
	Print rules for adding questions
*/
    void                                    CQuizMenu::PrintRule                            ( void ) const
    {
        int y = m_height / 20 + 2,
            x = m_width / 20 + 2;
            for ( auto rule : m_rule )
            {
            move( y, x );
            for( int i = 0; i < (int)rule.size(); i++)
                                addch( rule[i] );
            y+=2;                
            }

            nodelay(stdscr,false);
            getch();
            nodelay(stdscr,true);

            y = m_height / 20 + 2;
            move( y, x);

            for ( auto rule : m_rule )
            {
            move( y, x );
            for( int i = 0; i < (int)rule.size(); i++)
                                addch( 32 );
            y+=2;                
            }
    }    

//=============================================================================================================================
/*!
	Delete quiz ( not visual )
*/
    void                                    CQuizMenu::DelQuiz                              ( void )
    {
        toDelte = true;
    }

//=============================================================================================================================
/*!
    delete state getter
	\return bool flag to delete
*/
    bool                                    CQuizMenu::GetDeleteState                       ( void ) const
    { 
        return toDelte;
    }
//=============================================================================================================================
/*!
	Asc user to log in
*/
    void                                    CQuizMenu::LoginRequester                       ( void ) const
    {
    int y = m_height / 20 + 2,
        x = m_width / 20 + 2;
        move( y, x);
        
        for( int i = 0; i < (int)m_logoutError.size(); i++)
            addch( m_logoutError[i]);
        refresh();
        nodelay(stdscr,false);
        getch();
        nodelay(stdscr,true);
        move( y, x);
        
        for( int i = 0; i < (int)m_logoutError.size(); i++)
            addch( 32 ); 
        refresh();
       
    }
//=============================================================================================================================
/*!
	Write a message for user with warning about quiz is broken
*/
    void                                    CQuizMenu::BadFailMessage                       ( void ) const
    {
    int y = m_height / 20 + 2,
        x = m_width / 20 + 2;
        move( y, x);
        
        for( int i = 0; i < (int)m_failError.size(); i++)
            addch( m_failError[i]);
        refresh();
        nodelay(stdscr,false);
        getch();
        nodelay(stdscr,true);
        move( y, x);
        
        for( int i = 0; i < (int)m_failError.size(); i++)
            addch( 32 ); 
        refresh();
       
    }    
//=============================================================================================================================
/*!
	Run youre quiz, gl hf!
*/
    void                                    CQuizMenu::StartQuiz                            ( void ) const
    {
        try
        {
        CQuiz quiz = GeneratQuiz( false );
        quiz.Run();
        }
        catch ( ... )
        {
            return;
        }
    }
//=============================================================================================================================
/*!
	Print quiz into TXT fail 
*/
    void                                    CQuizMenu::PrintQuiz                            ( void ) const
    {
        try
        {
        CQuiz quiz = GeneratQuiz( false );
        quiz.MakeTxtFile();
        }
        catch ( ... )
        {
            BadFailMessage();
            return;
        }
    }
//=============================================================================================================================
/*!
	View whole quiz
*/
    void                                    CQuizMenu::ViewQuiz                             ( void ) const
    {
        try
        {
        CQuiz quiz = GeneratQuiz( true );
        quiz.Run();
        }
        catch ( ... )
        {
            BadFailMessage();
            return;
        }
    }
//=============================================================================================================================
/*!
    Generate quiz for run or view view - whole , run only n random questions ( n - parametr setted when quiz was created )
    \param bool flag view
	\return CQuiz instance whis  n unique random questions from all questions
*/
    CQuiz                                   CQuizMenu::GeneratQuiz                          ( bool isView ) const
    {
        std::ifstream f_input( m_quizProgrammName, std::ios::binary | std::ios::in );
        if(!f_input.is_open()) 
                throw std::domain_error("Bad quiz program file");

        for( int i = 0; i < 3; i++)
            while ( true )
            {
                char inputChar = f_input.get();
                if( inputChar == 10 )
                    break;
                if( inputChar == EOF )
                   throw std::domain_error("Bad quiz program file");
            }
        std::vector < std::pair < std::string, std::string > > questions;

        std::string inputAnswer   = "";
        std::string inputQuestion = "";

        while ( true )
        {
            char inputChar;
            while( true )
                {
                    inputChar = f_input.get();
                    if( inputChar == 10 || inputChar == EOF )
                        break;
                    inputQuestion += inputChar;
                }
            while( true )
                {
                    inputChar = f_input.get();
                    if( inputChar == 10 || inputChar == EOF)
                        break;
                    inputAnswer += inputChar;
                }
                
                if( inputChar == EOF )
            {
                break;
            }
            else if ( inputChar == 10 )
            {
                questions.emplace_back( inputQuestion ,inputAnswer);
                inputQuestion  = "";
                inputAnswer    = "";
            }                       

        }
        f_input.close();
        int bound    = (int)questions.size();
        int pageSize = (int)questions.size();
        if( !isView)
        {
        if( m_AmoutQustions < (int)questions.size())
            bound = m_AmoutQustions;

        srand(unsigned(time(0)));
        random_shuffle(questions.begin(), questions.end());
        pageSize = 5;
        }
        CQuiz m_quiz ( pageSize );
        for ( int i = 0; i < bound; i++)
        {
            m_quiz.AddTask(questions[i].first, questions[i].second );
        }
        return m_quiz;
    }

