//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Thu May  4 16:58:03 2017 Mex
// Last update Sun Jun 18 22:32:41 2017 Anthony
//

#include "Core.hpp"

Core::Core()
{
  _driverChoice = irr::video::EDT_OPENGL;
  if (_driverChoice == irr::video::EDT_COUNT)
    throw Error("Wrong Driver Choice");
  _device = irr::createDevice(_driverChoice, irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, false, false, &_receiver);
  if (_device == 0)
    throw Error("Could not create the driver");
  _driver = _device->getVideoDriver();
  _smgr = _device->getSceneManager();
  _currentGamePhase = INTRO;
  _gameState = INTRO;
  _timeThen = _device->getTimer()->getTime();
  _teamName = "AAA";
  _keys = new KeySelector();
  _threadPool = new ThreadPool(10);
  if (_device->activateJoysticks(_joystickInfo))
    std::cout << "Joystick support is enabled." << std::endl;
  else
    std::cout << "Joystick support is not enabled." << std::endl;
  _playerNbr = 1;
}

Core::~Core()
{
  delete _keys;
  delete _threadPool;
  unsigned int size = _player.size();;
  for (unsigned int i = 0; i < size; i++)
    delete _player[i];
  _device->drop();
}

irr::IrrlichtDevice*	Core::getDevice(void) const
{
  return (_device);
}

irr::video::IVideoDriver*	Core::getDriver(void) const
{
  return (_driver);
}

irr::scene::ISceneManager*	Core::getScene(void) const
{
  return (_smgr);
}

EventReceiver		Core::getEventReceiver(void) const
{
  return (_receiver);
}

SoundEventReceiver*  Core::getSoundEventReceiver(void)
{
  return (&_soundReceiver);
}

irr::core::array<irr::SJoystickInfo>	Core::getJoystickInfo(void) const
{
  return (_joystickInfo);
}

Core::gameState	Core::getGameState(void) const
{
  return (_gameState);
}

void	Core::changeGameState(gameState const& state)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  _gameState = state;
  if (state != EXIT)
    {
      _gamePhases[_currentGamePhase]->stop();
      _currentGamePhase = state;
      _gamePhases[_currentGamePhase]->init();
    }
}

void	Core::pushToGamePhase(IGamePhase* gamePhase)
{
  _gamePhases.emplace_back(gamePhase);
}

IGamePhase*	Core::getCurrentGamePhase(void) const
{
  return (_gamePhases[_currentGamePhase]);
}

IGamePhase*	Core::getGamePhase(unsigned int const i) const
{
  return (_gamePhases[i]);
}

irr::video::ITexture*	Core::initTexture(const char* filePath)
{
  irr::video::ITexture*	texture;

  if (!(texture = _driver->getTexture(filePath)))
    {
      std::string error("Could not load ");
      error += filePath;
      throw Error(error);
    }
  return (texture);
}

irr::scene::IAnimatedMeshSceneNode*	Core::getNewMesh(unsigned int ID, const char* meshPath, const char* textPath, irr::core::vector3df pos,
							 irr::core::vector3df scale, irr::core::vector3df rot)
{
  irr::scene::IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh(meshPath), 0, ID, pos, rot, scale);
  if (!node)
    {
      std::string error("Could not load ");
      error += meshPath;
      throw Error(error);
    }
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->getMaterial(0).setTexture(0, initTexture(textPath));
  node->setLoopMode(false);
  node->addShadowVolumeSceneNode();
  node->setAnimationSpeed(0);
  return (node);
}

void	Core::addNewPlayer(void)
{
  _player.emplace_back(new Player);
}

Player*	Core::getPlayer(unsigned int playerNumber) const
{
  return (_player[playerNumber]);
}

unsigned int	Core::getPlayerNbr(void) const
{
  return (_playerNbr);
}

void	Core::setPlayerNbr(unsigned int playerNbr)
{
  _playerNbr = playerNbr;
}

std::string const&	Core::getTeamName(void) const
{
  return (_teamName);
}

void	Core::setTeamName(std::string const teamName)
{
  _teamName = teamName;
}

KeySelector*	Core::getKeys(void) const
{
  return (_keys);
}

int	Core::getFPS(void) const
{
  return (_FPS);
}

void	Core::setFPS(int const& FPS)
{
  _FPS = FPS;
}

irr::f32	Core::getFrameDeltaTime() const
{
  return (_frameDeltaTime);
}

void			Core::setFrameDeltaTime(void)
{
  const irr::u32	now = _device->getTimer()->getTime();
  _frameDeltaTime = (irr::f32)(now - _timeThen) / 1000.f;
  _timeThen = now;
}

ThreadPool* Core::getThreadPool(void)
{
  return (_threadPool);
}
