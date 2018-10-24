/*!
 \file implementation part of classes CQuestions
 */
#include "CQuestion.h"

//=============================================================================================================================
/*!
	constructor
    \param strings question and answer
*/
                                            CQuestionTypeOne::CQuestionTypeOne              ( const std::string    & question,
                                                                                              const std::string    & answer)
                                                                                              :
                                                                                              m_question ( question ) ,
                                                                                              m_answer   ( answer   )
                                                                                              {
                                                                                              } 
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Get identical class instance but with child typ
	\return CQuestion child pointer
*/
    CQuestionTypeOne *                      CQuestionTypeOne::Clone                         ( void ) const
    {
        return new CQuestionTypeOne( * this );
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for question
	\return string question
*/
    std::string                             CQuestionTypeOne::printQuestion                 ( void ) const
    {
        return m_question;
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for answer
	\return string answer
*/
    std::string                             CQuestionTypeOne::getRightAnswer                ( void ) const
    {
        return m_answer;
    }
//=============================================================================================================================
/*!
	constructor
    \param string question, int answer
*/
                                            CQuestionTypeTwo::CQuestionTypeTwo              ( const std::string    & question,
                                                                                              int                    answer  )
                                                                                              :
                                                                                              m_question ( question ),
                                                                                              m_answer   ( answer   )                                                                                              
                                                                                              {
                                                                                              }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Get identical class instance but with child typ
	\return CQuestion child pointer
*/
    CQuestionTypeTwo *                      CQuestionTypeTwo::Clone                         ( void ) const
    {
        return new CQuestionTypeTwo( * this );
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for question
	\return string question
*/
    std::string                             CQuestionTypeTwo::printQuestion                 ( void ) const
    {
        return m_question;
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for answer
	\return string answer
*/
    std::string                             CQuestionTypeTwo::getRightAnswer                ( void ) const
    {
        std::string answerToRetutn = std::to_string( m_answer );
        return answerToRetutn;
    }
//=============================================================================================================================
/*!
	constructor
    \param strings question and answers, vector of strings with options for answer
*/
                                            CQuestionTypeThree::CQuestionTypeThree          ( const std::string    & question,
                                                                                              const std::string    & answer,  
                                                                                              std::vector < std::string > & answers)
                                                                                              :
                                                                                              m_question ( question ),
                                                                                              m_answer  ( answer      ),
                                                                                              m_AllAnswers ( answers )                                                                                              
                                                                                              {
                                                                                              }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Get identical class instance but with child typ
	\return CQuestion child pointer
*/
    CQuestionTypeThree *                    CQuestionTypeThree::Clone                       ( void ) const
    {
        return new CQuestionTypeThree( * this );
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for question
	\return string question and options for answer
*/
    std::string                             CQuestionTypeThree::printQuestion               ( void ) const
    {
        std::string questionToRetutn = m_question + '\n';
        int prefix = 97;
        for ( auto itString : m_AllAnswers )
        {   
            questionToRetutn += (char)prefix;  
            questionToRetutn += ( ". " + itString + '\n' );
            prefix++;
        }
        return questionToRetutn;
    }
//----------------------------------------------------------------------------------------------------------------------------
/*!
	Getter for answer
	\return string answer
*/
    std::string                             CQuestionTypeThree::getRightAnswer              ( void ) const
    {
        return m_answer;
    }
