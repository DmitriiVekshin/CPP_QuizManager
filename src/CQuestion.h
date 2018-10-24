/*!
 \file declaration part of classes CQuestion
 */
#ifndef CQUESTION_H
#define CQUESTION_H
#include <string>
#include <vector>

/*!
	\brief Parent class for question

    question interface
*/
class CQuestion
{
    public: 
                                            CQuestion                                       ( void ){}
//-----------------------------------------------------------------------------------------------------------------------------                                            
    virtual                                 ~CQuestion                                      ( void ){}
//-----------------------------------------------------------------------------------------------------------------------------    
    virtual CQuestion *                     Clone                                           ( void ) const = 0;
//-----------------------------------------------------------------------------------------------------------------------------    
    virtual std::string                     printQuestion                                   ( void ) const = 0;
//-----------------------------------------------------------------------------------------------------------------------------    
    virtual std::string                     getRightAnswer                                  ( void ) const = 0;

};
//=============================================================================================================================
/*!
	\brief Child class for question

    class represent text question with one word answer 

*/
class CQuestionTypeOne : public CQuestion
{
    public:
                                            CQuestionTypeOne                                ( const std::string    & ,
                                                                                              const std::string    & );
//-----------------------------------------------------------------------------------------------------------------------------                                                                                              
    CQuestionTypeOne *                      Clone                                           ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             printQuestion                                   ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             getRightAnswer                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    private:

    const std::string m_question;
    const std::string m_answer;


};
//=============================================================================================================================
/*!
	\brief Child class for question

    class represent text question with one numeric answer 

*/
class CQuestionTypeTwo : public CQuestion
{
    public:
                                            CQuestionTypeTwo                                ( const std::string    & ,
                                                                                              int                    );
//-----------------------------------------------------------------------------------------------------------------------------                                                                                              
    CQuestionTypeTwo *                      Clone                                           ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             printQuestion                                   ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             getRightAnswer                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    private:

    const std::string m_question;
    const int m_answer;
    
};
//=============================================================================================================================
/*!
	\brief Child class for question

    class represent text question with n presented option, user should choose correct option 

*/
class CQuestionTypeThree : public CQuestion

{
    public:
                                            CQuestionTypeThree                              ( const std::string    & ,
                                                                                              const std::string    & ,  
                                                                                              std::vector < std::string > & );
//-----------------------------------------------------------------------------------------------------------------------------                                                                                              
    CQuestionTypeThree *                    Clone                                           ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             printQuestion                                   ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    std::string                             getRightAnswer                                  ( void ) const;
//-----------------------------------------------------------------------------------------------------------------------------    
    private:

    const std::string m_question;
    const std::string m_answer;
    std::vector < std::string > m_AllAnswers;

};

#endif