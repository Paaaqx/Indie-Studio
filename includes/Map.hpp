//
// Map.hpp for Map.hpp in /home/paqx/Rendu/cpp_indie_studio/sources
//
// Made by Paqx
// Login   <louis.paquet@epitech.eu>
//
// Started on  Sat Jun 10 16:31:26 2017 Paqx
// Last update Sun Jun 18 21:37:29 2017 Mex
//

#ifndef MAP_HPP_
# define MAP_HPP_

# include <iostream>
# include <vector>
# include <map>
# include <random>
# include "Core.hpp"
# include "Room.hpp"

class Room;

class				Map
{
public:
  Map(Core* core);
  ~Map();

public:
  void				generateLevel(bool first);
  void				saveSeed(void);
  unsigned int			run(Player* player);
  Room*				getActualRoom(void) const;

private:
  void				loadSeed(void);
  void				generateMap(void);
  std::vector<int>		getSeed(void) const;
  void				deleteRoomsPool(void);
  Room&				getRoom(unsigned int ID) const;

private:
  typedef			void(Map::*methodPtr)(void);
  unsigned int			randomNumber(unsigned int min, unsigned int max);
  void				generateSeed(void);
  void				generateLava(void);
  void				initMapPool(void);
  void				generateRoom00(void);
  void				generateRoom01(void);
  void				generateRoom02(void);
  void				generateRoom03(void);
  void				generateRoom04(void);
  void				generateRoom05(void);
  void				generateRoom06(void);
  void				generateRoom07(void);
  void				generateRoom08(void);
  void				generateCatWalk(irr::core::vector3df const& pos);

private:
  Core*				_core;
  irr::scene::ISceneManager*	_smgr;
  irr::video::IVideoDriver*	_driver;
  std::map<int, methodPtr>	_generationMap;
  std::vector<Room*>		_roomsPool;
  unsigned int			miniRooms;
  unsigned int			maxRooms;
  unsigned int			mapPool;
  unsigned int			nbRooms;
  std::vector<int>		seed;
  int				lvlMultiplier;
  unsigned int			_actualRoom;
  int				tmp;
};

#endif /* !MAP_HPP */
