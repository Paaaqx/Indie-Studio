//
// Errors.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Wed May  3 16:52:34 2017 Mex
// Last update Thu Jul  6 09:21:11 2017 Paqx
//

#ifndef ERRORS_HPP_
# define ERRORS_HPP_

# include <string>
# include <exception>

class	GauntletError : public std::exception
{
public:
  GauntletError(std::string const &message) throw();
  virtual ~GauntletError() throw();
  
public:
  const char	*what() const throw();
  
private:
  std::string	_message;
};

class   Error : public GauntletError
{
public:
  Error(std::string const &message);
};

#endif /* !ERRORS_HPP */
