//
// MainMenu.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Wed May  3 16:43:13 2017 Mex
// Last update Sun Jun 18 22:35:20 2017 Anthony
//

#include "MouseEvent.hpp"
#include "MainMenu.hpp"

MainMenu::MainMenu(Core *core)
{
  _state = MainMenu::MAIN_MENU;
  _core = core;
  _device = (_core->getDevice());
  _driver = (_core->getDriver());
  _smgr = (_core->getScene());
}

MainMenu::~MainMenu(){}

void		MainMenu::init(void)
{
  _state = MainMenu::MAIN_MENU;
  _device->setWindowCaption(L"Gantelet : Main Menu");
  init2DTextures();
  _device->getCursorControl()->setVisible(false);
  _smgr->clear();
  initSpecialEffect();
  _font = _device->getGUIEnvironment()->getFont("./resources/myfont.xml");
  if (!_font)
    throw Error ("Could not load myfont.png");
  _teamFont = _device->getGUIEnvironment()->getFont("./resources/myfont.xml");
  if (!_teamFont)
    throw Error ("Could not load myfont.xml");
  _camera = _smgr->addCameraSceneNode(0, irr::core::vector3df(-50,50,-150));
  _player = MainMenu::UNKNOWN;
  _keyState = false;
  _optionState = false;
  for (int i = 0; i <= 5; ++i)
    _keys[i] = false;
  _posArrow.emplace_back(-71);
  _posArrow.emplace_back(-52);
  _posArrow.emplace_back(-30);
  _arrowState = 0;
  _arrow = false;
  _teamName = "AAA";
  stateArrow1 = false;
  stateArrow2 = false;
  stateLetter1 = false;
  stateLetter2 = false;
}

void		MainMenu::init2DTextures(void)
{
  _mouse = _core->initTexture("./resources/MainMenu/mouseCursor.png");
  _title = _core->initTexture("./resources/MainMenu/titre.png");
  _playButton = _core->initTexture("./resources/MainMenu/play.png");
  _hsButton = _core->initTexture("./resources/MainMenu/high_score.png");
  _optionsButton = _core->initTexture("./resources/MainMenu/options.png");
  _exitButton = _core->initTexture("./resources/MainMenu/exit.png");
  _teamNameButton = _core->initTexture("./resources/MainMenu/teamName.png");
  _returnButton = _core->initTexture("./resources/MainMenu/arrow.png");
  _saveButton = _core->initTexture("./resources/MainMenu/save.png");
  _goBackward = _core->initTexture("./resources/MainMenu/Options/go_backward.png");
  _goForward = _core->initTexture("./resources/MainMenu/Options/go_forward.png");
  _goLeft = _core->initTexture("./resources/MainMenu/Options/turn_left.png");
  _goRight = _core->initTexture("./resources/MainMenu/Options/turn_right.png");
  _attack = _core->initTexture("./resources/MainMenu/Options/attack.png");
  _useObject = _core->initTexture("./resources/MainMenu/Options/use_object.png");
  _player1 = _core->initTexture("./resources/MainMenu/Options/Player1.png");
  _player2 = _core->initTexture("./resources/MainMenu/Options/Player2.png");
  _player3 = _core->initTexture("./resources/MainMenu/Options/Player3.png");
  _player4 = _core->initTexture("./resources/MainMenu/Options/Player4.png");
  _enterKeyButton = _core->initTexture("./resources/MainMenu/Options/enter_key.png");

  _driver->makeColorKeyTexture(_mouse, irr::core::position2d<irr::s32>(0,0));
  _driver->makeColorKeyTexture(_title, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_playButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_saveButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_hsButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_optionsButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_exitButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_teamNameButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_returnButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_goBackward, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_goForward, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_goLeft, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_goRight, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_attack, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_enterKeyButton, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_useObject, irr::video::SColor(0,0,0,0));

  _driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
  _driver->getMaterial2D().AntiAliasing = irr::video::EAAM_FULL_BASIC;
}

