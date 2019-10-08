//
// MouseEvent.cpp for MouseEvent.cpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
//
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
//
// Started on  Fri May 12 10:46:02 2017 Anthony
// Last update Sun Jun 18 22:19:50 2017 Anthony
//

#include "MouseEvent.hpp"

MouseEvent::MouseEvent(MainMenu *menu)
{
  _menu = menu;
  _mouse = ((_menu->getCore())->getEventReceiver()).getLeftMousePosition();
}

MouseEvent::MouseEvent(MouseEvent const& other)
{
  _menu = other._menu;
  _mouse = other._mouse;
}

MouseEvent&	MouseEvent::operator=(MouseEvent const& other)
{
  _menu = other._menu;
  _mouse = other._mouse;
  return (*this);
}

MouseEvent::~MouseEvent(){}

void	MouseEvent::otherButton()
{
  if ((_mouse.X >= 675 && _mouse.X <= 1245) && (_mouse.Y >= 500 && _mouse.Y <= 560) && _menu->getState() == MainMenu::MAIN_MENU)
    {
      (_menu->getFireAnim())->setMaterialTexture(0, (_menu->getDriver())->getTexture("./resources/MainMenu/fire2.bmp"));
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setState(MainMenu::HIGH_SCORE);
    }
  else if ((_mouse.X >= 769 && _mouse.X <= 1152) && (_mouse.Y >= 650 && _mouse.Y <= 710) && _menu->getState() == MainMenu::MAIN_MENU)
    {
      (_menu->getFireAnim())->setMaterialTexture(0, (_menu->getDriver())->getTexture("./resources/MainMenu/fire3.bmp"));
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setState(MainMenu::OPTIONS);
    }
  else
    returnMainMenu();
}

void	MouseEvent::mainMenuButton()
{
  if ((_mouse.X >= 859 && _mouse.X <= 1062) && (_mouse.Y >= 800 && _mouse.Y <= 860) && _menu->getState() == MainMenu::MAIN_MENU)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      (_menu->getCore())->changeGameState(Core::EXIT);
      return;
    }
  else if ((_mouse.X >= 844 && _mouse.X <= 1077) && (_mouse.Y >= 350 && _mouse.Y <= 410) && _menu->getState() == MainMenu::MAIN_MENU)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setState(MainMenu::TEAM_SELECT);
      return;
    }
  else if (((_mouse.X >= 1500 && _mouse.X <= 1740) && (_mouse.Y >= 900 && _mouse.Y <= 960) && _menu->getState() == MainMenu::TEAM_SELECT))
    {
      (_menu->getCore())->changeGameState(Core::SELECT_CHAR);
      _menu->setArrow(false);
      (_menu->getCore())->setTeamName(_menu->getTeamName());
      _menu->setState(MainMenu::EXIT);
      return;
    }
  else
    otherButton();
}

void	MouseEvent::optionSelectCharacterButton()
{
  if ((_mouse.X >= 400 && _mouse.X <= 457) && (_mouse.Y >= 650 && _mouse.Y <= 687) && _menu->getState() == MainMenu::OPTIONS)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setPlayer(MainMenu::PLAYER3);
    }
  if ((_mouse.X >= 400 && _mouse.X <= 457) && (_mouse.Y >= 750 && _mouse.Y <= 787) && _menu->getPlayer() != MainMenu::PLAYER4 && _menu->getState() == MainMenu::OPTIONS)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setPlayer(MainMenu::PLAYER4);
    }
}

void	MouseEvent::optionButton()
{
  if ((_mouse.X >= 400 && _mouse.X <= 457) && (_mouse.Y >= 450 && _mouse.Y <= 487) && _menu->getPlayer() != MainMenu::PLAYER1 && _menu->getState() == MainMenu::OPTIONS)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setPlayer(MainMenu::PLAYER1);
    }
  else if ((_mouse.X >= 400 && _mouse.X <= 457) && (_mouse.Y >= 550 && _mouse.Y <= 587) && _menu->getPlayer() != MainMenu::PLAYER2 && _menu->getState() == MainMenu::OPTIONS)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setPlayer(MainMenu::PLAYER2);
    }
  else
    optionSelectCharacterButton();
}

