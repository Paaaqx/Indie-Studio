//
// EventReceiver.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Thu May  4 17:46:00 2017 Mex
// Last update Fri Jun 16 12:45:27 2017 Anthony
//

#include <iostream>
#include "EventReceiver.hpp"

EventReceiver::EventReceiver()
{
  for (unsigned int i = 1; i < irr::KEY_KEY_CODES_COUNT; i++)
    _keyIsDown[i] = false;
  _leftMouseState = false;
  _leftMousePosition.X = -1;
  _leftMousePosition.Y = -1;
  _key = -1;
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
      switch(event.MouseInput.Event)
	{
	case irr::EMIE_LMOUSE_PRESSED_DOWN:
	  _leftMouseState = true;
	  _leftMousePosition.X = event.MouseInput.X;
	  _leftMousePosition.Y = event.MouseInput.Y;
	  break;
	case irr::EMIE_LMOUSE_LEFT_UP:
	  _leftMouseState = false;
	  break;
	case irr::EMIE_MOUSE_MOVED:
	  _leftMousePosition.X = event.MouseInput.X;
	  _leftMousePosition.Y = event.MouseInput.Y;
	  break;
	default:
	  break;
	}
    }
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && event.JoystickEvent.Joystick == 0)
    _joystickState = event.JoystickEvent;
  return false;
}

bool	EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return _keyIsDown[keyCode];
}

bool	EventReceiver::getLeftMouseState(void) const
{
  return (_leftMouseState);
}

int		EventReceiver::getCurrentKey(void) const
{
  unsigned int	i = 1;

  while (i < irr::KEY_KEY_CODES_COUNT)
    {
      if (_keyIsDown[i] == true)
	return (i);
      ++i;
    }
  return (-1);
}

int			EventReceiver::getCurrentJoystick(void) const
{
  unsigned int		i = 0;
  irr::f32		moveHorizontal = 0.f;
  irr::f32		moveVertical = 0.f;
  const irr::f32	DEAD_ZONE = 0.05f;

  while (i < 33)
    {
      if (_joystickState.IsButtonPressed(i))
	return (i);
      ++i;
    }
  moveHorizontal = (irr::f32)_joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
  if (fabs(moveHorizontal) < DEAD_ZONE)
    moveHorizontal = 0.f;
  moveVertical = (irr::f32)_joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
  if (fabs(moveVertical) < DEAD_ZONE)
    moveVertical = 0.f;
  const irr::u16 povDegrees = _joystickState.POV / 100;
  if (povDegrees < 360)
    {
      if (povDegrees > 0 && povDegrees < 180)
	moveHorizontal = 1.f;
      else if (povDegrees > 180)
	moveHorizontal = -1.f;
      if (povDegrees > 90 && povDegrees < 270)
	moveVertical = -1.f;
      else if (povDegrees > 270 || povDegrees < 90)
	moveVertical = +1.f;
    }
  if (moveHorizontal == -1 || moveHorizontal <= -0.4000000)
    return (32);
  else if (moveHorizontal >= 0.400000)
    return (33);
  if (moveVertical >= 0.400000)
    return (34);
  else if (moveVertical == -1 || moveVertical <= -0.400000)
    return (35);
  return (-1);
}

irr::core::position2d<irr::s32>	EventReceiver::getLeftMousePosition(void) const
{
  return (_leftMousePosition);
}

const irr::SEvent::SJoystickEvent&	EventReceiver::getJoystickState(void) const
{
  return (_joystickState);
}
