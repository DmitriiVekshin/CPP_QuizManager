/*!
 \file implementation part of class CFrame
 */ 
#include "CFrame.h"

//=============================================================================================================================
/*!
	Frame constructor
*/
                                            CFrame::CFrame                                  ( void )
                                            {
                                                isTop = true;
                                                isBottom = true;
                                            }
//=============================================================================================================================                                            
/*!
	Frame destructor
*/
                                            CFrame::~CFrame                                 ( void )
                                            {
                                                this->DelFrame();   
                                            }
//=============================================================================================================================
/*!
	set frame size by size window
*/
    void                                    CFrame::SetSize                                 ( void )
    {
        getmaxyx(stdscr, m_height, m_width);
    }    
//=============================================================================================================================
/*!
	is Top flag setter
    \param bool flag
*/
    void                                    CFrame::SetIsTop                                ( bool  _top        )
    {
        isTop = _top;
    }
//=============================================================================================================================
/*!
    is Bottom flag setter
    \param bool flag
*/
    void                                    CFrame::SetIsBottom                             ( bool  _bottom     )
    {
        isBottom = _bottom;
    }
//=============================================================================================================================
    bool                                    CFrame::GetIsTop                                ( void       ) const
    {
        return isTop;
    }
//=============================================================================================================================

    bool                                    CFrame::GetIsBottom                             ( void       ) const
    {
        return isBottom;
    }
//=============================================================================================================================

    int                                     CFrame::GetHeight                               ( void       ) const
    {
        return m_height;
    }
//=============================================================================================================================

    int                                     CFrame::GetWidth                                ( void       ) const
    {
        return m_width;
    }
//=============================================================================================================================
/*!
	Draw frame
*/
    void                                    CFrame::DrawFrame                               ( void ) const
    {
        initscr();
        nodelay(stdscr,true);   
        keypad(stdscr,true);    
        noecho();               
        curs_set(0);
        refresh();
        char frameChar =    (char) 254;
        char splitterChar = (char)  43;


        for(int i=0;i<m_width;i++)
        {
                move(0,i);
                if( isTop )
                    addch(frameChar);
                else
                    addch(splitterChar);
        }
        for(int i=0;i<m_height;i++)
        {
                move(i,0);
                addch(frameChar);
        }
        for(int i=0;i<m_width;i++)
        {
                move(m_height-1,i);
                if( isBottom )
                    addch(frameChar);
                else
                    addch(splitterChar);
        }
        for(int i=0;i<m_height;i++)
        {
                move(i,m_width-1);
                addch(frameChar);
        }
                refresh();
    }
//=============================================================================================================================
/*!
	Delete frame
*/
    void                                    CFrame::DelFrame                                ( void ) const
    {
        refresh();
        
        char clearChar=(char)32;

        for(int i=0;i<m_width;i++)
        {
                move(0,i);
                addch(clearChar);
        }
        for(int i=0;i<m_height;i++)
        {
                move(i,0);
                addch(clearChar);
        }
        for(int i=0;i<m_width;i++)
        {
                move(m_height-1,i);
                addch(clearChar);
        }
        for(int i=0;i<m_height;i++)
        {
                move(i,m_width-1);
                addch(clearChar);
        }
                refresh();
    }
