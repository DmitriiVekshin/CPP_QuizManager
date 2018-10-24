/*!
 \file implementation part of class CMainMenu
 */
#include "CMainMenu.h"


//=============================================================================================================================
/*!
    constructor
    \param int ID, string quiz name
*/
                                            CQuizHead::CQuizHead                            ( int id , std::string name )
                                            :
                                                m_name ( name ),
                                                m_id  ( id )
                                            {}
//=============================================================================================================================
/*!
    getter name
*/
    std::string                             CQuizHead::GetName                              ( void               ) const
    {
        return m_name;
    }
//=============================================================================================================================    
/*!
    getter ID
*/
    int                                     CQuizHead::GetID                                ( void               ) const
    {
        return m_id;
    }
//=============================================================================================================================



//=============================================================================================================================
/*!
    constructor
*/
                                            CMainMenu::CMainMenu                            ( void )
                                            {
                                                m_nQuiz = 0;
                                                m_isSelected = -1;
                                                m_topLabel = -1;
                                                m_bottomLabel = -1;
                                                HeadlistInicialization();
                                                m_menuSize = (int)m_quizHead.size() - 1;
                                                getmaxyx(stdscr, m_height, m_width);
                                                m_cursor.SetX( m_width / 20 + 2);
                                                m_cursor.SetY( m_height / 20 + 2 );

                                            }
//=============================================================================================================================                                            
/*!
    destructor
*/
                                            CMainMenu::~CMainMenu                            ( void )
                                            {
                                                DelMenu();

                                            }
//=============================================================================================================================
/*!
    Start inicialization
*/
    void                                    CMainMenu::HeadlistInicialization                          ( void )
    {
        std::ifstream f_input(HEADLIST, std::ios::binary | std::ios::in );
        if(!f_input.is_open()) 
        {
            std::ofstream f_output(HEADLIST, std::ios::binary | std::ios::out );
                                           f_output.close();
        return;
        }
        std::string inputWord = "";
        int i = 0;
            

        int  inputInt  = 0;
        while( true  )
        {
            i = 0;                    
            inputWord = "";
            inputInt  = 0;
            while ( true )
            {
                char inputChar = f_input.get();

                if( inputChar == 10 )
                    break;
                else if ( inputChar == EOF )
                {
                    m_nQuiz = m_quizHead.size();
                    return;
                }

                inputInt    *= 10;
                inputInt    += (int)inputChar - 48;
            }  
            while ( true )
            {
                char inputChar = f_input.get();

                if( inputChar == 10 || inputChar == EOF )
                {
                    m_quizHead.emplace_back( inputInt, inputWord );
                    break;
                }

                inputWord += inputChar;
                i++;
            }
        }
    }
//=============================================================================================================================
/*!
    asc to write name for new quiz, then reed it and clean screen
	\return quiz name
*/        
    std::string                             CMainMenu::FillQuizName                         ( void )
    {
        std::string newName;
        DelMenu();
        m_frame.SetSize();           
        int x = m_width / 2 - m_NewQuizLabel.size()/2;
        int y = m_height / 2;
        move( y, x);
        for( int i = 0 ; i < (int)m_NewQuizLabel.size(); i++)
            {
            addch( (int)m_NewQuizLabel[i] );
            refresh();
            }

        newName =  ScanLabel( y, x, (int)m_NewQuizLabel.size(), false);
        return newName;
    }  
//=============================================================================================================================
/*!
    asc to write size of new quiz, then reed it and clean screen 
	\return quiz size
*/   
    std::string                                     CMainMenu::SetSizeQuiz                                     ( void )
    {
        std::string nQuestion;        
        int x = m_width / 2 - m_NewQuizAmountQuestion.size()/2;
        int y = m_height / 2;
        move( y, x);
        for( int i = 0 ; i < (int)m_NewQuizAmountQuestion.size(); i++)
            {
            addch( (int)m_NewQuizAmountQuestion[i] );
            refresh();
            }
        nQuestion = ScanLabel( y, x, (int)m_NewQuizAmountQuestion.size(), false); 
        return nQuestion;

    }    
    
