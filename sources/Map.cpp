//
// Map.cpp for Map.cpp in /home/paqx/Rendu/cpp_indie_studio/sources
//
// Made by1 Paqx
// Login   <louis.paquet@epitech.eu>
//
// Started on  Sat Jun 10 16:31:46 2017 Paqx
// Last update Sun Jun 18 23:13:44 2017 Anthony
//

#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "../includes/Map.hpp"

Map::Map(Core* core)
{
  _core = core;
  _driver = _core->getDriver();
  _smgr = _core->getDevice()->getSceneManager();
  _smgr->clear();
  this->miniRooms = 5;
  this->maxRooms = 15;
  this->lvlMultiplier = 1;
  this->mapPool = 8;
  _actualRoom = 0;
  initMapPool();
}

Map::~Map()
{
  deleteRoomsPool();
}

void		Map::deleteRoomsPool(void)
{
  unsigned int	size = _roomsPool.size();

  for (unsigned int i = 0; i < size; i++)
    delete _roomsPool[i];
  _roomsPool.clear();
}

void	Map::initMapPool()
{
  _generationMap.emplace(0, &Map::generateRoom00);
  _generationMap.emplace(1, &Map::generateRoom01);
  _generationMap.emplace(2, &Map::generateRoom02);
  _generationMap.emplace(3, &Map::generateRoom03);
  _generationMap.emplace(4, &Map::generateRoom04);
  _generationMap.emplace(5, &Map::generateRoom05);
  _generationMap.emplace(6, &Map::generateRoom06);
  _generationMap.emplace(7, &Map::generateRoom07);
  _generationMap.emplace(8, &Map::generateRoom08);
}

unsigned int					Map::randomNumber(unsigned int min, unsigned int max)
{
  static std::random_device			rd;
  static std::mt19937				eng(rd());
  std::uniform_int_distribution<int>		distr(min, max);

  return (distr(eng));
}

void		Map::saveSeed()
{
  std::ofstream	outfile ("./resources/save.ini", std::ios::out | std::ios::trunc);

  outfile << 'A';
  for (unsigned int i = 0; i != this->seed.size(); ++i)
    outfile << this->seed[i] << "|";
  outfile << 'A';
  outfile.close();
}

void	Map::generateSeed()
{
  this->lvlMultiplier += 0.1;
  this->nbRooms = this->randomNumber((this->miniRooms * this->lvlMultiplier), (this->maxRooms * this->lvlMultiplier));
  this->seed.clear();
  this->seed.emplace_back(0);
  for (unsigned int i = 0; i < (this->nbRooms - 2); ++i)
    this->seed.emplace_back(this->randomNumber(2, mapPool));
  this->seed.emplace_back(1);
}

void			Map::loadSeed()
{
  std::ifstream		outfile ("./resources/save.ini");
  std::string		seedFile;
  std::size_t		limits;
  std::size_t		sep = 1;

  this->seed.clear();
  std::getline(outfile, seedFile);
  limits = seedFile.find('A');
  if (limits != 0)
    {
      this->generateSeed();
      return;
    }
  limits = seedFile.find('A', 1);
  if (limits != seedFile.size() - 1)
    {
      this->generateSeed();
      return;
    }
  for(unsigned int i = 0; sep != seedFile.size() - 2; i = sep)
    {
      ++i;
      sep = seedFile.find("|", sep + 1);
      this->seed.emplace_back(stod(seedFile.substr(i, sep - i)));
    }
  if (seed.size() < miniRooms || (seed[seed.size() - 1] != 1) || (seed[0] != 0))
    {
      seed.clear();
      generateSeed();
      return;
    }
}

Room*	Map::getActualRoom(void) const
{
  return (_roomsPool[_actualRoom]);
}

void	Map::generateLevel(bool first)
{
  _actualRoom = 0;
  if (first)
    loadSeed();
  else
    generateSeed();
  saveSeed();
  nbRooms = seed.size();
  generateLava();
  deleteRoomsPool();
  for (unsigned int i = 0; i < nbRooms; i++)
    {
      (this->*_generationMap[seed[i]])();
      ++_actualRoom;
    }
  _actualRoom = 0;
  _roomsPool[_actualRoom]->setIsActive(true);
}

void				Map::generateLava(void)
{
  irr::scene::ISceneNode* skybox = _smgr->addSkyBoxSceneNode(_driver->getTexture("./resources/mp_mercury/mercury_up.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_dn.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_rt.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_lf.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_ft.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_bk.tga"));
  _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
  skybox->setVisible(true);
  tmp = 1;
  std::string string("a");
  for (unsigned int i = 0; i < 2; ++i)
    {
      irr::scene::IAnimatedMesh*	mesh = _smgr->addHillPlaneMesh(string.c_str(),
								       irr::core::dimension2d<irr::f32>(40, 15),
								       irr::core::dimension2d<irr::u32>(150, 150), 0, 0,
								       irr::core::dimension2d<irr::f32>(0, 0),
								       irr::core::dimension2d<irr::f32>(10, 10));
      irr::scene::ISceneNode*	node = _smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 2.0f, 300.0f, 30.0f);
      node->setPosition(irr::core::vector3df(125 + (2000 * tmp), -30, 0));
      node->setMaterialTexture(0, _driver->getTexture("./resources/mp_mercury/mercury_dn.tga"));
      node->setMaterialTexture(1, _driver->getTexture("./resources/water.jpg"));
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
      tmp += 3;
      string[0]++;
    }
}

