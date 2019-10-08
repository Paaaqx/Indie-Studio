//
// Elf.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Tue Jun  6 15:53:06 2017 Mex
// Last update Sun Jun 18 22:29:01 2017 Paqx
//

#include "Elf.hpp"

Elf::Elf(Core *core, irr::core::vector3df pos)
{
  _core = core;
  _pos = pos;
  // _elfMeshs.emplace_back("./resources/Mesh/Elf/SelectFace.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/SelectBody.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/SelectBow.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/SelectQuiver.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/SelectHair.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/WalkFace.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/WalkBody.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/WalkBow.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/WalkQuiver.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/WalkHair.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/AttackFace.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/AttackBody.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/AttackBow.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/AttackQuiver.md3");
  _elfMeshs.emplace_back("./resources/Mesh/Elf/AttackHair.md3");
  _meshNbr = 5;
  _actualMeshID = -1;
  _select = false;
  _attack = false;
  _death = false;
  _maxLifePoint = 300;
  _lifePoint = _maxLifePoint;
  _damage = 100;
  _range = 300;
  _defense = 15;
  _speed = 350;
  _entityID = 50;
  _nextRotation = std::numeric_limits<int>::min();
  _isActive = true;
  _knockback = false;
}

Elf::~Elf()
{
  _elfMeshs.clear();
  clearActualMeshs();
}

void	Elf::run(void)
{
  animateEntityAttack();
  animateEntityDeath();
  animateKnockBack();
  rotate();
}

void	Elf::move(void)
{
}

int	Elf::getMaxLifePoint(void) const
{
  return (_maxLifePoint);
}

void	Elf::setMaxLifePoint(int maxLifePoint)
{
  _maxLifePoint = maxLifePoint;
}

int	Elf::getLifePoint(void) const
{
  return (_lifePoint);
}

void	Elf::setLifePoint(int lifePoint)
{
  _lifePoint = lifePoint;
  if (_lifePoint <= 0 && _isActive && !_death)
    {
      setAnimation(true, false, DEATH);
      _isActive = false;
    }
}

unsigned int	Elf::getDamage(void) const
{
  return (_damage);
}

void	Elf::setDamage(unsigned int damage)
{
  _damage = damage;
}

void	Elf::setRange(unsigned int range)
{
  _range = range;
}

unsigned int	Elf::getRange(void) const
{
  return (_range);
}

unsigned int	Elf::getDefense(void) const
{
  return (_defense);
}

void	Elf::setDefense(unsigned int defense)
{
  _defense = defense;
}

unsigned int	Elf::getSpeed(void) const
{
  return (_speed);
}

void	Elf::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void	Elf::setAnimation(bool state, bool loopMode, AnimationType type)
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
      for (auto& it : _elfActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(80);
	  (*it).getMesh()->setLoopMode(loopMode);
	}
    }
  else
    {
      for (auto& it : _elfActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(0);
	  (*it).getMesh()->setLoopMode(false);
	}
    }
}

irr::core::vector3df const&	Elf::getPosition(void) const
{
  return (_pos);
}

void	Elf::setPosition(irr::core::vector3df const& pos)
{
  _pos = pos;
  for (auto& it : _elfActualMeshs)
    (*it).getMesh()->setPosition(_pos);
}

void	Elf::animateEntitySelect(void)
{
  if (_select)
    {
      _pos.Z -= 25 * _core->getFrameDeltaTime();
      setPosition(_pos);
      if (_elfActualMeshs[0]->getMesh()->getFrameNr() >= 60)
	_select = false;
    }
}

void	Elf::animateEntityAttack(void)
{
  if (_attack)
    {
      if (_elfActualMeshs[0]->getMesh()->getFrameNr() >= 55)
	{
	  setActualMeshs(1);
	  setAnimation(false, false, ATTACK);
	  _isActive = true;
	}
    }
}

void	Elf::animateEntityDeath(void)
{
  if (_death)
    {
      _rot.X -= 100 * _core->getFrameDeltaTime();
      setRotation(_rot);
      if (_elfActualMeshs[0]->getMesh()->getRotation().X <= -90)
	setAnimation(false, false, DEATH);
    }
}

