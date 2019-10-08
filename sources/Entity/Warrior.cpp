//
// Warrior.cpp for  in /home/pritesh/rendu/cpp_indie_studio/sources/Entity
//
// Made by Pritesh
// Login   <pritesh.patel@epitech.eu>
//
// Started on  Wed May 10 14:50:25 2017 Pritesh
// Last update Sun Jun 18 22:29:43 2017 Paqx
//

#include "Warrior.hpp"

Warrior::Warrior(Core *core, irr::core::vector3df pos)
{
  _core = core;
  _pos = pos;
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/SelectBody.md3");
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/SelectAxe.md3");
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/WalkBody.md3");
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/WalkAxe.md3");
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/AttackBody.md3");
  _warriorMeshs.emplace_back("./resources/Mesh/Warrior/AttackAxe.md3");
  _meshNbr = 2;
  _actualMeshID = -1;
  _select = false;
  _attack = false;
  _death = false;
  _maxLifePoint = 600;
  _lifePoint = _maxLifePoint;
  _damage = 100;
  _range = 130;
  _defense = 50;
  _speed = 275;
  _nextRotation = std::numeric_limits<int>::min();
  _entityID = 10;
  _isActive = true;
  _knockback = false;
}

Warrior::~Warrior()
{
  _warriorMeshs.clear();
  _warriorActualMeshs.clear();
}

void	Warrior::run(void)
{
  animateEntityAttack();
  animateEntityDeath();
  rotate();
}

void	Warrior::move(void)
{
}

int	Warrior::getMaxLifePoint(void) const
{
  return (_maxLifePoint);
}

void	Warrior::setMaxLifePoint(int maxLifePoint)
{
  _maxLifePoint = maxLifePoint;
}

int	Warrior::getLifePoint(void) const
{
  return (_lifePoint);
}

void	Warrior::setLifePoint(int lifePoint)
{
  _lifePoint = lifePoint;
  if (_lifePoint <= 0 && !_death && _isActive)
    {
      setAnimation(true, false, DEATH);
      _isActive = false;
    }
}

unsigned int	Warrior::getDamage(void) const
{
  return (_damage);
}

void	Warrior::setDamage(unsigned int damage)
{
  _damage = damage;
}

void	Warrior::setRange(unsigned int range)
{
  _range = range;
}

unsigned int	Warrior::getRange(void) const
{
  return (_range);
}

unsigned int	Warrior::getDefense(void) const
{
  return (_defense);
}

void	Warrior::setDefense(unsigned int defense)
{
  _defense = defense;
}

unsigned int	Warrior::getSpeed(void) const
{
  return (_speed);
}

void	Warrior::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void	Warrior::setAnimation(bool state, bool loopMode, AnimationType type)
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
      for (auto& it : _warriorActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(30);
	  (*it).getMesh()->setLoopMode(loopMode);
	}
    }
  else
    {
      for (auto& it : _warriorActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(0);
	  (*it).getMesh()->setLoopMode(false);
	}
    }
}

irr::core::vector3df const&	Warrior::getPosition(void) const
{
  return (_pos);
}

void	Warrior::setPosition(irr::core::vector3df const& pos)
{
  _pos = pos;
  for (auto& it : _warriorActualMeshs)
    (*it).getMesh()->setPosition(_pos);
}

void	Warrior::animateEntitySelect(void)
{
  if (_select)
    {
      _pos.Z -= 40 * _core->getFrameDeltaTime();
      setPosition(_pos);
      if (_warriorActualMeshs[0]->getMesh()->getFrameNr() >= 30)
	_select = false;
    }
}

void	Warrior::animateEntityAttack(void)
{
  if (_attack)
    {
      if (_warriorActualMeshs[0]->getMesh()->getFrameNr() >= 28)
	{
	  setActualMeshs(1);
	  setAnimation(false, false, ATTACK);
	  _isActive = true;
	}
    }
}

void	Warrior::animateEntityDeath(void)
{
  if (_death)
    {
      _rot.X -= 100 * _core->getFrameDeltaTime();
      setRotation(_rot);
      if (_warriorActualMeshs[0]->getMesh()->getRotation().X <= -90)
	setAnimation(false, false, DEATH);
    }
}