void	MainMenu::initSpecialEffect(void)
{
  _fireAnim = _smgr->addParticleSystemSceneNode(false);
  irr::scene::IParticleEmitter* em = _fireAnim->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7),
								 irr::core::vector3df(0.0f,0.06f,0.0f),
								 90,110,
								 irr::video::SColor(0,255,255,255),
								 irr::video::SColor(0,255,255,255),
								 1400,2000,80,
								 irr::core::dimension2df(5.f,5.f),
								 irr::core::dimension2df(15.f,15.f));
  _fireAnim->setEmitter(em);
  em->drop();
  irr::scene::IParticleAffector* paf = _fireAnim->createFadeOutParticleAffector();
  _fireAnim->addAffector(paf);
  paf->drop();
  _fireAnim->setPosition(irr::core::vector3df(-40,-240,40));
  _fireAnim->setScale(irr::core::vector3df(60,20,20));
  _fireAnim->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _fireAnim->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  _fireAnim->setMaterialTexture(0, _driver->getTexture("./resources/MainMenu/fire.bmp"));
  _fireAnim->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void				MainMenu::runHighScore(void)
{
  irr::gui::IGUIEnvironment*	guienv = (_core->getDevice())->getGUIEnvironment();
  ScoreManager			score("");
  ScoreManager::highScore	scoreTeam;
  std::string			teamName;
  std::string			teamScore;
  std::string			clas;
  int				j = 0;

  scoreTeam = score.getHighScore();
  while (j < 5)
    {
      std::stringstream convert;
      std::wstring wTeamName;
      std::wstring wTeamScore;
      std::wstring wClass;
      teamName = scoreTeam.getTeamName(j);
      teamScore = scoreTeam.getTeamScore(j);
      convert << (j + 1);
      clas = convert.str();
      wTeamName.assign(teamName.begin(), teamName.end());
      wTeamScore.assign(teamScore.begin(), teamScore.end());
      wClass.assign(clas.begin(), clas.end());
      _font->draw(irr::core::stringw(wClass.c_str()),
		  irr::core::rect<irr::s32>(500, 450 + (j * 90), 700, 500 + (j * 90)),
		  irr::video::SColor(255, 255, 255, 255));
      if (teamName != "" && teamScore != "")
	{
	  _font->draw(irr::core::stringw(wTeamName.c_str()),
		      irr::core::rect<irr::s32>(800, 450 + (j * 90), 1000, 500 + (j * 90)),
		      irr::video::SColor(255, 255, 255, 255));
	  _font->draw(irr::core::stringw(wTeamScore.c_str()),
		      irr::core::rect<irr::s32>(1000, 450 + (j * 90), 1300, 500 + (j * 90)),
		      irr::video::SColor(255, 255, 255, 255));
	}
      ++j;
    }
  guienv->drawAll();
  _driver->draw2DImage(_title, irr::core::position2d<irr::s32>(582,80), irr::core::rect<irr::s32>(0,0,732,96), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_hsButton, irr::core::position2d<irr::s32>(675,300), irr::core::rect<irr::s32>(0,0,570,60), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_returnButton, irr::core::position2d<irr::s32>(150,900), irr::core::rect<irr::s32>(0,0,75,60), 0, irr::video::SColor(255,255,255,255), true);
}

