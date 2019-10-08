//
// Monster.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Fri Jun 16 05:06:28 2017 Mex
// Last update Sun Jun 18 22:22:29 2017 Paqx
//

#include "Monster.hpp"

Monster::Monster(Core *core, irr::core::vector3df pos)
{
  _core = core;
  _pos = pos;
  _monsterMeshs.emplace_back("./resources/Mesh/Monster/Walk.md3");
  _monsterMeshs.emplace_back("./resources/Mesh/Monster/Attack.md3");
  _monsterMeshs.emplace_back("./resources/Mesh/Monster/Death.md3");
  _meshNbr = 1;
  _actualMeshID = -1;
  _select = false;
  _attack = false;
  _death = false;
  _attacking  = false;
  _isActive = true;
  _maxLifePoint = 400;
  _lifePoint = _maxLifePoint;
  _damage = 100;
  _range = 15;
  _defense = 50;
  _speed = 200;
  _nextRotation = std::numeric_limits<int>::min();
  _entityID = 200;
  _knockback = false;
  _target = chooseTarget();
}

Monster::~Monster()
{
  _monsterMeshs.clear();
  _monsterActualMeshs.clear();
}

int	Monster::chooseTarget()
{
  static std::random_device			rd;
  static std::mt19937				eng(rd());
  std::uniform_int_distribution<int>		distr(0, 3);

  return (distr(eng));
}

void	Monster::run(void)
{
  animateEntityAttack();
  animateEntityDeath();
  animateKnockBack();
  rotate();
}

void	Monster::move(void)
{
}

int	Monster::getMaxLifePoint(void) const
{
  return (_maxLifePoint);
}

void	Monster::setMaxLifePoint(int maxLifePoint)
{
  _maxLifePoint = maxLifePoint;
}

int	Monster::getLifePoint(void) const
{
  return (_lifePoint);
}

void	Monster::setLifePoint(int lifePoint)
{
  _lifePoint = lifePoint;
  if (_lifePoint <= 0 && !_death)
    {
      setActualMeshs(2);
      setAnimation(true, true, DEATH);
      _isActive = false;
    }
}

unsigned int	Monster::getDamage(void) const
{
  return (_damage);
}

void	Monster::setDamage(unsigned int damage)
{
  _damage = damage;
}

void	Monster::setRange(unsigned int range)
{
  _range = range;
}

unsigned int	Monster::getRange(void) const
{
  return (_range);
}

unsigned int	Monster::getDefense(void) const
{
  return (_defense);
}

void	Monster::setDefense(unsigned int defense)
{
  _defense = defense;
}

unsigned int	Monster::getSpeed(void) const
{
  return (_speed);
}

void	Monster::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void	Monster::setAnimation(bool state, bool loopMode, AnimationType type)
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
      break;
    case DEATH:
      _death = state;
      break;
    }
  if (state)
    {
      for (auto& it : _monsterActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(30);
	  (*it).getMesh()->setLoopMode(loopMode);
	}
    }
  else
    {
      for (auto& it : _monsterActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(0);
	  (*it).getMesh()->setLoopMode(false);
	}
    }
}

irr::core::vector3df const&	Monster::getPosition(void) const
{
  return (_pos);
}

void	Monster::setPosition(irr::core::vector3df const& pos)
{
  _pos = pos;
  for (auto& it : _monsterActualMeshs)
    (*it).getMesh()->setPosition(_pos);
}

void	Monster::animateEntityAttack(void)
{
  if (_attack)
    {
      if (_monsterActualMeshs[0]->getMesh()->getFrameNr() >= 90)
	{
	  setActualMeshs(0);
	  setAnimation(false, false, ATTACK);
	}
    }
}

void	Monster::animateEntityDeath(void)
{
  if (_death)
    {
      if (_monsterActualMeshs[0]->getMesh()->getFrameNr() >= 120)
	{
	  setAnimation(false, false, DEATH);
	  clearActualMeshs();
	}
    }
}

void	Monster::animateKnockBack(void)
{
  if (_knockback && _lifePoint > 0)
    {
      _pos.X = (irr::s32)_pos.X;
      _pos.Z = (irr::s32)_pos.Z;
      if (_pos.X > _knockbackPos.X)
	_pos.X -= (300 * _core->getFrameDeltaTime());
      else if (_pos.X < _knockbackPos.X)
	_pos.X += (300 * _core->getFrameDeltaTime());
      else if (_pos.Z > _knockbackPos.Y)
	_pos.Z -= (300 * _core->getFrameDeltaTime());
      else
	_pos.Z += (300 * _core->getFrameDeltaTime());
      setPosition(_pos);
      if ((_pos.X >=  _knockbackPos.X - 15 && _pos.X <= _knockbackPos.X + 15)
	  && (_pos.Z >=_knockbackPos.Y - 15 && _pos.Z <= _knockbackPos.Y + 15))
	{
	  _knockback = false;
	  _isActive = true;
	}
    }
}

