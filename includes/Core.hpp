//
// Core.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Thu May  4 16:54:36 2017 Mex
// Last update Sun Jun 18 20:49:41 2017 Anthony
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include <memory>
# include <iostream>
# include <irrlicht.h>
# include <vector>
# include <chrono>
# include <thread>
# include "IGamePhase.hpp"
# include "Errors.hpp"
# include "FPSBenchmark.hpp"
# include "EventReceiver.hpp"
# include "SoundEventReceiver.hpp"
# include "driverChoice.h"
# include "Player.hpp"
# include "KeySelector.hpp"
# include "ThreadPool.hpp"

# define WIDTH 1920
# define HEIGHT 1080

class					Core
{
public:
  Core();
  ~Core();

public:
  enum					gameState
    {
      INTRO = 0,
      MAIN_MENU = 1,
      SELECT_CHAR = 2,
      IN_GAME = 3,
      EXIT = 4,
    };

public:
  irr::IrrlichtDevice*			getDevice(void) const;
  EventReceiver				getEventReceiver(void) const;
  SoundEventReceiver*			getSoundEventReceiver(void);
  gameState				getGameState(void) const;
  void					changeGameState(gameState const& state);
  void					pushToGamePhase(IGamePhase* gamePhase);
  IGamePhase*				getCurrentGamePhase(void) const;
  IGamePhase*				getGamePhase(const unsigned int i) const;
  void					addNewPlayer(void);
  Player*				getPlayer(unsigned int playerNumber) const;
  unsigned int				getPlayerNbr(void) const;
  void					setPlayerNbr(unsigned int playerNbr);
  std::string const&			getTeamName(void) const;
  void					setTeamName(std::string const teamName);
  KeySelector*				getKeys(void) const;
  void					setKeys(void);
  int					getFPS(void) const;
  void					setFPS(int const& FPS);
  irr::f32				getFrameDeltaTime() const;
  void					setFrameDeltaTime(void);
  irr::video::IVideoDriver*		getDriver(void) const;
  irr::scene::ISceneManager*		getScene(void) const;
  irr::video::ITexture*			initTexture(const char* file);
  irr::scene::IAnimatedMeshSceneNode*	getNewMesh(unsigned int ID, const char* meshPath, const char* textPath,
						   irr::core::vector3df pos, irr::core::vector3df scale, irr::core::vector3df rot);
  irr::core::array<irr::SJoystickInfo>	getJoystickInfo(void) const;
  ThreadPool*				getThreadPool(void);

private:
  irr::video::E_DRIVER_TYPE		_driverChoice;
  irr::IrrlichtDevice*			_device;
  irr::video::IVideoDriver*		_driver;
  irr::scene::ISceneManager*		_smgr;
  EventReceiver				_receiver;
  SoundEventReceiver			_soundReceiver;
  // std::vector<std::unique_ptr<IGamePhase>>		_gamePhases;
  std::vector<IGamePhase*>		_gamePhases;
  gameState				_currentGamePhase;
  gameState				_gameState;
  KeySelector*				_keys;
  std::vector<Player*>			_player;
  unsigned int				_playerNbr;
  std::string				_teamName;
  irr::core::array<irr::SJoystickInfo>	_joystickInfo;
  int					_FPS;
  irr::u32				_timeThen;
  irr::f32				_frameDeltaTime;
  ThreadPool*     _threadPool;
};

#endif /* !CORE_HPP_ */