void				MainMenu::runOptions(void)
{
  _driver->makeColorKeyTexture(_player1, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_player2, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_player3, irr::video::SColor(0,0,0,0));
  _driver->makeColorKeyTexture(_player4, irr::video::SColor(0,0,0,0));

  _driver->draw2DImage(_title, irr::core::position2d<irr::s32>(582,80), irr::core::rect<irr::s32>(0,0,732,96), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_optionsButton, irr::core::position2d<irr::s32>(769,300), irr::core::rect<irr::s32>(0,0,383,60), 0, irr::video::SColor(255,255,255,255), true);

  _driver->draw2DImage(_player1, irr::core::position2d<irr::s32>(400,450), irr::core::rect<irr::s32>(0,0, 57, 37), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_player2, irr::core::position2d<irr::s32>(400,550), irr::core::rect<irr::s32>(0,0, 57, 37), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_player3, irr::core::position2d<irr::s32>(400,650), irr::core::rect<irr::s32>(0,0, 57, 37), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_player4, irr::core::position2d<irr::s32>(400,750), irr::core::rect<irr::s32>(0,0, 57, 37), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_returnButton, irr::core::position2d<irr::s32>(150,900), irr::core::rect<irr::s32>(0,0,75,60), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_saveButton,irr::core::position2d<irr::s32>(1500,900), irr::core::rect<irr::s32>(0,0,240,60),0,irr::video::SColor(255,255,255,255), true);

  if (_player != MainMenu::UNKNOWN)
    {
      _driver->draw2DImage(_goLeft,irr::core::position2d<irr::s32>(582,450), irr::core::rect<irr::s32>(0,0,270,30),0,irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goRight,irr::core::position2d<irr::s32>(1182,450),irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goForward,irr::core::position2d<irr::s32>(582,550), irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goBackward,irr::core::position2d<irr::s32>(1182,550), irr::core::rect<irr::s32>(0,0,330,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_attack,irr::core::position2d<irr::s32>(582,650), irr::core::rect<irr::s32>(0,0,180,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_useObject,irr::core::position2d<irr::s32>(1182,650), irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goLeft,irr::core::position2d<irr::s32>(582,450), irr::core::rect<irr::s32>(0,0,270,30),0,irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goRight,irr::core::position2d<irr::s32>(1182,450),irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goForward,irr::core::position2d<irr::s32>(582,550), irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_goBackward,irr::core::position2d<irr::s32>(1182,550), irr::core::rect<irr::s32>(0,0,330,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_attack,irr::core::position2d<irr::s32>(582,650), irr::core::rect<irr::s32>(0,0,180,30),0, irr::video::SColor(255,255,255,255), true);
      _driver->draw2DImage(_useObject,irr::core::position2d<irr::s32>(1182,650), irr::core::rect<irr::s32>(0,0,300,30),0, irr::video::SColor(255,255,255,255), true);
      switch (_player)
	{
	case PLAYER1:
	  showKeys(_core->getKeys()->keysPlayer1);
	  break;
	case PLAYER2:
	  showKeys(_core->getKeys()->keysPlayer2);
	  break;
	case PLAYER3:
	  showKeys(_core->getKeys()->keysPlayer3);
	  break;
	case PLAYER4:
	  showJoyStick(_core->getKeys()->joysticksPlayer4);
	  break;
	case UNKNOWN:
	  break;
	}
    }
}

void	MainMenu::runTeamSelect(void)
{
  if (!_arrow)
    {
      _arrowMesh = _smgr->addAnimatedMeshSceneNode(_smgr->addArrowMesh("arrow"), 0, 42,
						   irr::core::vector3df(_posArrow[_arrowState], 16 ,0),
						   irr::core::vector3df(195, 0, -5),
						   irr::core::vector3df(15, 15, 15));
      _arrowMesh->getMaterial(0).setTexture(0, _driver->getTexture("./resources/magma.jpg"));
      _arrowMesh->getMaterial(1).setTexture(0, _driver->getTexture("./resources/magma.jpg"));
      _arrowMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _arrow = true;
    }
  _driver->draw2DImage(_title, irr::core::position2d<irr::s32>(582,80), irr::core::rect<irr::s32>(0,0,732,96), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_teamNameButton, irr::core::position2d<irr::s32>(565, 350), irr::core::rect<irr::s32>(0,0,791,40), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_saveButton,irr::core::position2d<irr::s32>(1500,900), irr::core::rect<irr::s32>(0,0,240,60),0,irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_returnButton, irr::core::position2d<irr::s32>(150,900), irr::core::rect<irr::s32>(0,0,75,60), 0, irr::video::SColor(255,255,255,255), true);
  _device->getGUIEnvironment()->clear();
  _teamFont->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(_teamName.at(0)).c_str()).c_str(),
		  irr::core::rect<irr::s32>(700,600,0,0),
		  irr::video::SColor(255,255,255,255));
  _teamFont->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(_teamName.at(1)).c_str()).c_str(),
		  irr::core::rect<irr::s32>(800,600,0,0),
		  irr::video::SColor(255,255,255,255));
  _teamFont->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(_teamName.at(2)).c_str()).c_str(),
		  irr::core::rect<irr::s32>(900,600,0,0),
		  irr::video::SColor(255,255,255,255));
  _arrowMesh->setPosition(irr::core::vector3df(_posArrow[_arrowState], _arrowMesh->getPosition().Y, _arrowMesh->getPosition().Z));
  _arrowMesh->setRotation(irr::core::vector3df(_arrowMesh->getRotation().X, _arrowMesh->getRotation().Y + 150 * _core->getFrameDeltaTime(), _arrowMesh->getRotation().Z));
}

