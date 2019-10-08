
//
// Potion.hpp for  in /home/pritesh/rendu/cpp_indie_studio/includes
// 
// Made by Pritesh
// Login   <pritesh.patel@epitech.eu>
// 
// Started on  Wed May 10 17:00:12 2017 Pritesh
// Last update Fri Jun 16 11:40:20 2017 Anthony
//

#ifndef POTION_HPP_
# define POTION_HPP_

# include "IObject.hpp"

class			Potion : public IObjects
{
public:
  Potion();
  Potion(Potion const &other);
  ~Potion();
  Potion &operator=(Potion const &other);

public:
  irr::video::ITexture*	getTexture() const;
  void			useObject(IEntity *hero);

private:
  int			_potion;
}

#endif /*  !POTION_HPP_  */
