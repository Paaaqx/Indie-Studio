//
// FPSBenchmark.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Fri Jun  2 17:34:33 2017 Mex
// Last update Fri Jun 16 11:40:53 2017 Anthony
//

#include <irrlicht.h>
#include <string>

#ifndef FPSBENCHMARK
# define FPSBENCHMARK

# define WIDTH 1920
# define HEIGHT 1080

class				FPSBenchmark
{
public:
  FPSBenchmark(irr::IrrlichtDevice* device, irr::video::IVideoDriver* driver);
  ~FPSBenchmark();

public:
  void				display(void);
  int				refresh(void);

private:
  irr::IrrlichtDevice*		_device;
  irr::video::IVideoDriver*	_driver;
  irr::gui::IGUIEnvironment*	_guiEnv;
  irr::gui::IGUIFont*		_font;
  int				_FPS;
  int				_lastFPS;
};

#endif /* !FPSBENCHMARK */