void	MouseEvent::returnMainMenu()
{
  if ((_mouse.X >= 150 && _mouse.X <= 320) && (_mouse.Y >= 900 && _mouse.Y <= 960) && _menu->getState() != MainMenu::MAIN_MENU)
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      (_menu->getFireAnim())->setMaterialTexture(0, (_menu->getDriver())->getTexture("./resources/MainMenu/fire.bmp"));
      _menu->setArrow(false);
      if (_menu->getState() == MainMenu::TEAM_SELECT)
	_menu->getCore()->getScene()->getSceneNodeFromId(42)->remove();
      _menu->setState(MainMenu::MAIN_MENU);
      _menu->setPlayer(MainMenu::UNKNOWN);
      _menu->setOptionState(false);
      for (int i = 0; i <= 5; ++i)
	_menu->setKeys(i, false);
    }
  else if (((_mouse.X >= 1500 && _mouse.X <= 1740) && (_mouse.Y >= 900 && _mouse.Y <= 960) && _menu->getState() == MainMenu::OPTIONS))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->getCore()->getKeys()->saveButtons();
    }
  else
    handleKey1();
}

void	MouseEvent::handleKey1()
{
  if (((_mouse.X >= 582 && _mouse.X <= 852) && (_mouse.Y >= 490 && _mouse.Y <= 520) && _menu->getState() == MainMenu::OPTIONS && _menu->getPlayer() != MainMenu::PLAYER4)
       || _menu->getKeys(0))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setKeys(0,true);
      _menu->setOptionState(true);
    }
  else if (((_mouse.X >= 1182 && _mouse.X <= 1482) && (_mouse.Y >= 490 && _mouse.Y <= 520) && _menu->getState() == MainMenu::OPTIONS &&  _menu->getPlayer() != MainMenu::PLAYER4)
	   || _menu->getKeys(1))
     {
       _menu->getCore()->getSoundEventReceiver()->setState(false);
       _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
       _menu->setKeys(1,true);
       _menu->setOptionState(true);
    }
  else
    handleKey2();
}

void	MouseEvent::handleKey2()
{
  if (((_mouse.X >= 582 && _mouse.X <= 882) && (_mouse.Y >= 590 && _mouse.Y <= 620) && _menu->getState() == MainMenu::OPTIONS && _menu->getPlayer() != MainMenu::PLAYER4)
      || _menu->getKeys(2))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setKeys(2,true);
      _menu->setOptionState(true);
    }
  else if (((_mouse.X >= 1182 && _mouse.X <= 1482) && (_mouse.Y >= 590 && _mouse.Y <= 620) && _menu->getState() == MainMenu::OPTIONS && _menu->getPlayer() != MainMenu::PLAYER4)
	   || _menu->getKeys(3))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setKeys(3,true);
      _menu->setOptionState(true);
    }
  else
    handleKey3();
}

void	MouseEvent::handleKey3()
{
  if (((_mouse.X >= 582 && _mouse.X <= 882) && (_mouse.Y >= 690 && _mouse.Y <= 720) && _menu->getState() == MainMenu::OPTIONS && _menu->getPlayer() != MainMenu::PLAYER4)
	   || _menu->getKeys(4))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setKeys(4,true);
      _menu->setOptionState(true);
    }
  else if (((_mouse.X >= 1182 && _mouse.X <= 1482) && (_mouse.Y >= 690 && _mouse.Y <= 720) && _menu->getState() == MainMenu::OPTIONS &&  _menu->getPlayer() != MainMenu::PLAYER4)
	   || _menu->getKeys(5))
    {
      _menu->getCore()->getSoundEventReceiver()->setState(false);
      _menu->getCore()->getSoundEventReceiver()->process(6,false,0.2);
      _menu->setKeys(5,true);
      _menu->setOptionState(true);
    }
  else
    optionButton();
}
