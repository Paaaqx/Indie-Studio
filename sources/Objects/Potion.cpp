//
// Potion.cpp for  in /home/pritesh/rendu/cpp_indie_studio/sources/Objects
// 
// Made by Pritesh
// Login   <pritesh.patel@epitech.eu>
// 
// Started on  Wed May 10 17:15:56 2017 Pritesh
// Last update Fri May 12 17:24:09 2017 Pritesh
//

#include "../../includes/Potion.hpp"

Potion::Potion()
{
}

Potion::Potion(Potion const &other)
{
  _potion = other._potion;
}

Potion::~Potion()
{
}

Potion&	Potion::operator=(Potion const &other)
{
  _potion = other._potion;
}

void	Potion::useObjct(IEntity *hero)
{
  if (hero->getlifePoint() + _potion > hero->getmaxlifePoint())
    hero->setlifePoint(hero->getmaxlifePoint);
  hero->setlifePoint(hero->getlifePoint() + _potion);
}
