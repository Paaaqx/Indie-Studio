//
// EventReceiver.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Thu May  4 17:46:44 2017 Mex
// Last update Fri Jun 16 12:02:38 2017 Anthony
//

#ifndef EVENTRECEIVER_HPP_
# define EVENTRECEIVER_HPP_

#include "irrlicht.h"

class					EventReceiver : public irr::IEventReceiver
{
public:
  EventReceiver();

public:
  virtual bool				OnEvent(const irr::SEvent& event);
  virtual bool				IsKeyDown(irr::EKEY_CODE keyCode) const;
  bool					getLeftMouseState(void) const;
  irr::core::position2d<irr::s32>	getLeftMousePosition(void) const;
  int					getCurrentKey(void) const;
  int					getCurrentJoystick(void) const;
  int					getKey(void) const;
  void					setKey(int key);
  const irr::SEvent::SJoystickEvent	&getJoystickState(void) const;

private:
  bool					_keyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool					_leftMouseState;
  irr::core::position2d<irr::s32>	_leftMousePosition;
  int					_key;
  irr::SEvent::SJoystickEvent		_joystickState;
};

#endif /* !EVENTRECEIVER_HPP_ */
