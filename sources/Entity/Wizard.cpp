//
// Wizard.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Mon Jun  5 17:59:53 2017 Mex
// Last update Sun Jun 18 22:29:59 2017 Paqx
//

#include "Wizard.hpp"

Wizard::Wizard(Core *core, irr::core::vector3df pos)
{
  _core = core;
  _pos = pos;
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/SelectBody.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/SelectCap.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/SelectHat.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/SelectStaff.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/WalkBody.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/WalkCap.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/WalkHat.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/WalkStaff.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/AttackBody.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/AttackCap.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/AttackHat.md3");
  _wizardMeshs.emplace_back("./resources/Mesh/Wizard/AttackStaff.md3");
  _meshNbr = 4;
  _actualMeshID = -1;
  _select = false;
  _attack = false;
  _death = false;
  _isActive = true;
  _maxLifePoint = 300;
  _lifePoint = _maxLifePoint;
  _damage = 150;
  _range = 200;
  _defense = 10;
  _speed = 250;
  _entityID = 40;
  _nextRotation = std::numeric_limits<int>::min();
  _knockback = false;
}

Wizard::~Wizard()
{
  _wizardMeshs.clear();
  clearActualMeshs();
}

void	Wizard::run(void)
{
  animateEntityAttack();
  animateEntityDeath();
  animateKnockBack();
  rotate();
}

void	Wizard::move(void)
{
}

int	Wizard::getMaxLifePoint(void) const
{
  return (_maxLifePoint);
}

void	Wizard::setMaxLifePoint(int maxLifePoint)
{
  _maxLifePoint = maxLifePoint;
}

int	Wizard::getLifePoint(void) const
{
  return (_lifePoint);
}

void	Wizard::setLifePoint(int lifePoint)
{
  _lifePoint = lifePoint;
  if (_lifePoint <= 0 && !_death && _isActive)
    {
      setAnimation(true, false, DEATH);
      _isActive = false;
    }
}

unsigned int	Wizard::getDamage(void) const
{
  return (_damage);
}

void	Wizard::setDamage(unsigned int damage)
{
  _damage = damage;
}

void	Wizard::setRange(unsigned int range)
{
  _range = range;
}

unsigned int	Wizard::getRange(void) const
{
  return (_range);
}

unsigned int	Wizard::getDefense(void) const
{
  return (_defense);
}

void	Wizard::setDefense(unsigned int defense)
{
  _defense = defense;
}

unsigned int	Wizard::getSpeed(void) const
{
  return (_speed);
}

void	Wizard::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void	Wizard::setAnimation(bool state, bool loopMode, AnimationType type)
{
  switch (type)
    {
    case SELECT:
      _select = state;
      break;
    case MOVE:
      // _move = state;
      break;
    case ATTACK:
      _attack = state;
      _isActive = false;
      break;
    case DEATH:
      _death = state;
      break;
    }
  if (state)
    {
      for (auto& it : _wizardActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(30);
	  (*it).getMesh()->setLoopMode(loopMode);
	}
    }
  else
    {
      for (auto& it : _wizardActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(0);
	  (*it).getMesh()->setLoopMode(false);
	}
    }
}

irr::core::vector3df const&	Wizard::getPosition(void) const
{
  return (_pos);
}

void	Wizard::setPosition(irr::core::vector3df const& pos)
{
  _pos = pos;
  for (auto& it : _wizardActualMeshs)
    (*it).getMesh()->setPosition(_pos);
}

void	Wizard::animateEntitySelect(void)
{
  if (_select)
    {
      _pos.Z -= 30 * _core->getFrameDeltaTime();
      setPosition(_pos);
      if (_wizardActualMeshs[0]->getMesh()->getFrameNr() >= 60)
	_select = false;
    }
}

void	Wizard::animateEntityAttack(void)
{
  if (_attack)
    {
      if (_wizardActualMeshs[0]->getMesh()->getFrameNr() >= 19)
	{
	  setActualMeshs(1);
	  setAnimation(false, false, ATTACK);
	  _isActive = true;
	}
    }
}

void	Wizard::animateEntityDeath(void)
{
  if (_death)
    {
      _rot.X -= 100 * _core->getFrameDeltaTime();
      setRotation(_rot);
      if (_wizardActualMeshs[0]->getMesh()->getRotation().X <= -90)
	setAnimation(false, false, DEATH);
    }
}

void	Wizard::animateKnockBack(void)
{
  if (_knockback && _lifePoint > 0)
    {
      if (_pos.X > _knockbackPos.X)
	_pos.X -= (300 * _core->getFrameDeltaTime());
      else if (_pos.X < _knockbackPos.X)
	_pos.X += (300 * _core->getFrameDeltaTime());
      else if (_pos.Z > _knockbackPos.Y)
	_pos.Z -= (300 * _core->getFrameDeltaTime());
      else
	_pos.Z += (300 * _core->getFrameDeltaTime());
      setPosition(_pos);
      if ((_pos.X >=  _knockbackPos.X - 10 && _pos.X <= _knockbackPos.X + 10)
	  && (_pos.Z >=_knockbackPos.Y - 10 && _pos.Z <= _knockbackPos.Y + 10))
	{
	  _knockback = false;
	  _isActive = true;
	}
    }
}

