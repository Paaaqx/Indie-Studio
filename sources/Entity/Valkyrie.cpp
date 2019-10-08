//
// Valkyrie.cpp for Valkyrie.cpp in /home/paqx/Rendu/cpp_indie_studio/sources/Entity
//
// Made by Paqx
// Login   <louis.paquet@epitech.eu>
//
// Started on  Thu Jun 15 13:12:55 2017 Paqx
// Last update Sun Jun 18 22:29:23 2017 Paqx
//


#include "Valkyrie.hpp"

Valkyrie::Valkyrie(Core *core, irr::core::vector3df pos)
{
  _core = core;
  _pos = pos;
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectArm.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectCap.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectChest.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectChestPlate.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectForeArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectHands.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectHead.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectHelmetMail.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectHelmet.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectLegArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectLegs.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectShell.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectShoes.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectSholder.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/SelectSword.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkArm.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkCap.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkChest.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkChestPlate.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkForeArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkHand.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkHead.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkHelmetMail.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkHelmet.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkLegArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkLegs.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkShell.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkShoes.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkSholder.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/WalkSword.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackArm.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackCap.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackChest.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackChestPlate.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackForeArmArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackHands.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackHead.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackHelmetMail.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackHelmet.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackLegArmor.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackLegs.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackShell.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackShoes.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackSholder.md3");
  _valkyrieMeshs.emplace_back("./resources/Mesh/Valkyrie/AttackSword.md3");
  _meshNbr = 16;
  _actualMeshID = -1;
  _select = false;
  _attack = false;
  _death = false;
  _maxLifePoint = 600;
  _lifePoint = _maxLifePoint;
  _damage = 150;
  _range = 130;
  _defense = 30;
  _speed = 275;
  _entityID = 20;
  _nextRotation = std::numeric_limits<int>::min();
  _isActive = true;
  _knockback = false;
}

Valkyrie::~Valkyrie()
{
  _valkyrieMeshs.clear();
  clearActualMeshs();
}

void	Valkyrie::run(void)
{
  animateEntityAttack();
  animateEntityDeath();
  animateKnockBack();
  rotate();
}

void	Valkyrie::move(void)
{
}

int	Valkyrie::getMaxLifePoint(void) const
{
  return (_maxLifePoint);
}

void	Valkyrie::setMaxLifePoint(int maxLifePoint)
{
  _maxLifePoint = maxLifePoint;
}

int	Valkyrie::getLifePoint(void) const
{
  return (_lifePoint);
}

void	Valkyrie::setLifePoint(int lifePoint)
{
  _lifePoint = lifePoint;
  if (_lifePoint <= 0 && !_death && _isActive)
    {
      _isActive = false;
      setAnimation(true, false, DEATH);
    }
}

unsigned int	Valkyrie::getDamage(void) const
{
  return (_damage);
}

void	Valkyrie::setDamage(unsigned int damage)
{
  _damage = damage;
}

void	Valkyrie::setRange(unsigned int range)
{
  _range = range;
}

unsigned int	Valkyrie::getRange(void) const
{
  return (_range);
}

unsigned int	Valkyrie::getDefense(void) const
{
  return (_defense);
}

void	Valkyrie::setDefense(unsigned int defense)
{
  _defense = defense;
}

unsigned int	Valkyrie::getSpeed(void) const
{
  return (_speed);
}

void	Valkyrie::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void	Valkyrie::setAnimation(bool state, bool loopMode, AnimationType type)
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
      for (auto& it : _valkyrieActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(30);
	  (*it).getMesh()->setLoopMode(loopMode);
	}
    }
  else
    {
      for (auto& it : _valkyrieActualMeshs)
	{
	  (*it).getMesh()->setAnimationSpeed(0);
	  (*it).getMesh()->setLoopMode(false);
	}
    }
}

irr::core::vector3df const&	Valkyrie::getPosition(void) const
{
  return (_pos);
}

void	Valkyrie::setPosition(irr::core::vector3df const& pos)
{
  _pos = pos;
  for (auto& it : _valkyrieActualMeshs)
    (*it).getMesh()->setPosition(_pos);
}

void	Valkyrie::animateEntitySelect(void)
{
  if (_select)
    {
      setPosition(_pos);
      if (_valkyrieActualMeshs[0]->getMesh()->getFrameNr() >= 60)
	_select = false;
    }
}

void	Valkyrie::animateEntityAttack(void)
{
  if (_attack)
    {
      if (_valkyrieActualMeshs[0]->getMesh()->getFrameNr() >= 34)
	{
	  setActualMeshs(1);
	  setAnimation(false, false, ATTACK);
	  _isActive = true;
	}
    }
}

void	Valkyrie::animateEntityDeath(void)
{
  if (_death)
    {
      _rot.X -= 100 * _core->getFrameDeltaTime();
      setRotation(_rot);
      if (_valkyrieActualMeshs[0]->getMesh()->getRotation().X <= -90)
	setAnimation(false, false, DEATH);
    }
}

void	Valkyrie::animateKnockBack(void)
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

