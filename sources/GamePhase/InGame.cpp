//
// InGame.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Tue May  9 15:36:44 2017 Mex
// Last update Tue Aug 15 10:30:21 2017 Paqx
//

#include "InGame.hpp"

InGame::InGame(Core *core)
{
  _pauseState = false;
  _startTime = 0;
  _core = core;
  _device = (_core->getDevice());
  _driver = (_core->getDriver());
  _smgr = (_core->getScene());
}

InGame::~InGame(){}

void	InGame::init(void)
{
  (_core->getDevice())->setWindowCaption(L"Gantelet");
  _smgr->clear();
  _map = new Map(_core);
  _map->generateLevel(true);
  initPlayers();
  initHud();
  initPlayersLifeBar();
  _player[0]->getEntity()->setPosition(irr::core::vector3df(-100, 0, 50));
  _player[1]->getEntity()->setPosition(irr::core::vector3df(-40, 0, 50));
  _player[2]->getEntity()->setPosition(irr::core::vector3df(50, 0, 50));
  _player[3]->getEntity()->setPosition(irr::core::vector3df(100, 0, 50));
  _pause = _core->initTexture("resources/pause.png");
  _device->getCursorControl()->setVisible(false);
  _camera = _smgr->addCameraSceneNode(0, irr::core::vector3df(0, 500, -200));
  _actualPlayer = 0;
}

void	InGame::initPlayers(void)
{
  for (unsigned int i = 0; i <= 3; i++)
    {
      _player.emplace_back(_core->getPlayer(i));
      _player[i]->getEntity()->setActualMeshs(1);
    }
}

void			InGame::initHud(void)
{
  _icon4 = _driver->getTexture("./resources/MainMenu/Options/Player1.png");
  _driver->makeColorKeyTexture(_icon4, irr::video::SColor(0, 0, 0, 0));
  _icon3 = _driver->getTexture("./resources/MainMenu/Options/Player2.png");
  _driver->makeColorKeyTexture(_icon3, irr::video::SColor(0, 0, 0, 0));
  _icon2 = _driver->getTexture("./resources/MainMenu/Options/Player3.png");
  _driver->makeColorKeyTexture(_icon2, irr::video::SColor(0, 0, 0, 0));
  _icon1 = _driver->getTexture("./resources/MainMenu/Options/Player4.png");
  _driver->makeColorKeyTexture(_icon1, irr::video::SColor(0, 0, 0, 0));  
}

void			InGame::initPlayersLifeBar(void)
{
  _red_life_bar = _driver->getTexture ("./resources/life_bare.png");
  _green_life_bar = _driver->getTexture("./resources/greenLifeBar.jpg");
  _position_up_left.X = 0;
  _position_up_left.Y = 0;
  _rectangle.UpperLeftCorner = _position_up_left;
}

void	InGame::moveInGame(Player*& player)
{
  if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[2])) || (*player).getKeys()[2] == _core->getEventReceiver().getCurrentJoystick())
    {
      (*player).getEntity()->setPosition((*player).getEntity()->getPosition() + irr::core::vector3df(0, 0, ((*player).getEntity()->getSpeed() * _core->getFrameDeltaTime())));
      (*player).getEntity()->setNextRotation(180);
      (*player).getEntity()->setAnimation(true, true, IEntity::MOVE);
      _core->getSoundEventReceiver()->setState(false);
      _core->getSoundEventReceiver()->process(5,false,0.4);
    }
  else if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[3])) || (*player).getKeys()[3] == _core->getEventReceiver().getCurrentJoystick())
    {
      (*player).getEntity()->setPosition((*player).getEntity()->getPosition() + irr::core::vector3df(0, 0, ((*player).getEntity()->getSpeed() * -_core->getFrameDeltaTime())));
      (*player).getEntity()->setNextRotation(0);
      (*player).getEntity()->setAnimation(true, true, IEntity::MOVE);
      _core->getSoundEventReceiver()->setState(false);
      _core->getSoundEventReceiver()->process(5,false,0.4);
    }
  else if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[4])) || (*player).getKeys()[4] == _core->getEventReceiver().getCurrentJoystick())
    {
      if ((*player).getEntity()->isActive())
	{
	  (*player).getEntity()->setActualMeshs(2);
	  (*player).getEntity()->setAnimation(true, true, IEntity::ATTACK);
	  for (auto& it : _player)
	    {
	      if (it != player)
		if ((*it).getEntity()->hitbox((*player).getEntity()->getAttackRect()))
		  {
		    (*it).getEntity()->setLifePoint((*it).getEntity()->getLifePoint() - (*player).getEntity()->getDamage());
		    (*it).getEntity()->setKnockBack((*player).getEntity()->getAttackKnockback());
		  }
	    }
	  std::vector<IEntity*> monsters;
	  monsters = _map->getActualRoom()->getMonstersHit((*player).getEntity()->getAttackRect());
	  if ((monsters.size()) > 0)
	    {
	      for (auto& m : monsters)
		{
		  (*m).setLifePoint((*m).getLifePoint() - (*player).getEntity()->getDamage());
		  (*m).setKnockBack((*player).getEntity()->getAttackKnockback());
		}
	      _map->getActualRoom()->refreshMonstersNbr();
	    }
	}
      _core->getSoundEventReceiver()->setState(false);
      _core->getSoundEventReceiver()->process(5,false,0.4);
    }
}