void	MainMenu::showKeys(std::vector<int> keys)
{
  _device->getGUIEnvironment()->clear();
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(0)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,490,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(1)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,490,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(2)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,590,0,0),
	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(3)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,590,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(4)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,690,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedKey(keys.at(5)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,690,0,0),
  	      irr::video::SColor(255,255,255,255));
}

void	MainMenu::showJoyStick(std::vector<int> keys)
{
  _device->getGUIEnvironment()->clear();
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(0)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,490,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(1)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,490,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(2)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,590,0,0),
	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(3)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,590,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(4)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(582,690,0,0),
  	      irr::video::SColor(255,255,255,255));
  _font->draw(irr::core::stringw(_core->getKeys()->getTranslatedJoyStick(keys.at(5)).c_str()).c_str(),
  	      irr::core::rect<irr::s32>(1182,690,0,0),
  	      irr::video::SColor(255,255,255,255));
}

void	MainMenu::runMainMenu(void)
{
  _driver->draw2DImage(_title, irr::core::position2d<irr::s32>(582,80), irr::core::rect<irr::s32>(0,0,732,96), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_playButton, irr::core::position2d<irr::s32>(844,350), irr::core::rect<irr::s32>(0,0,233,60), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_hsButton, irr::core::position2d<irr::s32>(675,500), irr::core::rect<irr::s32>(0,0,570,60), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_optionsButton, irr::core::position2d<irr::s32>(769,650), irr::core::rect<irr::s32>(0,0,383,60), 0, irr::video::SColor(255,255,255,255), true);
  _driver->draw2DImage(_exitButton, irr::core::position2d<irr::s32>(859,800), irr::core::rect<irr::s32>(0,0,203,60), 0, irr::video::SColor(255,255,255,255), true);
  _core->getSoundEventReceiver()->process(1,true,0.8);
}

void	MainMenu::eventResponse(void)
{
  if ((_core->getEventReceiver()).IsKeyDown(irr::KEY_ESCAPE))
    (_core->changeGameState(Core::EXIT));
  if (((_core->getEventReceiver()).getLeftMouseState()))
    {
      MouseEvent	event(this);
      event.mainMenuButton();
    }
  if (_optionState == true && _state == OPTIONS && _player != UNKNOWN)
    _driver->draw2DImage(_enterKeyButton,irr::core::position2d<irr::s32>(600,900), irr::core::rect<irr::s32>(0,0,662,60),0, irr::video::SColor(255,255,255,255), true);
  if (_core->getEventReceiver().getCurrentKey() != -1)
    {
      for (int i = 0; i <= 5;++i)
	{
	  if (_keys[i] == true && _player != UNKNOWN)
	    {
	      saveKeys(i, _player, _core->getEventReceiver().getCurrentKey());
	      setKeys(i,false);
	    }
	  setOptionState(false);
	}
    }
  if (_state == TEAM_SELECT)
    {
      switch (_core->getEventReceiver().getCurrentKey())
	{
	case 0x25:
	  letterAndArrow(stateArrow1, 0, "Arrow");
	  break;
	case 0x27:
	  letterAndArrow(stateArrow2, 1, "Arrow");
	  break;
	case 0x26:
	  letterAndArrow(stateLetter1, 0, "Letter");
	  break;
	case 0x28:
	  letterAndArrow(stateLetter2, 1, "Letter");
	default:
	  break;
	}
    }
}

