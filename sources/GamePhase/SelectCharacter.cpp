//
// SelectCharacter.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Tue May  9 16:03:00 2017 Mex
// Last update Sun Jun 18 22:30:44 2017 Anthony
//

#include "SelectCharacter.hpp"

SelectCharacter::SelectCharacter(Core *core)
{
  _core = core;
  _device = (_core->getDevice());
  _driver = (_core->getDriver());
  _smgr = (_core->getScene());
}

SelectCharacter::~SelectCharacter(){}

void	SelectCharacter::init(void)
{
  _device->setWindowCaption(L"Gantelet : Select your Character");
  _device->getCursorControl()->setVisible(false);
  _smgr->clear();
  initPlayers();
  initSpecialEffects();
  initMeshs();
  initEntities();
  _camera = _smgr->addCameraSceneNode(0, irr::core::vector3df(0,120,-200), irr::core::vector3df(0, 90,0));
  _camera->setFarValue(10000.0f);
  _currentPlayer = 0;
  _stateWarrior = false;
  _stateValkyrie = false;
  _stateWizard = false;
  _stateElf = false;
  _posArrow.emplace_back(-105);
  _posArrow.emplace_back(-47);
  _posArrow.emplace_back(35);
  _posArrow.emplace_back(100);
  _arrowState = 0;
  _arrow = false;
  stateArrow1 = false;
  stateArrow2 = false;
  for (int i = 0; i <= 3;++i)
    _isBusy.emplace_back(false);
}

void		SelectCharacter::initPlayers(void)
{
  for (unsigned int i = 0; i < 4; i++)
    _core->addNewPlayer();
  _core->getPlayer(0)->setKeys(_core->getKeys()->keysPlayer1);
  _core->getPlayer(0)->setOccupied(false);
  _core->getPlayer(1)->setKeys(_core->getKeys()->keysPlayer2);
  _core->getPlayer(1)->setOccupied(false);
  _core->getPlayer(2)->setKeys(_core->getKeys()->keysPlayer3);
  _core->getPlayer(2)->setOccupied(false);
  _core->getPlayer(3)->setKeys(_core->getKeys()->joysticksPlayer4);
  _core->getPlayer(3)->setOccupied(false);
}

void	SelectCharacter::initEntities(void)
{
  _warrior = new Warrior(_core, irr::core::vector3df(-100, 0, 50));
  _warrior->setActualMeshs(0);
  _warrior->setRotation(irr::core::vector3df(0, -10, 0));
  _valkyrie = new Valkyrie(_core, irr::core::vector3df(-40, 0, 50));
  _valkyrie->setActualMeshs(0);
  _wizard = new Wizard(_core, irr::core::vector3df(50, 0, 50));
  _wizard->setActualMeshs(0);
  _wizard->setRotation(irr::core::vector3df(0, 15, 0));
  _elf = new Elf(_core, irr::core::vector3df(100, 0, 50));
  _elf->setActualMeshs(0);
  _elf->setRotation(irr::core::vector3df(0, 25, 0));
}

void	SelectCharacter::initMeshs(void)
{
  irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1000);
  if (cube)
    {
      cube->setPosition(irr::core::vector3df(0,-600,50));
      cube->setMaterialTexture(0, _driver->getTexture("./resources/magma.jpg"));
      cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  irr::scene::ISceneNode* skybox = _smgr->addSkyBoxSceneNode(_driver->getTexture("./resources/mp_mercury/mercury_up.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_dn.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_rt.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_lf.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_ft.tga"),
							     _driver->getTexture("./resources/mp_mercury/mercury_bk.tga"));
  _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
  skybox->setVisible(true);
  irr::scene::IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh("./resources/stick.3ds"));
  if (!node)
    throw Error("Could not load stick.3sd");
  node->setPosition(irr::core::vector3df(0,0,-40));
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setFrameLoop(0, 80);
  node->getMaterial(0).setTexture(0, _driver->getTexture("./resources/stick.jpg"));
  node->setScale(irr::core::vector3df(50, 50, 50));
  node->addShadowVolumeSceneNode();
}

