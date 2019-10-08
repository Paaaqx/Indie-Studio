//
// Errors.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Wed May  3 16:50:18 2017 Mex
// Last update Thu Jul  6 09:22:16 2017 Paqx
//

#include "Errors.hpp"

GauntletError::GauntletError(std::string const &message) throw()
{
  this->_message = message;
}

GauntletError::~GauntletError() throw(){}

const char *GauntletError::what() const throw()
{
  return _message.c_str();
}

Error::Error(std::string const &message) : GauntletError(message){}
