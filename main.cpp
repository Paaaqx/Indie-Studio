//
// main.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Wed May  3 16:35:10 2017 Mex
// Last update Thu Jul  6 09:31:09 2017 Paqx
//

#include <iostream>
#include "Errors.hpp"
#include "Map.hpp"
#include "MainMenu.hpp"
#include "SelectCharacter.hpp"
#include "Intro.hpp"
#include "InGame.hpp"

static void	initGamePhases(Core *core)
{
  core->pushToGamePhase(new Intro(core));
  core->pushToGamePhase(new MainMenu(core));
  core->pushToGamePhase(new SelectCharacter(core));
  core->pushToGamePhase(new InGame(core));
  core->getCurrentGamePhase()->init();
}

static void	deleteGamePhases(Core *core)
{
  for (unsigned int i = 1; i < 4; i++)
    delete core->getGamePhase(i);
}

int			main(void)
{
  try
    {
      Core		core;
      FPSBenchmark	FPS(core.getDevice(), core.getDriver());

      initGamePhases(&core);
      while (core.getDevice()->run() && core.getDriver() && (core.getGameState() != Core::EXIT))
	{
	  core.setFrameDeltaTime();
	  core.getDriver()->beginScene(true, true, irr::video::SColor(255,0,0,0));
	  if (core.getDevice()->isWindowActive())
	    core.getCurrentGamePhase()->run();
	  core.setFPS(FPS.refresh());
	  FPS.display();
	  core.getDriver()->endScene();
	}
      deleteGamePhases(&core);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  return (0);
}
