//
// IPowerUp.hpp for IPowerUp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Tue May  9 18:14:51 2017 Anthony
// Last update Tue May  9 18:29:24 2017 Anthony
//

#ifndef IPOWERUP_HPP_
# define IPOWERUP_HPP_

# include "irrlicht.h"
# include "IEntity.hpp"

class				IPowerUp
{
public:
  virtual			~IPowerUp(){};

public:
  virtual irr::video::ITexture*	getTexture() const = 0;
  virtual void			usePowerUp(IEntity *hero) const = 0
}

#endif /* !IPOWERUP_HPP_ */
