/*!
 \file implementation part of class CMenu
 */
#include "CMenu.h"

/*!
	Hashing and salting input string
    \param string to hashing
	\return hash of input string
*/
    std::string                            CMenu::GoHash                                    ( std::string & password ) const
    {

        uint64_t outputHash = 66;
    	for ( uint32_t i = 0; i < password.size(); i++ ) 
        {
    		outputHash = ( outputHash * 67751) ^ (( password[i] + 32) * 86719);
            i++;
      }
            std::string outStringHash = std::to_string( outputHash );
            std::string SALT = "00110011";

          outStringHash += SALT;
    	return outStringHash;
    }
//=============================================================================================================================
/*!
	Wait while user dont press key for choosing action
	\return choosing command
*/
    MenuCommand                         CMenu::ChooseAction                                 ( void )
    {
        nodelay(stdscr,false);
        MenuCommand command;
            
                    int inputChar = getch();
                    switch (inputChar)
                    {
                    case KEY_UP     :
                        if( m_isSelected > m_topLabel )
                            {
                            m_isSelected--;
                            command = MenuCommand::Up;
                            }
                        else if ( m_isSelected == m_topLabel && m_topLabel > -1)
                            {
                                DelMenu();
                                m_topLabel --;
                                m_bottomLabel --;
                                command = MenuCommand::Down;
                            }
                        else   
                            command = MenuCommand::MissClick;
                                                                                break;
                    case KEY_DOWN   :  
                        if( m_isSelected < m_bottomLabel )
                            {
                            m_isSelected++;
                            command = MenuCommand::Down;
                            }
                        else if ( m_isSelected == m_bottomLabel && m_bottomLabel < m_menuSize )
                            {
                                DelMenu();                                
                                m_topLabel ++;
                                m_bottomLabel ++;
                                command = MenuCommand::Up;
                                    
                            }
                        else   
                            command = MenuCommand::MissClick;
                                                                            break;
                    case KEY_LEFT   :  command = MenuCommand::Left;         break;
                    case KEY_RIGHT  :  command = MenuCommand::Right;        break;
                    case 27         :  command = MenuCommand::Escape;       break;
                    case 10         :  command = MenuCommand::Enter;        break;
                    default         :  command = MenuCommand::MissClick;    break; 
                    }
            nodelay(stdscr,true);                    
    return command;  

    }
//=============================================================================================================================
/*!
	Print to file
    \param string to print and ofstream to file
*/
    bool                                    CMenu::FilePrint                                ( std::string & toPrint, std::ofstream & stream ) const
    {
        if(!stream.is_open())
            return false;

                for( int q = 0;  q < (int)toPrint.size(); q++ )
                               stream.put(toPrint[q]);
        return true;

    }
//=============================================================================================================================
/*!
	Reed users input and clean srcreen after reeding
    \param y , x = starting coordinates, size of label to delete, flag for password 
	\return input string
*/     
    std::string                             CMenu::ScanLabel                                ( int y, int x, int labelSize, bool isPasssword )
    {
        std::string   inputLabel = "";
        std::vector <int> newName;
        
            int start_x = x;
            int start_y = y;
            y+=2;
            move( y, x);
            while(true)
            {
                addch( 95 );
                refresh();
                nodelay(stdscr,false);
                int inputChar = getch();
    
                 if( inputChar == KEY_BACKSPACE )
                        {
                        move( y, x);
                            if( x ==  start_x )
                        continue;
                        addch( 32 );
                        refresh();
                        x--;
                        move(y , x );    
                        
                
                        newName.pop_back();
                        }
                else if( inputChar == 10 )
                {
                        for ( int a = 0;  a <  (int) newName.size()  ; a++)
                            inputLabel +=  newName[a];
                            x = start_x;
                            y = start_y;
                        move( y, x );
                        while( x <= start_x + labelSize )
                        {
                            addch( 32 );
                            refresh();
                            x++;
                        }
                        y += 2;
                        x = start_x;
                        move( y, x );
                        while( x <= start_x + (int)newName.size() )
                            {
                            addch( 32 );
                            refresh();
                            x++;
                        }
                                        nodelay(stdscr,true);
                        return    inputLabel;

                    }       
                    else
                    {

                    
                        move( y, x);
                        x++;
                        if ( isPasssword )
                            addch( 42 );
                        else    
                        addch( inputChar );
                                refresh();

                        newName.push_back(inputChar);
                        move( y, x);
                    }
        }
    }
//=============================================================================================================================                                            
/*!
	Asc user to write a password, call scanLabel with flag password
	\return user password
*/  
    std::string                             CMenu::FillPassword                             ( void )
    {
        std::string newPassword;
        int x = m_width / 2 - m_QuizPassword.size()/2;
        int y = m_height / 2;
        move( y, x);
        for( int i = 0 ; i < (int)m_QuizPassword.size(); i++)
            {
            addch( (int)m_QuizPassword[i] );
            refresh();
            }
        newPassword = ScanLabel( y, x, (int)m_QuizPassword.size(), true); 
        return newPassword;

    }          
