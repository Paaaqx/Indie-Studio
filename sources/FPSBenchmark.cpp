//
// FPSBenchmark.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Fri Jun  2 17:35:55 2017 Mex
// Last update Fri Jun  2 17:59:09 2017 Mex
//

#include "FPSBenchmark.hpp"

FPSBenchmark::FPSBenchmark(irr::IrrlichtDevice* device, irr::video::IVideoDriver* driver)
{
  _device = device;
  _driver = driver;
  _guiEnv = _device->getGUIEnvironment();
  _font = _guiEnv->getFont("./resources/myfont.xml");
  _lastFPS = -1;
}

FPSBenchmark::~FPSBenchmark(){}

void	FPSBenchmark::display(void)
{
  _font->draw(irr::core::stringw(std::to_string(_FPS).c_str()).c_str(),
	     irr::core::rect<irr::s32>(WIDTH - 100,-10,0,0),
	     irr::video::SColor(255,255,255,255));
  _guiEnv->drawAll();
}

int	FPSBenchmark::refresh(void)
{
  _FPS = _driver->getFPS();
  if (_FPS != _lastFPS)
    {
      _lastFPS = _FPS;
      _guiEnv->clear();
    }
  return (_FPS);
}
