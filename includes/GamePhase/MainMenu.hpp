//
// MainMenu.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Wed May  3 16:42:26 2017 Mex
// Last update Sun Jun 18 22:35:04 2017 Anthony
//

#ifndef MAINMENU_HPP_
# define MAINMENU_HPP_

# include "Core.hpp"
# include "KeySelector.hpp"
# include <IGUIEnvironment.h>
# include <ScoreManager.hpp>
# include <chrono>
# include <thread>

class					MainMenu : public IGamePhase
{
public:
  MainMenu(Core* core);
  ~MainMenu();

public:
    enum				MainMenuState
    {
      MAIN_MENU = 0,
      HIGH_SCORE = 1,
      OPTIONS = 2,
      TEAM_SELECT = 3,
      EXIT = 4,
    };
  enum					Player
    {
      PLAYER1 = 0,
      PLAYER2,
      PLAYER3,
      PLAYER4,
      UNKNOWN
    };

public:
  void					init(void) override;
  void					run(void) override;
  void					stop(void) override;
  Core*					getCore(void);
  irr::scene::IParticleSystemSceneNode*	getFireAnim(void);
  MainMenuState				getState(void);
  Player				getPlayer(void);
  irr::video::IVideoDriver*		getDriver(void);
  void					setState(MainMenuState state);
  void					setOptionState(bool _optionState);
  void					setPlayer(Player player);
  void					setKeys(int index, bool state);
  void					saveKeys(int i, Player player, int key);
  bool					getKeys(int index);
  bool					getOptionState(void);
  std::string const&			getTeamName(void) const;
  void					setTeamName(std::string const teamName);
  irr::scene::ISceneNode*		getArrowMesh(void) const;
  void					setArrow(bool const state);
  void					switchArrow(unsigned int type);
  void					switchLetter(unsigned int type);
  irrklang::ISoundEngine*		getSoundEngine(void) const;
  void					setSoundEngine(irrklang::ISoundEngine* _sound);

private:
  void					runMainMenu(void);
  void					runHighScore(void);
  void					runOptions(void);
  void					runTeamSelect(void);
  void					init2DTextures(void);
  void					initSpecialEffect(void);
  void					eventResponse(void);
  void					showKeys(std::vector<int> keys);
  void					showJoyStick(std::vector<int> keys);
  void					letterAndArrow(bool &state, int pos, std::string type);

private:
  Core*					_core;
  irr::IrrlichtDevice*			_device;
  irr::video::IVideoDriver*		_driver;
  irr::video::ITexture*			_mouse;
  irr::video::ITexture*			_title;
  irr::video::ITexture*			_goBackward;
  irr::video::ITexture*			_goForward;
  irr::video::ITexture*			_goLeft;
  irr::video::ITexture*			_goRight;
  irr::video::ITexture*			_attack;
  irr::video::ITexture*			_useObject;
  irr::video::ITexture*			_enterKeyButton;
  irr::video::ITexture*			_playButton;
  irr::video::ITexture*			_hsButton;
  irr::video::ITexture*			_saveButton;
  irr::video::ITexture*			_optionsButton;
  irr::video::ITexture*			_exitButton;
  irr::video::ITexture*			_teamNameButton;
  irr::video::ITexture*			_returnButton;
  irr::video::ITexture*			_player1;
  irr::video::ITexture*			_player2;
  irr::video::ITexture*			_player3;
  irr::video::ITexture*			_player4;
  irr::scene::ISceneManager*		_smgr;
  irr::scene::ICameraSceneNode*		_camera;
  irr::scene::IParticleSystemSceneNode*	_fireAnim;
  irr::gui::IGUIFont*			_font;
  irr::gui::IGUIFont*			_teamFont;
  irr::scene::ISceneNode*		_arrowMesh;
  std::vector<int>			_posArrow;
  unsigned int				_arrowState;
  std::string				_teamName;
  bool					_arrow;
  MainMenuState				_state;
  Player				_player;
  bool					_keyState;
  bool					_optionState;
  int					_keys[5];
  irr::u32				_timeThen;
  irr::u32				_timeFirst;
  bool					stateArrow1;
  bool					stateArrow2;
  bool					stateLetter1;
  bool					stateLetter2;
};

#endif /* !MAINMENU_HPP_ */
