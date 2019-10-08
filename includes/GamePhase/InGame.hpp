//
// InGame.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Tue May  9 15:33:25 2017 Mex
// Last update Tue Aug 15 10:32:31 2017 Paqx
//

#ifndef INGAME_HPP_
# define INGAME_HPP_

# include "Monster.hpp"
# include "ThreadPool.hpp"

typedef struct				s_Life
{
  int					warriorLife;
  int					elfLife;
  int					valkyrieLife;
  int					wizardLife;
}					t_Life;

class					InGame : public IGamePhase
{
public:
  InGame(Core *core);
  ~InGame();

public:
  void					init(void) override;
  void					run(void) override;
  void					stop(void) override;
  void					initPlayers(void);
  void					initHud(void);
  void					initPlayersLifeBar(void);
  void					displayPlayersIcon(void);
  void					displayWarriorLife(void);
  void					displayElfLife(void);
  void					displayWizardLife(void);
  void					displayValkyrieLife(void);
  void					movePlayers(void);
  void					restartLevel(void);
  void					keyFct(void);
  void					moveInGame(Player*& player);
  void					draw(void);

private:
  Core*					_core;
  irr::IrrlichtDevice*			_device;
  irr::video::IVideoDriver*		_driver;
  irr::video::ITexture*			_mouse;
  irr::video::ITexture*			_back;
  irr::video::ITexture*			_pause;
  irr::scene::ISceneManager*		_smgr;
  irr::scene::ICameraSceneNode*		_camera;
  irr::video::ITexture*			_icon4;
  irr::video::ITexture*			_icon3;
  irr::video::ITexture*			_icon2;
  irr::video::ITexture*			_icon1;
  irr::video::ITexture*			_red_life_bar;
  irr::video::ITexture*			_green_life_bar;
  irr::core::position2d<irr::s32>	_position_up_left;
  irr::core::position2d<irr::s32>	_position_down_right_warrior;
  irr::core::position2d<irr::s32>	_position_down_right_elf;
  irr::core::position2d<irr::s32>	_position_down_right_valkyrie;
  irr::core::position2d<irr::s32>	_position_down_right_wizard;
  irr::core::rect<irr::s32>		_rectangle;
  Map*					_map;
  std::vector<Player*>			_player;
  unsigned int				_playerNbr;
  unsigned int				_actualPlayer;
  IEntity*				_monsterTest;
  bool					_pauseState;
  irr::u32				_startTime;
};

#endif /* !INGAME_HPP_ */