//=============================================================================================================================
/*!
    Add new quiz, create quiz, updates program files, call quiz menu
*/   
    void                                    CMainMenu::AddQuiz                              ( void )
    {
    CFrame newFrame;
    newFrame.SetSize();
    newFrame.DrawFrame();    
    std::string name = FillQuizName();
             for ( auto iter : m_quizHead )
                if ( iter.GetName() == name )
                {
                int x = m_width / 2 - m_NameErrorLabel.size()/2;
                int y = m_height / 2;
                move( y, x);
                for( int i = 0 ; i < (int)m_NameErrorLabel.size(); i++)
                    {
                    addch( (int)m_NameErrorLabel[i] );
                    refresh();
                    }
                    nodelay(stdscr,false);
                    getch();
                    nodelay(stdscr,true);
                    
                for( int i = 0 ; i < (int)m_NameErrorLabel.size(); i++)
                    {
                    addch( 32 );
                    refresh();
                    }    
                AddQuiz();
                return;
                }
    std::string password = FillPassword();
    m_nQuiz++;
    m_quizHead.emplace_back( m_nQuiz, name );

    std::string quizID = std::to_string(m_nQuiz);
    std::string quizProgrammName = "examples/quiz" + quizID + ".bin";
    name   += "\n";
    quizID += "\n";
    std::ofstream f_HeadOutput(HEADLIST, std::ios::binary | std::ios::app );
    FilePrint( quizID, f_HeadOutput);
    FilePrint( name, f_HeadOutput);
    f_HeadOutput.close();
    std::string nQuestion = SetSizeQuiz();

    std::ofstream f_BodyOutput( quizProgrammName, std::ios::binary | std::ios::out );
    password = GoHash( password );
    password += "\n";
    nQuestion += "\n";
       
    FilePrint( password, f_BodyOutput );
    FilePrint( name, f_BodyOutput );
    FilePrint( nQuestion, f_BodyOutput );
    f_BodyOutput.close();
    m_menuSize ++;
                    m_cursor.DelCursor();
                    m_frame.DelFrame();          
                    DelMenu();

    if(!CallQuizMenu( quizProgrammName ))
    {
        m_quizHead.pop_back();
        m_menuSize --;
        m_nQuiz--;
        char * failToDelete = new char [quizProgrammName.size()];
        std::strncpy (failToDelete, quizProgrammName.c_str(), quizProgrammName.size() );
        std::remove( failToDelete );
        delete [] failToDelete;
    }
                    DrawMenu();
                    m_frame.DrawFrame();
                    m_cursor.DrawCursor();
    return;
    }
    
//=============================================================================================================================
/*!
    Call quiz menu
    \param called quiz program name
	\return flag to return, if is true delete this quiz
*/
    bool                                    CMainMenu::CallQuizMenu                         ( std::string & quiz ) const
    {
        CQuizMenu m_quizMenu ( quiz );
        if( m_quizMenu.GetDeleteState() == true)
            return false;
        return true;
    }
//=============================================================================================================================
/*!
    Draw menu
*/
    void                                    CMainMenu::DrawMenu                         ( void )
    {
    refresh();        
        getmaxyx(stdscr, m_height, m_width);
    int pos_Y = m_height / 20 + 2;
    int actualQuiz = m_topLabel;
    if( m_topLabel == -1)
    {
        move( pos_Y , m_width / 20 + 4 );
        for ( auto i = 0 ; i <  (int)m_mainMenuLabel.size(); i ++)
        {
        addch(m_mainMenuLabel[i]);
        refresh();
        }
            pos_Y+=2;
        actualQuiz = 0;
    }


    for ( int i = pos_Y ; i <  m_height - 4; i+=2)
    {   
        if( actualQuiz < (int)m_quizHead.size())
        {
        move( i , m_width / 20 + 4 );
            for ( int l = 0 ; l <  (int)m_quizHead[actualQuiz].GetName().size(); l ++)
            {
                addch(m_quizHead[actualQuiz].GetName()[l]);
                refresh();
            }
        }    
        else
            break;            
        m_bottomLabel = actualQuiz;
        actualQuiz++;
    }
    if( m_bottomLabel != (int)m_quizHead.size() - 1 && m_quizHead.size() != 0)
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
    Delete menu ( visual )
*/  
    void                                    CMainMenu::DelMenu                          ( void )
    {
        refresh();        
        char menuDelChar=(char) 32;
        int pos_Y = m_height / 20 + 2;
        int actualQuiz = m_topLabel;
        if( m_topLabel == -1)
        {
            move( pos_Y , m_width / 20 + 4 );
            for ( auto i = 0 ; i <  (int)m_mainMenuLabel.size(); i ++)
                {
                addch(menuDelChar);
                refresh();
                }
            pos_Y+=2;
            actualQuiz = 0;
            m_cursor.DelCursor();
            m_frame.DelFrame();
        }
    



        for ( int i = pos_Y ; i <  m_height - 4; i+=2)
        {   

            if( actualQuiz < (int)m_quizHead.size())
            {
                move( i , m_width / 20 + 4 );
                for ( auto l = 0 ; l <  (int)m_quizHead[actualQuiz].GetName().size(); l ++)
                {
                    addch(menuDelChar);
                    refresh();
                }
            }    
            else
                break;            
            m_bottomLabel = actualQuiz;
            actualQuiz++;
        }
    
    refresh();
    }
//=============================================================================================================================
/*!
    Menu run function, choose actions
*/
    void                                    CMainMenu::Run                                  ( void )
    {                           
        DrawMenu();

        while(true)
        {
        MenuCommand action = ChooseAction();
        
            if( action == MenuCommand::Enter )   
            {
                if(m_isSelected == -1)
                    {
                    AddQuiz();
                    }
                else
                {
                    std::string quizID = std::to_string(m_quizHead[m_isSelected].GetID());
                    std::string quizProgrammName = "examples/quiz" + quizID  + ".bin";
                    DelMenu();
                    m_frame.DelFrame();          
                    m_cursor.DelCursor();
                    if(!CallQuizMenu( quizProgrammName ))
                    {
                        m_quizHead.erase( m_quizHead.begin() + m_isSelected);
                        m_menuSize --;
                        m_nQuiz--;
                        char * failToDelete = new char [quizProgrammName.size()];
                        std::strncpy (failToDelete, quizProgrammName.c_str(), quizProgrammName.size() );
                        std::remove( failToDelete );
                        delete [] failToDelete;
                    }
                m_cursor.DrawCursor();
                }
                
            }  
            else if( action == MenuCommand::Escape) 
            {
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
    }

