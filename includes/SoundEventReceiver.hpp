//
// SoundEventReceiver.hpp for  in /home/simixay/Desktop/rendu/cpp_indie_studio/includes
//
// Made by simixay
// Login   <simixay.prakaythong@epitech.eu>
//
// Started on  Wed Jun 14 13:55:52 2017 simixay
// Last update Sun Jun 18 22:47:06 2017 Anthony
//

#ifndef SOUNDEVENTRECEIVER_HPP_
# define SOUNDEVENTRECEIVER_HPP_

# include <irrKlang.h>
# include <iostream>

class				SoundEventReceiver : public irrklang::ISoundStopEventReceiver
{
public:
  SoundEventReceiver();

public:
  virtual void OnSoundStopped(irrklang::ISound* sound,
			      irrklang::E_STOP_EVENT_CAUSE reason, void* userData);

public:
  irrklang::ISound*		getSound(void) const;
  void				setBackgroundSound(irrklang::ISound* sound, double volume);
  void				setLavaSound(irrklang::ISound* sound, double volume);
  irrklang::ISoundEngine*	getEngine(void) const;
  bool 				getState(void) const;
  void				setState(bool state);
  void 				process(int command, bool loop, double volume);
  void 				doStep(irrklang::ISound** sound, bool loop,std::string path, double volume);
  void 				checkEvent(irrklang::ISound* sound);

private:
  irrklang::ISound*		_sound;
  irrklang::ISound*		_clickSound;
  irrklang::ISound*		 _lavaSound;
  irrklang::ISound*		_fireCrackingSound;
  irrklang::ISound*		_footstepSound;
  irrklang::ISoundEngine*	_engine;
  irrklang::ISound*		_backgroundSound;
  irrklang::ISound*		_introMusic;
  bool				 _state;
  bool				_backgroundState;
  bool 				_introState;
};

#endif /* !SOUNDEVENTRECEIVER_HPP_ */