void	Elf::animateKnockBack(void)
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

void	Elf::setKnockBack(irr::core::position2d<irr::s32> const& knockback)
{
  _knockback = true;
  if (knockback.X == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(_pos.X, knockback.Y);
  else if (knockback.Y == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(knockback.X, _pos.Z);
  _isActive = false;
}

irr::core::position2d<irr::s32> const	Elf::getAttackKnockback(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::position2d<irr::s32>(0, _pos.Z - (_damage * 3)));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::position2d<irr::s32>(_pos.X - (_damage * 3), 0));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::position2d<irr::s32>(0, _pos.Z + (_damage * 3)));
  return (irr::core::position2d<irr::s32>(_pos.X + (_damage * 3), 0));
}

bool	Elf::hitbox(irr::core::rect<irr::s32> rect) const
{
  rect.repair();
  return (rect.isPointInside(irr::core::position2d<irr::s32>(_pos.X, _pos.Z)));
}

irr::core::vector3df const&   Elf::getRotation(void) const
{
  return (_rot);
}

void	Elf::setRotation(irr::core::vector3df const& rot)
{
  _rot = rot;
  for (auto& it : _elfActualMeshs)
    (*it).getMesh()->setRotation(_rot);
}

bool	Elf::isActive(void) const
{
  return (_isActive);
}

irr::core::rect<irr::s32>	Elf::getAttackRect(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::rect<irr::s32>(_pos.X + 60, _pos.Z + 10, _pos.X - 60, _pos.Z - _range));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::rect<irr::s32>(_pos.X - _range, _pos.Z + 60, _pos.X - 10, _pos.Z - 50));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::rect<irr::s32>(_pos.X - 60, _pos.Z + _range, _pos.X + 60, _pos.Z - 10));
  return (irr::core::rect<irr::s32>(_pos.X + _range, _pos.Z - 60, _pos.X + 10, _pos.Z + 60));
}

void	Elf::setEntityID(unsigned int const entityID)
{
  _entityID = entityID;
}

void	Elf::clearActualMeshs()
{
  int	i = _elfActualMeshs.size() - 1;

  while (i >= 0)
    {
      if (((_core->getScene())->getSceneNodeFromId(_elfActualMeshs[i]->getID())))
	(_core->getScene())->getSceneNodeFromId(_elfActualMeshs[i]->getID())->remove();
      --i;
    }
  _elfActualMeshs.clear();
}

void	Elf::setActualMeshs(unsigned int id)
{
  _actualMeshID = id;
  clearActualMeshs();
  std::vector<std::string> textures = { "./resources/Mesh/Elf/body.png", "./resources/Mesh/Elf/bowQuiver.png",
					"./resources/Mesh/Elf/bowQuiver.png", "./resources/Mesh/Elf/hair.png"};
  unsigned int i = (id * _meshNbr);
  for (unsigned int j = 0; j < 4; j++, ++i)
    {
      _elfActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID + j, _elfMeshs[i].c_str(), textures[j].c_str(), _pos,irr::core::vector3df(0.60, 0.60, 0.60), _rot)
						   ,_entityID + j , _core));
      if (id == 1)
	{
	  _elfActualMeshs[j]->getMesh()->setLoopMode(true);
	  _elfActualMeshs[j]->getMesh()->setAnimationSpeed(120);
	}
      else
	{
	  _elfActualMeshs[j]->getMesh()->setLoopMode(false);
	  _elfActualMeshs[j]->getMesh()->setAnimationSpeed(0);
	}
    }
  _elfActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID, "./resources/Mesh/Elf/SelectFace.md3",  "./resources/Mesh/Elf/face.png", _pos,irr::core::vector3df(0.60, 0.60, 0.60), _rot)
					       ,_entityID, _core));
    textures.clear();
}

int	Elf::getActualMeshID(void) const
{
  return (_actualMeshID);
}

void	Elf::setNextRotation(int nextRotation)
{
  _nextRotation = nextRotation;
}

void	Elf::rotate(void)
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

void					Elf::AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df wizardPos,
					   irr::core::vector3df elfPos)
{
  (void)warriorPos;
  (void)valkPos;
  (void)wizardPos;
  (void)elfPos;
}
