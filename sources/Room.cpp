//
// Room.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Tue Jun 13 12:46:26 2017 Mex
// Last update Sun Jun 18 23:13:32 2017 Anthony
//

#include "Room.hpp"

Room::Room(Core* core, unsigned int ID, unsigned int roomNbr, irr::core::vector3df startPos)
{
  _core = core;
  _ID = ID;
  _roomNbr = roomNbr;
  _startPos = startPos;
  _isActive = false;
  _roomClear = false;
  _endRoom = false;
  _endAnimation = false;
  _then = 0;
  _monsterNbr = -1;
  _monsterMaxNbr = -1;
}

Room::~Room(){}

unsigned int	Room::getRoomID(void) const
{
  return (_ID);
}

void	Room::setTerrain(irr::scene::ITerrainSceneNode* terrain)
{
  _terrain = terrain;
}

irr::core::vector3df const&	Room::getStartPos(void) const
{
  return (_startPos);
}

void	Room::setStartPos(irr::core::vector3df const& startPos)
{
  _startPos = startPos;
}

irr::core::position2d<irr::f32>	Room::getSize(void) const
{
  return (_size);
}

void	Room::setSize(irr::core::position2d<irr::f32> const& size)
{
  _size = size;
}

void	Room::setCatwalk(irr::core::vector3df const& catwalkPos, irr::core::position2d<irr::f32> const& catwalkSize)
{
  _catwalkPos = catwalkPos;
  _catwalkSize = catwalkSize;
}

irr::core::vector3df const&	Room::getEndPos(void) const
{
  return (_endPos);
}

void	Room::setEndPos(irr::core::vector3df const& endPos)
{
  _endPos = endPos;
}

void	Room::setIsActive(bool const& isActive)
{
  _isActive = isActive;
}

std::vector<IEntity*> const	Room::getMonstersHit(irr::core::rect<irr::s32> rect)
{
  std::vector<IEntity*>		vec;
  refreshMonstersNbr();
  for (int i = 0; i < _monsterMaxNbr; i++)
    if ((_monsterPool[i]->hitbox(rect) == true) && _monsterPool[i]->isActive())
      vec.emplace_back(_monsterPool[i]);
  return (vec);
}

void			Room::initMonsters(unsigned int monsterNbr)
{
  irr::core::vector3df	pos = irr::core::vector3df(_startPos.X + (_size.X / 1.5), 0, _startPos.Z + _size.Y / 1.5);

  _monsterMaxNbr = monsterNbr;
  _monsterNbr = _monsterMaxNbr;
  for (int i = 0; i < _monsterMaxNbr; i++, pos.Z -= 80)
    _monsterPool.emplace_back(new Monster(_core, irr::core::vector3df(pos.X, pos.Y, pos.Z)));
}

void			Room::spawnMonsters(void)
{
  unsigned int		id = 200;

  for (auto& it : _monsterPool)
    {
      (*it).setEntityID(id);
      (*it).setActualMeshs(1);
      (*it).setRotation(irr::core::vector3df((*it).getRotation().X, 90, (*it).getRotation().Z));
      ++id;
    }
}

void		Room::refreshMonstersNbr(void)
{
  unsigned int	nbr = 0;
  for (auto& it : _monsterPool)
    if ((*it).getLifePoint() > 0)
      ++nbr;
  _monsterNbr = nbr;
}

bool	Room::hitbox(IEntity* monster) const
{
  if ((monster->getLifePoint()) > 0)
    {
      irr::core::vector3df monsterPos = monster->getPosition();
      irr::core::rect<irr::f32> rect(_startPos.X, _startPos.Z + _size.Y, _startPos.X + _size.X, _startPos.Z);
      rect.repair();
      if (!(rect.isPointInside(irr::core::position2d<irr::f32>(monsterPos.X, monsterPos.Z))))
	return (false);
    }
  return (true);
}

bool	Room::hitbox(Player* player) const
{
  if ((player->getEntity()->getLifePoint()) > 0)
    {
      irr::core::vector3df playerPos = player->getEntity()->getPosition();
      irr::core::rect<irr::f32> rect(_startPos.X, _startPos.Z + _size.Y, _startPos.X + _size.X, _startPos.Z);
      rect.repair();
      if (_roomClear)
      	{
      	  irr::core::rect<irr::f32> rect2(_endPos.X, _endPos.Z + 240, _endPos.X + 480, _endPos.Z);
      	  rect2.repair();
	  if (!_isActive && (!(rect2.isPointInside(irr::core::position2d<irr::f32>(playerPos.X, playerPos.Z)))))
	    return (false);
      	  if (!(rect.isPointInside(irr::core::position2d<irr::f32>(playerPos.X, playerPos.Z)))
      	      && (!(rect2.isPointInside(irr::core::position2d<irr::f32>(playerPos.X, playerPos.Z)))))
	    return (false);
      	}
      else
	{
	  if (!(rect.isPointInside(irr::core::position2d<irr::f32>(playerPos.X, playerPos.Z))))
	    return (false);
	}
    }
  return (true);
}

void	Room::endAnimation(irr::IrrlichtDevice* device)
{
  if (_endAnimation)
    {
      if (_then == 0)
	_then = device->getTimer()->getTime();
      if ((device->getTimer()->getTime() - _then) >= 5000)
	{
	  _terrain->setPosition(irr::core::vector3df(_terrain->getPosition().X, _terrain->getPosition().Y - 29, _terrain->getPosition().Z));
	  _endAnimation = false;
	  _isActive = false;
	}
    }
}

void	Room::AIPool(irr::core::vector3df const& player1, irr::core::vector3df const& player2, irr::core::vector3df const& player3, irr::core::vector3df const& player4)
{
 for (auto& it : _monsterPool)
   (*it).AI(player1, player2, player3, player4);
}

Room::LEVEL_STATE	Room::run(irr::IrrlichtDevice* device, Player* player)
{
  irr::core::vector3df playerPos = player->getEntity()->getPosition();  
  for (auto& it : _monsterPool)
    {
      (*it).run();
      if ((hitbox(it)) == false)
	{
	  (*it).setLifePoint(0);
	  refreshMonstersNbr();
	}
    }
  endAnimation(device);
  if ((_monsterNbr == 0 && _roomClear == false && _ID != 1) || (_ID == 0 && _roomClear == false))
    {
      _roomClear = true;
      return (ROOM_CLEAR);
    }
  if ((playerPos.X >= _endPos.X + 300) && (playerPos.Z >= _endPos.Z) && _roomClear == true && _ID != 1 && _endRoom == false)
    {
      _endAnimation = true;
      _endRoom = true;
      return (NEXT_ROOM);
    }
  if ((playerPos.X >= _endPos.X - 400 && playerPos.X <= _endPos.X - 300) && _ID == 1)
    return (NEXT_LEVEL);
  return (ACTUAL_ROOM);
}
