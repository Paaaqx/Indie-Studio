//
// IObject.hpp for IObjects in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Tue May  9 17:42:35 2017 Anthony
// Last update Tue May  9 18:29:47 2017 Anthony
//

#ifndef IOBJECTS_HPP_
# define IOBJECTS_HPP_

# include "irrlicht.h"
# include "IEntity.hpp"

class				IObjects
{
public:
  virtual			~IObjects(){};

public:
  virtual irr::video::ITexture*	getTexture() const = 0;
  virtual void			useObject(IEntity *hero) = 0;
};

#endif /* !IOBJECTS_HPP_ */