void  MainMenu::letterAndArrow(bool &state, int pos, std::string type)
{
  if (state == false)
    {
      if (type == "Letter")
	switchLetter(pos);
      else
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

void	MainMenu::saveKeys(int i, Player player, int key)
{
  switch(player)
    {
    case PLAYER1:
      _core->getKeys()->keysPlayer1.at(i) = key;
      break;
    case PLAYER2:
      _core->getKeys()->keysPlayer2.at(i) = key;
      break;
    case PLAYER3:
      _core->getKeys()->keysPlayer3.at(i) = key;
      break;
    case PLAYER4:
      _core->getKeys()->joysticksPlayer4.at(i) = key;
      break;
    case UNKNOWN:
      break;
    }
}

void	MainMenu::run(void)
{
  _smgr->drawAll();
  switch(_state)
    {
    case MainMenu::MAIN_MENU:
      runMainMenu();
      break;
    case MainMenu::HIGH_SCORE:
      runHighScore();
      break;
    case MainMenu::OPTIONS:
      runOptions();
      break;
    case MainMenu::TEAM_SELECT:
      runTeamSelect();
      break;
    case MainMenu::EXIT:
      break;
    }
  irr::core::position2d<irr::s32> mouse = _device->getCursorControl()->getPosition();
  _driver->draw2DImage(_mouse, irr::core::position2d<irr::s32>(mouse.X - 1,mouse.Y - 3), irr::core::rect<irr::s32>(0,0,50,50), 0, irr::video::SColor(255,255,255,255), true);
  eventResponse();
}

void	MainMenu::stop(void)
{
  _driver->removeTexture(_title);
  _driver->removeTexture(_mouse);
  _driver->removeTexture(_playButton);
  _driver->removeTexture(_hsButton);
  _driver->removeTexture(_saveButton);
  _driver->removeTexture(_optionsButton);
  _driver->removeTexture(_exitButton);
  _driver->removeTexture(_teamNameButton);
  _driver->removeTexture(_returnButton);
  _driver->removeTexture(_goLeft);
  _driver->removeTexture(_goRight);
  _driver->removeTexture(_goForward);
  _driver->removeTexture(_goBackward);
  _driver->removeTexture(_attack);
  _driver->removeTexture(_useObject);
  _driver->removeTexture(_player1);
  _driver->removeTexture(_player2);
  _driver->removeTexture(_player3);
  _driver->removeTexture(_player4);
  _driver->removeTexture(_enterKeyButton);
}

Core*	MainMenu::getCore(void)
{
  return (_core);
}

irr::scene::IParticleSystemSceneNode*	MainMenu::getFireAnim(void)
{
  return (_fireAnim);
}

MainMenu::MainMenuState	MainMenu::getState(void)
{
  return (_state);
}

MainMenu::Player	MainMenu::getPlayer(void)
{
  return (_player);
}

void	MainMenu::setState(MainMenuState state)
{
  _state = state;
}

void	MainMenu::setPlayer(Player player)
{
  _player = player;
}

void	MainMenu::setKeys(int i, bool state)
{
  _keys[i] = state;
}

void	MainMenu::setOptionState(bool state)
{
  _optionState = state;
}

bool	MainMenu::getKeys(int i)
{
  return(_keys[i]);
}

irr::video::IVideoDriver*	MainMenu::getDriver(void)
{
  return (_driver);
}

void	MainMenu::setTeamName(std::string const teamName)
{
  _teamName = teamName;
}

std::string const&	MainMenu::getTeamName(void) const
{
  return (_teamName);
}

void	MainMenu::switchArrow(unsigned int type)
{
  if (type == 0)
    {
      if (_arrowState == 0)
	_arrowState = 2;
      else
	--_arrowState;
    }
  else
    {
      if (_arrowState == 2)
	_arrowState = 0;
      else
	++_arrowState;
    }
}

void	MainMenu::switchLetter(unsigned int type)
{
  if (type == 0)
    {
      if (_teamName[_arrowState] == 'Z')
	_teamName[_arrowState] = 'A';
      else
	++_teamName[_arrowState];
    }
  else
    {
      if (_teamName[_arrowState] == 'A')
	_teamName[_arrowState] = 'Z';
      else
	--_teamName[_arrowState];
    }
}

void	MainMenu::setArrow(bool state)
{
  _arrow = state;
}

irr::scene::ISceneNode*		MainMenu::getArrowMesh(void) const
{
  return (_arrowMesh);
}
