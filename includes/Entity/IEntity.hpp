//
// Entity.hpp for entity.hpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Mon May  8 16:59:20 2017 Anthony
// Last update Sun Jun 18 22:11:48 2017 Paqx
// Last update Mon May 15 18:14:54 2017 Mex
//

#ifndef IENTITY_HPP_
# define IENTITY_HPP_

# include <iostream>
# include <vector>
# include <irrlicht.h>
// # include "IPowerUp.hpp"
// # include "IObject.hpp"

class Player;

class						IEntity
{
public:
  virtual ~IEntity(){};

public:
    enum					AnimationType
    {
      SELECT = 0,
      MOVE = 1,
      ATTACK = 2,
      DEATH = 3,
    };

public:
  virtual void					AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df WizardPos,
					   irr::core::vector3df elfPos) = 0;
  virtual void					run(void) = 0;
  virtual void					move(void) = 0;
  virtual int					getMaxLifePoint(void) const = 0;
  virtual void					setMaxLifePoint(int maxlifePoint) = 0;
  virtual int					getLifePoint(void) const = 0;
  virtual void					setLifePoint(int lifePoint) = 0;
  virtual unsigned int				getDamage(void) const = 0;
  virtual void					setDamage(unsigned int damage) = 0;
  virtual void					setRange(unsigned int range) = 0;
  virtual unsigned int				getRange(void) const = 0;
  virtual unsigned int				getDefense(void) const = 0;
  virtual void					setDefense(unsigned int defense) = 0;
  virtual unsigned int				getSpeed(void) const = 0;
  virtual void					setSpeed(unsigned int speed) = 0;
  virtual void					setAnimation(bool state, bool loopMode, AnimationType type) = 0;
  virtual void					animateEntitySelect(void) = 0;
  virtual void					animateEntityAttack(void) = 0;
  virtual void		                        animateEntityDeath(void) = 0;
  virtual void					animateKnockBack(void) = 0;
  virtual void					setKnockBack(irr::core::position2d<irr::s32> const& knockback) = 0;
  virtual irr::core::position2d<irr::s32> const	getAttackKnockback(void) = 0;
  virtual bool					isActive(void) const = 0;
  virtual bool					hitbox(irr::core::rect<irr::s32> rect) const = 0;
  virtual irr::core::vector3df const&		getPosition(void) const = 0;
  virtual void					setPosition(irr::core::vector3df const& pos) = 0;
  virtual irr::core::rect<irr::s32>		getAttackRect(void) = 0;
  virtual irr::core::vector3df const&		getRotation(void) const = 0;
  virtual void					setRotation(irr::core::vector3df const& rot) = 0;
  virtual void					setEntityID(unsigned int const entityID) = 0;
  virtual void					setActualMeshs(unsigned int id) = 0;
  virtual int					getActualMeshID(void) const = 0;
  virtual void					clearActualMeshs(void) = 0;
  virtual void					setNextRotation(int nextRotation) = 0;
  virtual void					rotate(void) = 0;
};

#endif /* !IENTITY_HPP_ */