void					Map::generateRoom00(void)
{
  Room*					room = new Room(_core, 0, _actualRoom, irr::core::vector3df(-360, -110, -220));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 1, 2));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/roomStart.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 3, 240 * 2));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 710, room->getStartPos().Y, room->getStartPos().Z + 120));
  _roomsPool.emplace_back(room);
}

void					Map::generateRoom01(void)
{
  Room*					room = new Room(_core, 1, _actualRoom,	irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 118));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 1, 2));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/roomEnd.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 3, 240 * 2));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 710, room->getStartPos().Y, room->getStartPos().Z + 120));
  _roomsPool.emplace_back(room);
}

void					Map::generateRoom02(void)
{
  Room*					room = new Room(_core, 2, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 118));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(4, 1, 2));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 4, 240 * 2));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 950, room->getStartPos().Y, room->getStartPos().Z + 120));
  room->initMonsters(4);
  _roomsPool.emplace_back(room);
}

void					Map::generateRoom03(void)
{
  Room*					room = new Room(_core, 3, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 118));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(2.5, 1, 4));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 2.5, 240 * 4));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 590, room->getStartPos().Y, room->getStartPos().Z + 580));
  room->initMonsters(5);
  _roomsPool.emplace_back(room);
}

void					Map::generateRoom04(void)
{
  Room*					room = new Room(_core, 4, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 600));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(2.5, 1, 4));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 2.5, 240 * 4));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 590, room->getStartPos().Y, room->getStartPos().Z + 120));
  room->initMonsters(5);
  _roomsPool.emplace_back(room);
}

void	Map::generateRoom05(void)
{
  Room*					room = new Room(_core, 5, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 118));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(5, 1, 5));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 5, 240 * 5));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 1190, room->getStartPos().Y, room->getStartPos().Z + 880));
  room->initMonsters(7);
  _roomsPool.emplace_back(room);
}

void	Map::generateRoom06(void)
{
  Room*					room = new Room(_core, 6, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 900));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(5, 1, 5));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 5, 240 * 5));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 1190, room->getStartPos().Y, room->getStartPos().Z + 120));
  room->initMonsters(7);
  _roomsPool.emplace_back(room);
}

void	Map::generateRoom07(void)
{
  Room*					room = new Room(_core, 7, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 118));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(3.5, 1, 2.5));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 3.5, 240 * 2.5));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 820, room->getStartPos().Y, room->getStartPos().Z + 300));
  room->initMonsters(2);
  _roomsPool.emplace_back(room);
}

void	Map::generateRoom08(void)
{
  Room*					room = new Room(_core, 8, _actualRoom, irr::core::vector3df(_roomsPool[_actualRoom - 1]->getEndPos().X + 470,
											     _roomsPool[_actualRoom - 1]->getEndPos().Y,
											     _roomsPool[_actualRoom - 1]->getEndPos().Z - 418));
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, room->getStartPos(),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(4, 1, 4));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  terrain->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
  room->setTerrain(terrain);
  room->setSize(irr::core::position2d<irr::f32>(240 * 4, 240 * 4));
  room->setEndPos(irr::core::vector3df(room->getStartPos().X + 950, room->getStartPos().Y, room->getStartPos().Z + 300));
  room->initMonsters(5);
  _roomsPool.emplace_back(room);
}

void					Map::generateCatWalk(irr::core::vector3df const& pos)
{
  irr::scene::ITerrainSceneNode*	terrain = _smgr->addTerrainSceneNode("./resources/flat.jpeg", 0, 100, irr::core::vector3df(pos.X, pos.Y + 1, pos.Z),
									     irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 1, 1));

  terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  irr::video::ITexture* platform = _driver->getTexture("./resources/metal.png");
  _driver->makeColorKeyTexture(platform, irr::video::SColor(0,255,0,0));
  terrain->setMaterialTexture(0, platform);
  terrain->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

unsigned int		Map::run(Player* player)
{
  Room::LEVEL_STATE	state = _roomsPool[_actualRoom]->run(_core->getDevice(), player);
  if (_actualRoom != 0)
    {
      _roomsPool[_actualRoom - 1]->run(_core->getDevice(), player);
      if (!(_roomsPool[_actualRoom]->hitbox(player)) && !(_roomsPool[_actualRoom - 1]->hitbox(player)))
	player->getEntity()->setLifePoint(0);
    }
  else if (!(_roomsPool[_actualRoom]->hitbox(player)))
    player->getEntity()->setLifePoint(0);
  switch(state)
    {
    case Room::ACTUAL_ROOM:
      break;
    case Room::ROOM_CLEAR:
      generateCatWalk(_roomsPool[_actualRoom]->getEndPos());
      break;
    case Room::NEXT_ROOM:
      if (_actualRoom < _roomsPool.size())
	++_actualRoom;
      _roomsPool[_actualRoom]->setIsActive(true);
      _roomsPool[_actualRoom]->spawnMonsters();
      break;
    case Room::NEXT_LEVEL:
      generateLevel(false);
      return (1);
      break;
    }
  _smgr->drawAll();
  return (0);
}
