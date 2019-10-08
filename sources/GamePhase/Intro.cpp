//
// Intro.cpp for  in /home/marti7/rendu/c++/cpp_indie_studio/sources
//
// Made by Raphaël Martins
// Login   <raphael.martins@epitech.eu>
//
// Started on  Tue Jun  6 17:09:20 2017 Raphaël Martins
// Last update Sun Jun 18 22:24:53 2017 Anthony
//

#include "Intro.hpp"

Intro::Intro(Core* core)
{
  _core = core;
  _device = (_core->getDevice());
  _driver = (_core->getDriver());
  _smgr = (_core->getScene());
}

Intro::~Intro(){}

void  Intro::fist_mesh(irr::core::vector3df pos, irr::core::vector3df rot)
{
  _fist_mesh = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("resources/Intro/Silver_fist.md3"));
  if (_fist_mesh)
    {
      _fist_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, true);
      _fist_mesh->getMaterial(0).setTexture(0, _driver->getTexture("resources/Intro/silver_material.jpg"));
      _fist_mesh->setScale(irr::core::vector3df(50, 50, 50));
      _fist_mesh->setPosition(pos);
      _fist_mesh->setRotation(rot);
    }
}

void	Intro::init(void)
{
  _device->setWindowCaption(L"United Games");
  _smgr->clear();
  _device->getCursorControl()->setVisible(false);
  _camera = _smgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 45));
  irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(300, 0, -1, irr::core::vector3df(0, 0, 300));
  if (!cube)
    throw Error("Intro: Cube load failed");
  cube->setMaterialTexture(0, _driver->getTexture("./resources/Intro/brick_wall.jpeg"));
  cube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _alpha = 0;
  _state = false;
  fist_mesh(irr::core::vector3df(-2, 2, 0), irr::core::vector3df(100, 10, 0));
  fist_mesh(irr::core::vector3df(-2, 0, 0), irr::core::vector3df(100, 10, 45));
  fist_mesh(irr::core::vector3df(-2, -2, 0), irr::core::vector3df(100, 10, 90));
  fist_mesh(irr::core::vector3df(0, -2, 0), irr::core::vector3df(100, 10, 135));
  fist_mesh(irr::core::vector3df(2, -2, 0), irr::core::vector3df(100, 10, 180));
  fist_mesh(irr::core::vector3df(2, 0, 0), irr::core::vector3df(100, 10, 225));
  fist_mesh(irr::core::vector3df(2, 2, 0), irr::core::vector3df(100, 10, 270));
  fist_mesh(irr::core::vector3df(0, 2, 0), irr::core::vector3df(100, 10, 315));
  irr::scene::ILightSceneNode* lumiere = _smgr->addLightSceneNode (0, irr::core::vector3df(0,0,0), irr::video::SColorf(1.0f,1.0f,1.0f,1.0f), 50000.0f);
  irr::scene::ISceneNodeAnimator* anim = _smgr->createFlyCircleAnimator(irr::core::vector3df(200,300,200),190.0f, -0.0005f);
  lumiere->addAnimator(anim);
  anim->drop();
}

void	Intro::verifTime()
{
  if (_state == false)
    {
      _timeStart = _device->getTimer()->getTime();
      _state = true;
    }
  else
    {
      irr::u32  timeEnd = _device->getTimer()->getTime();
      if ((timeEnd - _timeStart) >= 7500)
	_core->changeGameState(Core::MAIN_MENU);
    }
}

void	Intro::run(void)
{
  verifTime();
  _smgr->drawAll();
  runTitle();
  _core->getSoundEventReceiver()->process(7,false,1.0);
}

void	Intro::runTitle(void)
{
  _intro_title = _core->initTexture("resources/Intro/united_games1.png");
  _driver->makeColorKeyTexture(_intro_title, irr::video::SColor(0,0,0,0));
  _driver->draw2DImage(_intro_title, irr::core::position2d<irr::s32>(732,400), irr::core::rect<irr::s32>(0,0,290,150), 0, irr::video::SColor(255,255,255,255), true);
  _introLogo = _core->initTexture("resources/Intro/logo1.png");
  _driver->makeColorKeyTexture(_introLogo, irr::video::SColor(0,0,0,0));
  _driver->draw2DImage(_introLogo, irr::core::position2d<irr::s32>(1022,400), irr::core::rect<irr::s32>(0,0,150,150), 0, irr::video::SColor(255,255,255,255), true);
}

void	Intro::stop(void)
{
  _driver->removeTexture(_intro_title);
}

Core*	Intro::getCore(void)
{
  return (_core);
}

irr::video::IVideoDriver*	Intro::getDriver(void)
{
  return (_driver);
}

irr::IrrlichtDevice*	Intro::getDevice(void)
{
  return (_device);
}

irr::scene::ISceneManager*	Intro::getScene(void)
{
  return (_smgr);
}