void	SelectCharacter::initSpecialEffects(void)
{
  _fireAnim = _smgr->addParticleSystemSceneNode(false);
  irr::scene::IParticleEmitter* em = _fireAnim->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
								 irr::core::vector3df(0.0f,0.06f,0.0f),
								 50,70,
								 irr::video::SColor(0,255,255,255),
								 irr::video::SColor(0,255,255,255),
								 400,1000,0,
								 irr::core::dimension2df(10.f,10.f),
								 irr::core::dimension2df(18.f,18.f));
  _fireAnim->setEmitter(em);
  em->drop();
  irr::scene::IParticleAffector* paf = _fireAnim->createFadeOutParticleAffector();
  _fireAnim->addAffector(paf);
  paf->drop();
  _fireAnim->setPosition(irr::core::vector3df(0,0,-40));
  _fireAnim->setScale(irr::core::vector3df(2,2,2));
  _fireAnim->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _fireAnim->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _fireAnim->setMaterialTexture(0, _core->initTexture("./resources/MainMenu/fire.bmp"));
  _fireAnim->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void	SelectCharacter::run(void)
{
  _warrior->animateEntitySelect();
  _wizard->animateEntitySelect();
  _valkyrie->animateEntitySelect();
  _elf->animateEntitySelect();
  if (!_arrow)
    {
      _arrowMesh = _smgr->addAnimatedMeshSceneNode(_smgr->addArrowMesh("arrow"), 0, 42,
						   irr::core::vector3df(_posArrow[_arrowState], 200 ,80),
						   irr::core::vector3df(195, 0, -5),
						   irr::core::vector3df(70, 70, 70));
      _arrowMesh->getMaterial(0).setTexture(0, _driver->getTexture("./resources/magma.jpg"));
      _arrowMesh->getMaterial(1).setTexture(0, _driver->getTexture("./resources/magma.jpg"));
      _arrowMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _arrow = true;
    }
  _arrowMesh->setPosition(irr::core::vector3df(_posArrow[_arrowState], _arrowMesh->getPosition().Y, _arrowMesh->getPosition().Z));
  _arrowMesh->setRotation(irr::core::vector3df(_arrowMesh->getRotation().X, _arrowMesh->getRotation().Y + 150 * _core->getFrameDeltaTime(), _arrowMesh->getRotation().Z));
  _smgr->drawAll();
  _core->getSoundEventReceiver()->setState(false);
  _core->getSoundEventReceiver()->process(4,true,0.5);
  if ((_core->getEventReceiver()).IsKeyDown(irr::KEY_ESCAPE))
    (_core->changeGameState(Core::MAIN_MENU));
  animationPlayer(_stateWarrior);
  animationPlayer(_stateValkyrie);
  animationPlayer(_stateWizard);
  animationPlayer(_stateElf);
  if ((_core->getEventReceiver()).IsKeyDown(irr::KEY_RETURN) && atLeastOne())
    {
      attributeIA();
      _core->getSoundEventReceiver()->getEngine()->stopAllSounds();
      (_core->changeGameState(Core::IN_GAME));
      _core->getSoundEventReceiver()->setState(false);
      _core->getSoundEventReceiver()->process(2,true,0.1);
      _core->getSoundEventReceiver()->setState(false);
      _core->getSoundEventReceiver()->process(3,true,0.7);
    }
}

bool	SelectCharacter::atLeastOne()
{
  for (int i = 0; i <= 3;++i)
    {
      if (_isBusy.at(i))
	return (true);
    }
  return (false);
}

void	SelectCharacter::attributeIA(void)
{
  for (int i = 0; i <= 3 ;++i)
    {
      if (!_isBusy.at(0) && (!_core->getPlayer(i)->isOccupied()))
	{
	  _core->getPlayer(i)->setEntity(_warrior);
	  _core->getPlayer(i)->setOccupied(true);
	  _isBusy.at(0) = true;
	  _core->getPlayer(i)->setIA(true);
	}
      if (!_isBusy.at(1) && (!_core->getPlayer(i)->isOccupied()))
	{
	  _core->getPlayer(i)->setEntity(_valkyrie);
	  _core->getPlayer(i)->setOccupied(true);
	  _isBusy.at(1) = true;
	  _core->getPlayer(i)->setIA(true);
	}
      if (!_isBusy.at(2) && (!_core->getPlayer(i)->isOccupied()))
	{
	  _core->getPlayer(i)->setEntity(_wizard);
	  _core->getPlayer(i)->setOccupied(true);
	  _isBusy.at(2) = true;
	  _core->getPlayer(i)->setIA(true);
	}
      if (!_isBusy.at(3) && (!_core->getPlayer(i)->isOccupied()))
	{
	  _core->getPlayer(i)->setEntity(_elf);
	  _core->getPlayer(i)->setOccupied(true);
	  _isBusy.at(3) = true;
	  _core->getPlayer(i)->setIA(true);
	}
    }
}

