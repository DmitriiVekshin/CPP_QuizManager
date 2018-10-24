/*!
 \file Contains command for menu
 */

//=================================================================================================

#ifndef CCOMAND_H
#define CCOMAND_H
enum MenuCommand {   Up         , /// move cursor up
                     Down       , /// move cursor down
                     Left       , /// open next page 
                     Right      , /// open previos pade
                     Enter      , /// select ot enter
                     Escape     , /// close actual menu
                     MissClick    /// users missclicks or wrong commands
                                };  
#endif