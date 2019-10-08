//
// Elf.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Tue Jun  6 15:51:49 2017 Mex
// Last update Sun Jun 18 22:27:47 2017 Paqx
//

#ifndef ELF_HPP_
# define ELF_HPP_

# include "IEntity.hpp"
# include "MeshManager.hpp"

class					Elf : public IEntity
{
public:
  Elf(Core *core, irr::core::vector3df pos);
  ~Elf();
  
public:
  void					AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df WizardPos,
					   irr::core::vector3df elfPos) override;
  void					run(void) override;
  void					move(void) override;
  int					getMaxLifePoint(void) const override;
  void					setMaxLifePoint(int maxLifePoint) override;
  int					getLifePoint(void) const override;
  void					setLifePoint(int lifePoint) override;
  unsigned int				getDamage(void) const override;
  void					setDamage(unsigned int damage) override;
  void					setRange(unsigned int range) override;
  unsigned int				getRange(void) const override;
  unsigned int				getDefense(void) const override;
  void					setDefense(unsigned int defense) override;
  unsigned int				getSpeed(void) const override;
  void					setSpeed(unsigned int speed) override;
  void					setAnimation(bool state, bool loopMode, AnimationType type) override;
  void					animateEntitySelect(void) override;
  void					animateEntityAttack(void) override;
  void					animateEntityDeath(void) override;
  void					animateKnockBack(void) override;
  void					setKnockBack(irr::core::position2d<irr::s32> const& knockback) override;
  irr::core::position2d<irr::s32> const	getAttackKnockback(void) override;
  bool					hitbox(irr::core::rect<irr::s32> rect) const override;
  irr::core::vector3df	const&		getPosition(void) const override;
  void					setPosition(irr::core::vector3df const& pos) override;
  irr::core::rect<irr::s32>		getAttackRect(void) override;
  irr::core::vector3df const&		getRotation(void) const override;
  void					setRotation(irr::core::vector3df const& rot) override;
  bool					isActive(void) const override;
  void					setEntityID(unsigned int const entityID);
  void					setActualMeshs(unsigned int id) override;
  int					getActualMeshID(void) const override;
  void					clearActualMeshs(void) override;
  void					setNextRotation(int nextRotation) override;
  void					rotate(void) override;
  
private:
  Core*					_core;
  irr::core::vector3df			_pos;
  irr::core::vector3df			_rot;
  int					_nextRotation;
  std::vector<std::string>		_elfMeshs;
  std::vector<MeshManager*>		_elfActualMeshs;
  bool					_select;
  bool					_attack;
  bool					_death;
  bool					_isActive;
  int					_maxLifePoint;
  int					_lifePoint;
  unsigned int				_damage;
  unsigned int				_range;
  unsigned int				_defense;
  unsigned int				_speed;
  unsigned int					_meshNbr;
  int					_actualMeshID;
  unsigned int				_entityID;
  bool					_knockback;
  irr::core::position2d<irr::s32>	_knockbackPos;
  // IObject			_object;
  // IPowerUp			_powerUp;
};

#endif /* !ELF_HPP_ */