void  SelectCharacter::doKeyboard(bool &state)
{
  switch (_core->getEventReceiver().getCurrentKey())
    {
    case 0x25:
      arrow(stateArrow1, 0);
      break;
    case 0x27:
      arrow(stateArrow2, 1);
      break;
    default:
      break;
    }
  for (int i = 0; i <= 2; ++i)
    {
      if ((_core->getEventReceiver()).IsKeyDown(_core->getKeys()->getIrrlichtKey(_core->getPlayer(i)->getKeys()[4]))
	  && state == false && (!_core->getPlayer(i)->isOccupied()))
	checkBusy(_arrowState, i);
    }
}

void	  SelectCharacter::doJoystick(bool &state)
{
  if (_core->getEventReceiver().getCurrentJoystick() != -1)
    {
      switch (_core->getEventReceiver().getCurrentJoystick())
	{
	case 0x20:
	  arrow(stateArrow1, 0);
	  break;
	case 0x21:
	  arrow(stateArrow1, 1);
	  break;
	default:
	  break;
	}
    }
  for (int i = 3; i <= 3; ++i)
    {
      if (((_core->getEventReceiver()).getCurrentJoystick() == _core->getPlayer(i)->getKeys()[4])
	  && state == false && (!_core->getPlayer(i)->isOccupied()))
	checkBusy(_arrowState, i);
    }
}

void  SelectCharacter::animationPlayer(bool &state)
{
  doKeyboard(state);
  doJoystick(state);
}

void	SelectCharacter::checkBusy(int pos, unsigned int player)
{
  if (pos == 0 && (!_isBusy.at(0)))
    {
      _core->getPlayer(player)->setEntityName("WARRIOR");
      _warrior->setAnimation(true, false, IEntity::SELECT);
      _core->getPlayer(player)->setEntity(_warrior);
      _stateWarrior = true;
      _isBusy.at(0) = true;
      _core->getPlayer(player)->setOccupied(true);
    }
  else if (pos == 1 && (!_isBusy.at(1)))
    {
      _core->getPlayer(player)->setEntityName("VALKYRIE");
      _core->getPlayer(player)->setEntity(_valkyrie);
      _valkyrie->setAnimation(true, false, IEntity::SELECT);
      _isBusy.at(1) = true;
      _stateValkyrie = true;
      _core->getPlayer(player)->setOccupied(true);
    }
  else
    checkBusy2(pos, player);
}

void 		SelectCharacter::checkBusy2(int pos, unsigned int player)
{
  if (pos == 2 && (!_isBusy.at(2)))
    {
      _core->getPlayer(player)->setEntityName("WIZARD");
      _core->getPlayer(player)->setEntity(_wizard);
      _wizard->setAnimation(true, false, IEntity::SELECT);
      _isBusy.at(2) = true;
      _stateWizard = true;
      _core->getPlayer(player)->setOccupied(true);
    }
  else if (pos == 3  && (!_isBusy.at(3)))
    {
      _core->getPlayer(player)->setEntityName("ELF");
      _elf->setAnimation(true, false, IEntity::SELECT);
      _core->getPlayer(player)->setEntity(_elf);
      _isBusy.at(3) = true;
      _stateElf = true;
      _core->getPlayer(player)->setOccupied(true);
    }
}

void  SelectCharacter::arrow(bool &state, int pos)
{
  if (state == false)
    {
      switchArrow(pos);
      _timeFirst = _device->getTimer()->getTime();
      state = true;
    }
  else
    {
      _timeThen = _device->getTimer()->getTime();
      if ((_timeThen - _timeFirst) > 100)
	state = false;
    }
}

void	SelectCharacter::switchArrow(unsigned int type)
{
  if (type == 0)
    {
      if (_arrowState == 0)
	_arrowState = 3;
      else
	--_arrowState;
    }
  else
    {
      if (_arrowState == 3)
	_arrowState = 0;
      else
	++_arrowState;
    }
}

void	SelectCharacter::stop(void)
{
  _isBusy.clear();
}
