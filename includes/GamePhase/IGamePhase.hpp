//
// IGamePhase.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Mon May  8 23:17:45 2017 Mex
// Last update Tue May  9 18:11:48 2017 Mex
//

#ifndef IGAMEPHASE_HPP
# define IGAMEPHASE_HPP

# include <irrlicht.h>

class		IGamePhase
{
public:
  virtual ~IGamePhase(){}

public:
  virtual void	init(void) = 0;
  virtual void	run(void) = 0;
  virtual void	stop(void) = 0;
};

#endif /* !IGAMEPHASE_HPP_ */