void	Valkyrie::setKnockBack(irr::core::position2d<irr::s32> const& knockback)
{
  _knockback = true;
  if (knockback.X == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(_pos.X, knockback.Y);
  else if (knockback.Y == 0)
    _knockbackPos = irr::core::position2d<irr::s32>(knockback.X, _pos.Z);
  _isActive = false;
}

irr::core::position2d<irr::s32> const	Valkyrie::getAttackKnockback(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::position2d<irr::s32>(0, _pos.Z - (_damage * 2)));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::position2d<irr::s32>(_pos.X - (_damage * 2), 0));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::position2d<irr::s32>(0, _pos.Z + (_damage * 2)));
  return (irr::core::position2d<irr::s32>(_pos.X + (_damage * 2), 0));
}

bool	Valkyrie::hitbox(irr::core::rect<irr::s32> rect) const
{
  rect.repair();
  return (rect.isPointInside(irr::core::position2d<irr::s32>(_pos.X, _pos.Z)));
}

irr::core::vector3df const&   Valkyrie::getRotation(void) const
{
  return (_rot);
}

void	Valkyrie::setRotation(irr::core::vector3df const& rot)
{
  _rot = rot;
  for (auto& it : _valkyrieActualMeshs)
    (*it).getMesh()->setRotation(_rot);
}

irr::core::rect<irr::s32>       Valkyrie::getAttackRect(void)
{
  if (_rot.Y >= 0 && _rot.Y <= 45)
    return (irr::core::rect<irr::s32>(_pos.X + 60, _pos.Z + 10, _pos.X - 60, _pos.Z - _range));
  else if (_rot.Y >= 45 && _rot.Y <= 135)
    return (irr::core::rect<irr::s32>(_pos.X - _range, _pos.Z + 60, _pos.X - 10, _pos.Z - 50));
  else if (_rot.Y >= 135 && _rot.Y <= 215)
    return (irr::core::rect<irr::s32>(_pos.X - 60, _pos.Z + _range, _pos.X + 60, _pos.Z - 10));
  return (irr::core::rect<irr::s32>(_pos.X + _range, _pos.Z - 60, _pos.X + 10, _pos.Z + 60));
}

bool    Valkyrie::isActive(void) const
{
  return (_isActive);
}

void	Valkyrie::setEntityID(unsigned int const entityID)
{
  _entityID = entityID;
}

void	Valkyrie::clearActualMeshs()
{
  int	i = _valkyrieActualMeshs.size() - 1;

  while (i >= 0)
    {
      if (((_core->getScene())->getSceneNodeFromId(_valkyrieActualMeshs[i]->getID())))
	(_core->getScene())->getSceneNodeFromId(_valkyrieActualMeshs[i]->getID())->remove();
      --i;
    }
  _valkyrieActualMeshs.clear();
}

void	Valkyrie::setActualMeshs(unsigned int id)
{
  _actualMeshID = id;
  clearActualMeshs();
  std::vector<std::string> textures = {"./resources/Mesh/Valkyrie/Textures/PlateArmourArmArmour.jpg", "./resources/Mesh/Valkyrie/Textures/ChainmailArms.jpg",
				       "./resources/Mesh/Valkyrie/Textures/RedCape.jpg", "./resources/Mesh/Valkyrie/Textures/ChainmailTorso.jpg",
				       "./resources/Mesh/Valkyrie/Textures/SilveralTorso.jpg","./resources/Mesh/Valkyrie/Textures/SilveralWristArmour(uses Druid Wrist).jpg",
				       "./resources/Mesh/Valkyrie/Textures/GlovesLeather.jpg", "./resources/Mesh/Valkyrie/Textures/MDFheadH.jpg",
				       "./resources/Mesh/Valkyrie/Textures/ChainMailHood.png", "./resources/Mesh/Valkyrie/Textures/SilveralHelmetFemale.jpg",
				       "./resources/Mesh/Valkyrie/Textures/SilveralLegs.jpg", "./resources/Mesh/Valkyrie/Textures/ChainmailLegs.jpg",
				       "./resources/Mesh/Valkyrie/Textures/SilveralHiPChainmail.jpg", "./resources/Mesh/Valkyrie/Textures/SilverallBoots.jpg",
				       "./resources/Mesh/Valkyrie/Textures/PLateArmourShoulderPads.jpg", "./resources/Mesh/Valkyrie/Textures/SilveralSword.jpg"};
  unsigned int i = (id * _meshNbr);
  for (unsigned int j = 0; j < 16; ++j, ++i)
    {
      _valkyrieActualMeshs.emplace_back(new MeshManager(_core->getNewMesh(_entityID + j, _valkyrieMeshs[i].c_str(), textures[j].c_str(), _pos,irr::core::vector3df(60, 60, 60), _rot)
							,_entityID + j , _core));
      if (id == 1)
	{
	  _valkyrieActualMeshs[j]->getMesh()->setLoopMode(true);
	  _valkyrieActualMeshs[j]->getMesh()->setAnimationSpeed(30);
	}
      else
	{
	  _valkyrieActualMeshs[j]->getMesh()->setLoopMode(false);
	  _valkyrieActualMeshs[j]->getMesh()->setAnimationSpeed(0);
	}
    }
  textures.clear();
}

int	Valkyrie::getActualMeshID(void) const
{
  return (_actualMeshID);
}

void	Valkyrie::setNextRotation(int nextRotation)
{
  _nextRotation = nextRotation;
}

void	Valkyrie::rotate(void)
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

void					Valkyrie::AI(irr::core::vector3df warriorPos,
					   irr::core::vector3df valkPos,
					   irr::core::vector3df wizardPos,
					   irr::core::vector3df elfPos)
{
  (void)warriorPos;
  (void)valkPos;
  (void)wizardPos;
  (void)elfPos;
}