void	Monster::setKnockBack(irr::core::position2d<irr::s32> const& knockback)
{
  _knockback = true;
  if (knockback.X == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(_pos.X, knockback.Y);
  else if (knockback.Y == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(knockback.X, _pos.Z);
  _isActive = false;
}

irr::core::position2d<irr::s32> const	Monster::getAttackKnockback(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::position2d<irr::s32>(0, _pos.Z - (_damage * 3)));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::position2d<irr::s32>(_pos.X - (_damage * 3), 0));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::position2d<irr::s32>(0, _pos.Z + (_damage * 3)));
  return (irr::core::position2d<irr::s32>(_pos.X + (_damage * 3), 0));
}

bool	Monster::hitbox(irr::core::rect<irr::s32> rect) const
{
  rect.repair();
  return (rect.isPointInside(irr::core::position2d<irr::s32>(_pos.X, _pos.Z)));
}

irr::core::vector3df const&   Monster::getRotation(void) const
{
  return (_rot);
}

void	Monster::setRotation(irr::core::vector3df const& rot)
{
  _rot = rot;
  for (auto& it : _monsterActualMeshs)
    (*it).getMesh()->setRotation(_rot);
}

irr::core::rect<irr::s32>	Monster::getAttackRect(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::rect<irr::s32>(_pos.X + 5, _pos.Z + 10, _pos.X - 5, _pos.Z));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::rect<irr::s32>(_pos.X - 10, _pos.Z + 5, _pos.X, _pos.Z - 5));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::rect<irr::s32>(_pos.X - 5, _pos.Z - 10, _pos.X + 5, _pos.Z));
  return (irr::core::rect<irr::s32>(_pos.X + 10, _pos.Z - 5, _pos.X, _pos.Z + 5));
}

void	Monster::setEntityID(unsigned int const entityID)
{
  _entityID = entityID;
}

void	Monster::clearActualMeshs()
{
  if (_monsterActualMeshs.size() != 0)
    {
      if (((_core->getScene())->getSceneNodeFromId(_monsterActualMeshs[0]->getID())))
	(_core->getScene())->getSceneNodeFromId(_monsterActualMeshs[0]->getID())->remove();
      _monsterActualMeshs.clear();
    }
}

void	Monster::setActualMeshs(unsigned int id)
{
  _actualMeshID = id;
  clearActualMeshs();
  unsigned int i = (id * _meshNbr);
  _monsterActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID, _monsterMeshs[i].c_str(), "./resources/Mesh/Monster/Monster.png",
								     _pos, irr::core::vector3df(8, 8, 8), _rot), _entityID, _core));
  if (id == 1)
    {
      _monsterActualMeshs[0]->getMesh()->setLoopMode(true);
      _monsterActualMeshs[0]->getMesh()->setAnimationSpeed(30);
    }
  else
    {
      _monsterActualMeshs[0]->getMesh()->setLoopMode(false);
      _monsterActualMeshs[0]->getMesh()->setAnimationSpeed(0);
    }
}

int	Monster::getActualMeshID(void) const
{
  return (_actualMeshID);
}

void	Monster::setNextRotation(int nextRotation)
{
  if (nextRotation == 0 && _rot.Y == 270)
    _nextRotation = 360;
  else
    _nextRotation = nextRotation;
}

bool	Monster::isActive(void) const
{
  return (_isActive);
}

void	Monster::rotate(void)
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

void					Monster::AI(irr::core::vector3df warriorPos,
					    irr::core::vector3df valkPos,
					    irr::core::vector3df wizardPos,
					    irr::core::vector3df elfPos)
{
  std::vector<irr::core::vector3df>	targets;
  irr::core::vector3df			distance;
  irr::u32				timestart;

  targets.emplace_back(warriorPos);
  targets.emplace_back(valkPos);
  targets.emplace_back(wizardPos);
  targets.emplace_back(elfPos);
  if (getLifePoint() > 0)
    {
      distance.X = (this->_pos.X - targets[_target].X) / 2;
      distance.Z = (this->_pos.Z - targets[_target].Z) / 2;
      if (_attacking == false)
	{
	  this->_time = this->_core->getDevice()->getTimer()->getTime();
	  _attacking = true;
	}
      else
	timestart = this->_core->getDevice()->getTimer()->getTime();
      if ((distance.X >= -40 && distance.X <= 40) && (distance.Z >= -40 && distance.Z <= 40))
	{
	  if (timestart - this->_time > 100)
	    {
	      this->setActualMeshs(1);
	      this->setAnimation(true, true, IEntity::ATTACK);
	    }
	  else
	    _attacking = false;
	}
      else
	{
	  this->setPosition((this->getPosition() - irr::core::vector3df((distance.X * _core->getFrameDeltaTime()), 0, (distance.Z * _core->getFrameDeltaTime()))));
	  this->setAnimation(true, true, IEntity::MOVE);
	}
      if (distance.X > 0)
	this->setNextRotation(90);
      if (distance.Z > 0)
	this->setNextRotation(0);
      if (distance.X < 0)
	this->setNextRotation(270);
      if (distance.Z < 0)
	this->setNextRotation(180);
      this->run();
    }
}
