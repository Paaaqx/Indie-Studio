/*
** SoundEventReceiver.cpp for cpp_indie_studio in /home/simixay/Desktop/rendu/cpp_indie_studio/sources
**
** Made by simixay
** Login   <simixay@epitech.net>
**
** Started on  Wed Jun 14 14:01:58 2017 simixay
// Last update Sun Jun 18 22:47:15 2017 Anthony
*/

# include "SoundEventReceiver.hpp"
# include "Errors.hpp"

SoundEventReceiver::SoundEventReceiver()
{
  if (!(_engine = irrklang::createIrrKlangDevice()))
    throw Error("Could nod load sound engine");
  _state = false;
  _footstepSound = NULL;
  _lavaSound = NULL;
  _sound = NULL;
  _backgroundSound = NULL;
  _clickSound = NULL;
  _fireCrackingSound = NULL;
  _introMusic = NULL;
  _introState = false;
}

void	SoundEventReceiver::OnSoundStopped(irrklang::ISound* sound,
					   irrklang::E_STOP_EVENT_CAUSE reason,void* userData)
{
  sound->stop();
  if (std::string(sound->getSoundSource()->getName()).compare("./resources/sounds/lava.ogg") == 0
      || std::string(sound->getSoundSource()->getName()).compare("./resources/sounds/background.ogg") == 0
      || std::string(sound->getSoundSource()->getName()).compare("./resources/sounds/ingame_background.ogg") == 0
      || std::string(sound->getSoundSource()->getName()).compare("./resources/sounds/fire_crackingmak.ogg") == 0)
    sound->setIsLooped(true);
  (void)(reason);
  (void)(userData);
}

irrklang::ISound*	SoundEventReceiver::getSound(void) const
{
  return (_sound);
}

void	SoundEventReceiver::setBackgroundSound(irrklang::ISound* sound, double volume)
{
  _backgroundSound = sound;
  if (_backgroundSound)
  {
	  _backgroundSound->setVolume(volume);
	  checkEvent(_backgroundSound);
	  setState(true);
  }
}

void	SoundEventReceiver::setLavaSound(irrklang::ISound* sound, double volume)
{
  _lavaSound = sound;
  if (_lavaSound)
  {
	  _lavaSound->setVolume(volume);
	  checkEvent(_lavaSound);
	  setState(true);
  }
}

irrklang::ISoundEngine*	SoundEventReceiver::getEngine(void) const
{
  return (_engine);
}

bool	SoundEventReceiver::getState(void) const
{
  return (_state);
}

void	SoundEventReceiver::setState(bool state)
{
  _state = state;
}

void	SoundEventReceiver::process(int command, bool loop, double volume)
{
  if (!_introState && command == 7)
    {
      doStep(&_introMusic,false,"./resources/sounds/intro_music.ogg",volume);
	_introState = true;
    }
  if (!_state)
    {
      switch(command)
	{
	case 1:
	  setBackgroundSound(_engine->play2D("./resources/sounds/background.ogg",loop,false,true),volume);
	  setState(true);
	  break;
	case 2:
	  setBackgroundSound(_engine->play2D("./resources/sounds/ingame_background.ogg",loop, false, true),volume);
	  setState(true);
	  break;
	case 3:
	  setLavaSound(_engine->play2D("./resources/sounds/lava.ogg",loop,false,true), volume);
	  break;
        case 4:
	  doStep(&_fireCrackingSound,true,"./resources/sounds/fire_cracking.ogg",volume);
	  setState(true);
	  break;
        case 5:
	  doStep(&_footstepSound,false,"./resources/sounds/footsteps.ogg", volume);
	  break;
        case 6:
	  doStep(&_clickSound,false, "./resources/sounds/click.wav", volume);
	  setState(true);
	  break;
        default:
	  break;
	}

    }
}

void	SoundEventReceiver::doStep(irrklang::ISound** sound,bool loop,std::string path, double volume)
{
  if (!(*sound))
    {
      (*sound) = _engine->play2D(path.c_str(),loop, false, true);
      checkEvent((*sound));
    }
  else if ((*sound) && (*sound)->isFinished())
  {
	  (*sound) = _engine->play2D(path.c_str(), loop, false, true);
	  (*sound)->setVolume(volume);
  }
  checkEvent(*sound);
}

void	SoundEventReceiver::checkEvent(irrklang::ISound* sound)
{
  if (sound)
    sound->setSoundStopEventReceiver(this);
}