void	InGame::movePlayers(void)
{
  for (auto& player : _player)
    {
      if ((*player).getEntity()->isActive())
	{
	  for (unsigned int i = 0; i < 4; i++)
	    if (!(_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[i])) && (*player).getEntity()->getActualMeshID() == 1)
  	      (*player).getEntity()->setAnimation(false, false, IEntity::MOVE);
  	  if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[0])) || (*player).getKeys()[0] == _core->getEventReceiver().getCurrentJoystick())
  	    {
	      (*player).getEntity()->setPosition((*player).getEntity()->getPosition() + irr::core::vector3df(((*player).getEntity()->getSpeed() * -_core->getFrameDeltaTime()), 0, 0));
	      (*player).getEntity()->setNextRotation(90);
	      (*player).getEntity()->setAnimation(true, true, IEntity::MOVE);
	      _core->getSoundEventReceiver()->setState(false);
	      _core->getSoundEventReceiver()->process(5, false, 0.4);
	    }
	  else if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey((*player).getKeys()[1])) || (*player).getKeys()[1] == _core->getEventReceiver().getCurrentJoystick())
	    {
	      (*player).getEntity()->setPosition((*player).getEntity()->getPosition() + irr::core::vector3df(((*player).getEntity()->getSpeed() * _core->getFrameDeltaTime()), 0, 0));
	      (*player).getEntity()->setNextRotation(270);
	      (*player).getEntity()->setAnimation(true, true, IEntity::MOVE);
	      _core->getSoundEventReceiver()->setState(false);
	      _core->getSoundEventReceiver()->process(5,false,0.4);
	    }
	  else
	    moveInGame(player);
	}
    }
  _camera->setPosition(irr::core::vector3df(_player[_actualPlayer]->getEntity()->getPosition().X, 500, _player[_actualPlayer]->getEntity()->getPosition().Z - 200));
  _camera->setTarget(_player[_actualPlayer]->getEntity()->getPosition());
}

void	       	InGame::displayPlayersIcon(void)
{
  _driver->draw2DImage(_icon4, irr::core::position2d<irr::s32>(282,890), irr::core::rect<irr::s32>(0, 0, 57, 37), 0, irr::video::SColor(255, 255, 255, 255), true);
  _driver->draw2DImage(_icon3, irr::core::position2d<irr::s32>(682,890), irr::core::rect<irr::s32>(0, 0, 57, 37), 0, irr::video::SColor(255, 255, 255, 255), true);
  _driver->draw2DImage(_icon2, irr::core::position2d<irr::s32>(1082,890), irr::core::rect<irr::s32>(0, 0, 57, 37), 0, irr::video::SColor(255, 255, 255, 255), true);
  _driver->draw2DImage(_icon1, irr::core::position2d<irr::s32>(1482,890), irr::core::rect<irr::s32>(0, 0, 57, 37), 0, irr::video::SColor(255, 255, 255, 255), true);
}

void		InGame::displayWarriorLife(void)
{
  t_Life	life;

  life.warriorLife = _player[0]->getEntity()->getLifePoint() - 360;
  _position_down_right_warrior.Y = _position_up_left.Y + 14;
  _position_down_right_warrior.X = _position_up_left.X + life.warriorLife;
  _rectangle.LowerRightCorner = _position_down_right_warrior;
  _driver->draw2DImage(_red_life_bar, irr::core::position2d<irr::s32>(180,980), irr::core::rect<irr::s32>(0, 0, 250, 23), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_green_life_bar, irr::core::position2d<irr::s32>(190,983), _rectangle, 0, irr::video::SColor(255,255,255,255), true);
}