void	Wizard::setKnockBack(irr::core::position2d<irr::s32> const& knockback)
{
  _knockback = true;
  if (knockback.X == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(_pos.X, knockback.Y);
  else if (knockback.Y == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(knockback.X, _pos.Z);
  _isActive = false;
}

irr::core::position2d<irr::s32> const	Wizard::getAttackKnockback(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::position2d<irr::s32>(0, _pos.Z - (_damage * 2)));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::position2d<irr::s32>(_pos.X - (_damage * 2), 0));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::position2d<irr::s32>(0, _pos.Z + (_damage * 2)));
  return (irr::core::position2d<irr::s32>(_pos.X + (_damage * 2), 0));
}

bool	Wizard::hitbox(irr::core::rect<irr::s32> rect) const
{
  rect.repair();
  return (rect.isPointInside(irr::core::position2d<irr::s32>(_pos.X, _pos.Z)));
}

bool	Wizard::isActive(void) const
{
  return (_isActive);
}

irr::core::vector3df const&   Wizard::getRotation(void) const
{
  return (_rot);
}

void	Wizard::setRotation(irr::core::vector3df const& rot)
{
  _rot = rot;
  for (auto& it : _wizardActualMeshs)
    (*it).getMesh()->setRotation(_rot);
}

irr::core::rect<irr::s32>       Wizard::getAttackRect(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::rect<irr::s32>(_pos.X + 60, _pos.Z + 10, _pos.X - 60, _pos.Z - _range));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::rect<irr::s32>(_pos.X - _range, _pos.Z + 60, _pos.X - 10, _pos.Z - 50));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::rect<irr::s32>(_pos.X - 60, _pos.Z + _range, _pos.X + 60, _pos.Z - 10));
  return (irr::core::rect<irr::s32>(_pos.X + _range, _pos.Z - 60, _pos.X + 10, _pos.Z + 60));
}

void	Wizard::setEntityID(unsigned int const entityID)
{
  _entityID = entityID;
}

void	Wizard::clearActualMeshs()
{
  int	i = _wizardActualMeshs.size() - 1;

  while (i >= 0)
    {
      if (((_core->getScene())->getSceneNodeFromId(_wizardActualMeshs[i]->getID())))
	(_core->getScene())->getSceneNodeFromId(_wizardActualMeshs[i]->getID())->remove();
      --i;
    }
  _wizardActualMeshs.clear();
}

void	Wizard::setActualMeshs(unsigned int id)
{
  _actualMeshID = id;
  clearActualMeshs();
  unsigned int i = (id * _meshNbr);
  for (unsigned int j = 0; j < 4; j++)
    {
      _wizardActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID + j, _wizardMeshs[i].c_str(), "./resources/Mesh/Wizard/Wizard.bmp",
									_pos, irr::core::vector3df(50, 50, 50), _rot), _entityID + j, _core));
      if (id == 1)
	{
	  _wizardActualMeshs[j]->getMesh()->setLoopMode(true);
	  _wizardActualMeshs[j]->getMesh()->setAnimationSpeed(120);
	}
      else
	{
	  _wizardActualMeshs[j]->getMesh()->setLoopMode(false);
	  _wizardActualMeshs[j]->getMesh()->setAnimationSpeed(0);
	}
      ++i;
    }
}

int	Wizard::getActualMeshID(void) const
{
  return (_actualMeshID);
}

void    Wizard::setNextRotation(int nextRotation)
{
  _nextRotation = nextRotation;
}

void    Wizard::rotate(void)
{
  if (_nextRotation != std::numeric_limits<int>::min())
    {
      if (_rot.Y + 15 >= _nextRotation && _rot.Y - 15 <= _nextRotation)
	{
	  if (_nextRotation == 360)
	    _rot.Y = 0;
	  else
	    _rot.Y = _nextRotation;
	  setRotation(_rot);
	  _nextRotation = std::numeric_limits<int>::min();
	}
      else
	{
	  if (_nextRotation > _rot.Y)
	    _rot.Y += (500 * _core->getFrameDeltaTime());
	  else
	    _rot.Y -= (500 * _core->getFrameDeltaTime());
	  setRotation(_rot);
	}
    }
}

void					Wizard::AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df wizardPos,
					   irr::core::vector3df elfPos)
{
  (void)warriorPos;
  (void)valkPos;
  (void)wizardPos;
  (void)elfPos;
}