void	Warrior::animateKnockBack(void)
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

void	Warrior::setKnockBack(irr::core::position2d<irr::s32> const& knockback)
{
  _knockback = true;
  if (knockback.X == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(_pos.X, knockback.Y);
  else if (knockback.Y == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(knockback.X, _pos.Z);
  _isActive = false;
}

irr::core::position2d<irr::s32> const	Warrior::getAttackKnockback(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::position2d<irr::s32>(0, _pos.Z - (_damage * 3)));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::position2d<irr::s32>(_pos.X - (_damage * 3), 0));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::position2d<irr::s32>(0, _pos.Z + (_damage * 3)));
  return (irr::core::position2d<irr::s32>(_pos.X + (_damage * 3), 0));
}

bool	Warrior::hitbox(irr::core::rect<irr::s32> rect) const
{
  return (rect.isPointInside(irr::core::position2d<irr::s32>(_pos.X, _pos.Z)));
}

bool	Warrior::isActive(void) const
{
  return (_isActive);
}

irr::core::vector3df const&   Warrior::getRotation(void) const
{
  return (_rot);
}

void	Warrior::setRotation(irr::core::vector3df const& rot)
{
  _rot = rot;
  for (auto& it : _warriorActualMeshs)
    (*it).getMesh()->setRotation(_rot);
}

irr::core::rect<irr::s32>	Warrior::getAttackRect(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::rect<irr::s32>(_pos.X + 50, _pos.Z, _pos.X - 50, _pos.Z - _range));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::rect<irr::s32>(_pos.X - _range, _pos.Z + 50, _pos.X, _pos.Z - 50));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::rect<irr::s32>(_pos.X - 50, _pos.Z + _range, _pos.X + 50, _pos.Z));
  return (irr::core::rect<irr::s32>(_pos.X + _range, _pos.Z - 50, _pos.X, _pos.Z + 50));
}

void	Warrior::setEntityID(unsigned int const entityID)
{
  _entityID = entityID;
}

void	Warrior::clearActualMeshs()
{
  int	i = _warriorActualMeshs.size() - 1;

  while (i >= 0)
    {
      if (((_core->getScene())->getSceneNodeFromId(_warriorActualMeshs[i]->getID())))
	(_core->getScene())->getSceneNodeFromId(_warriorActualMeshs[i]->getID())->remove();
      --i;
    }
  _warriorActualMeshs.clear();
}

void	Warrior::setActualMeshs(unsigned int id)
{
  _actualMeshID = id;
  clearActualMeshs();
  unsigned int i = (id * _meshNbr);
  _warriorActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID, _warriorMeshs[i].c_str(), "./resources/Mesh/Warrior/Warrior.png",
								     _pos, irr::core::vector3df(8, 8, 8), _rot), _entityID, _core));
  ++i;
  _warriorActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID + 1, _warriorMeshs[i].c_str(), "./resources/Mesh/Warrior/Axe.png",
								     _pos, irr::core::vector3df(8, 8, 8), _rot), _entityID + 1, _core));
  for (unsigned int j = 0; j < 2; j++)
    {
      if (id == 1)
	{
	  _warriorActualMeshs[j]->getMesh()->setLoopMode(true);
	  _warriorActualMeshs[j]->getMesh()->setAnimationSpeed(30);
	}
      else
	{
	  _warriorActualMeshs[j]->getMesh()->setLoopMode(false);
	  _warriorActualMeshs[j]->getMesh()->setAnimationSpeed(0);
	}
    }
}

int	Warrior::getActualMeshID(void) const
{
  return (_actualMeshID);
}

void	Warrior::setNextRotation(int nextRotation)
{
  if (nextRotation == 0 && _rot.Y == 270)
    _nextRotation = 360;
  else
    _nextRotation = nextRotation;
}

void	Warrior::rotate(void)
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

void					Warrior::AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df wizardPos,
					   irr::core::vector3df elfPos)
{
  (void)warriorPos;
  (void)valkPos;
  (void)wizardPos;
  (void)elfPos;
}