void	InGame::displayElfLife(void)
{
  t_Life	life;

  life.elfLife = _player[3]->getEntity()->getLifePoint() - 60;
  _position_down_right_elf.Y = _position_up_left.Y + 14;
  _position_down_right_elf.X = _position_up_left.X + life.elfLife;
  _rectangle.LowerRightCorner = _position_down_right_elf;
  _driver->draw2DImage(_red_life_bar, irr::core::position2d<irr::s32>(580,980), irr::core::rect<irr::s32>(0, 0, 250, 23), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_green_life_bar, irr::core::position2d<irr::s32>(590,983), _rectangle, 0, irr::video::SColor(255,255,255,255), true);
}

void	InGame::displayWizardLife()
{
  t_Life	life;
  
  life.wizardLife = _player[2]->getEntity()->getLifePoint() - 60;
  _position_down_right_wizard.Y = _position_up_left.Y + 14;
  _position_down_right_wizard.X = _position_up_left.X + life.wizardLife;
  _rectangle.LowerRightCorner = _position_down_right_wizard;
  _driver->draw2DImage(_red_life_bar, irr::core::position2d<irr::s32>(980,980), irr::core::rect<irr::s32>(0, 0, 250, 23), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_green_life_bar, irr::core::position2d<irr::s32>(990,983), _rectangle, 0, irr::video::SColor(255,255,255,255), true);
}

void	InGame::displayValkyrieLife()
{
  t_Life	life;

  life.valkyrieLife = _player[1]->getEntity()->getLifePoint() - 360;
  _position_down_right_valkyrie.Y = _position_up_left.Y + 14;
  _position_down_right_valkyrie.X = _position_up_left.X + life.valkyrieLife;
  _rectangle.LowerRightCorner = _position_down_right_valkyrie;
  _driver->draw2DImage(_red_life_bar, irr::core::position2d<irr::s32>(1380,980), irr::core::rect<irr::s32>(0, 0, 250, 23), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_green_life_bar, irr::core::position2d<irr::s32>(1390,983), _rectangle, 0, irr::video::SColor(255,255,255,255), true);
}

void	InGame::keyFct(void)
{
  irr::u32	endTime;
    
  if ((_core->getEventReceiver()).IsKeyDown(irr::KEY_ESCAPE))
    {
      (_core->changeGameState(Core::MAIN_MENU));
      _core->getSoundEventReceiver()->getEngine()->stopAllSounds();
      _core->getSoundEventReceiver()->setState(false);
    }
  if ((_core->getEventReceiver()).IsKeyDown(irr::KEY_SPACE))
    {
      if (_pauseState == false)
	{
	  endTime = _device->getTimer()->getTime();
	  if ((endTime - _startTime) > 100)
	    {
	      _startTime = _device->getTimer()->getTime();
	      _pauseState = true;
	    }
	}
      else
	{
	  endTime = _device->getTimer()->getTime();
	  if ((endTime - _startTime) > 100)
	    {
	      _pauseState = false;
	      _startTime = _device->getTimer()->getTime();
	    }
	}
    }
}

void	InGame::run(void)
{
  _smgr->drawAll();
  if (_pauseState == false)
    {
      for (auto& player : _player)
	{
	  (*player).getEntity()->run();
	  if (_map->run(player) == 1)
	    {
	      (_core->changeGameState(Core::IN_GAME));
	      _core->getSoundEventReceiver()->getEngine()->stopAllSounds();
	      _core->getSoundEventReceiver()->setState(false);
	    }
	}
      std::function<void()> fct = std::bind(&InGame::movePlayers, this);
      _core->getThreadPool()->putInQueue(fct);
    }
  else
    _driver->draw2DImage(_pause, irr::core::position2d<irr::s32>(600, 440), irr::core::rect<irr::s32>(0,0,800,160),0,irr::video::SColor(255,255,255,255), true);
  displayPlayersIcon();
  displayWarriorLife();
  displayValkyrieLife();
  displayWizardLife();
  displayElfLife();
  keyFct();
}

void	InGame::stop(void)
{
  delete _map;
  _driver->removeTexture(_pause);
  _player.clear();
}
