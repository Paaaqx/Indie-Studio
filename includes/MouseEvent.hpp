//
// MouseEvent.hpp for MouseEvent.hpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Fri May 12 10:38:40 2017 Anthony
// Last update Fri Jun 16 11:58:25 2017 Anthony
//

#ifndef MOUSEEVENT_HPP_
# define MOUSEEVENT_HPP_

# include <chrono>
# include <thread>
# include "MainMenu.hpp"
# include "KeySelector.hpp"

class					MouseEvent
{
public:
  MouseEvent(MainMenu *menu);
  MouseEvent(MouseEvent const& other);
  MouseEvent&	operator=(MouseEvent const& other);
  ~MouseEvent();

public:
  void					mainMenuButton();
  void					otherButton();
  void					optionSelectCharacterButton();
  void					highScoreButton();
  void					optionButton();
  void					returnMainMenu();
  void					handleKey1();
  void					handleKey2();
  void					handleKey3();
  
private:
  MainMenu				*_menu;
  irr::core::position2d<irr::s32>	_mouse;
};

#endif /* !MOUSEEVENT_HPP_ */
