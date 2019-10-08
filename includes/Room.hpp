//
// Room.hpp for Room.hpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Tue May  9 18:21:20 2017 Anthony
// Last update Sun Jun 18 22:38:11 2017 Mex
//

#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <vector>
# include "Monster.hpp"

class					Room
{
public:
  Room(Core *core, unsigned int ID, unsigned int roomNbr, irr::core::vector3df startPos);
  ~Room();

public:
  enum					LEVEL_STATE
    {
      ACTUAL_ROOM = 0,
      ROOM_CLEAR = 1,
      NEXT_ROOM = 2,
      NEXT_LEVEL = 3,
    };
  
public:
  unsigned int				getRoomID(void) const;
  void					setTerrain(irr::scene::ITerrainSceneNode* terrain);
  irr::core::vector3df const&		getStartPos(void) const;
  void					setStartPos(irr::core::vector3df const& startPos);
  irr::core::position2d<irr::f32>	getSize(void) const;
  void					setSize(irr::core::position2d<irr::f32> const& size);
  void					setCatwalk(irr::core::vector3df const& catwalkPos, irr::core::position2d<irr::f32> const& catwalkSize);
  irr::core::vector3df const&		getEndPos(void) const;
  void					setEndPos(irr::core::vector3df const& endPos);
  void					setIsActive(bool const& isActive);
  std::vector<IEntity*> const		getMonstersHit(irr::core::rect<irr::s32> rect);
  LEVEL_STATE				run(irr::IrrlichtDevice* device, Player* player);
  void					endAnimation(irr::IrrlichtDevice* device);
  void					initMonsters(unsigned int monsterNbr);
  void					spawnMonsters(void);
  void					refreshMonstersNbr(void);
  bool					hitbox(Player* player) const;
  bool					hitbox(IEntity* Monster) const;
  void					AIPool(irr::core::vector3df const& player1, irr::core::vector3df const& player2,
					       irr::core::vector3df const& player3, irr::core::vector3df const& player4);

private:
  Core*					_core;
  unsigned int				_ID;
  unsigned int				_roomNbr;
  irr::scene::ITerrainSceneNode*	_terrain;
  irr::core::vector3df			_pos;
  irr::core::vector3df			_startPos;
  irr::core::vector3df			_endPos;
  irr::core::position2d<irr::f32>	_size;
  irr::core::vector3df			_catwalkPos;
  irr::core::position2d<irr::f32>	_catwalkSize;
  bool					_isActive;
  bool					_endAnimation;
  bool					_deathAnimation;
  bool					_roomClear;
  bool					_endRoom;
  irr::u32				_then;
  std::vector<IEntity*>			_monsterPool;
  int					_monsterMaxNbr;
  int					_monsterNbr;
};

#endif /* ROOM_HPP_ */
