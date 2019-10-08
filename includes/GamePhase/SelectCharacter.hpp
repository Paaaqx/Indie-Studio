//
// SelectCharacter.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Tue May  9 16:01:31 2017 Mex
// Last update Fri Jun 16 14:34:48 2017 Anthony
//

#ifndef SELECTCHARACTER_HPP_
# define SELECTCHARACTER_HPP_

# include "Elf.hpp"
# include "Warrior.hpp"
# include "Wizard.hpp"
# include "Valkyrie.hpp"
# include "KeySelector.hpp"

class					SelectCharacter : public IGamePhase
{
public:
  SelectCharacter(Core *core);
  ~SelectCharacter();

public:
  void					init(void) override;
  void					run(void) override;
  void					stop(void) override;

private:
  void					initSpecialEffects(void);
  void					initMeshs(void);
  void					initEntities(void);
  void					initPlayers(void);
  void 					animationPlayer(bool &state);
//  void					animationPlayer(IEntity *type, bool& state);
  void 					arrow(bool &state, int pos);
  void 					switchArrow(unsigned int type);
  void 					checkBusy(int pos, unsigned int player);
  void 					checkBusy2(int pos, unsigned int player);
  void 					attributeIA(void);
  bool 					atLeastOne(void);
  void					doKeyboard(bool &state);
  void					doJoystick(bool &state);

private:
  Core*					_core;
  irr::IrrlichtDevice*			_device;
  irr::video::IVideoDriver*		_driver;
  irr::scene::ISceneManager*		_smgr;
  irr::scene::ICameraSceneNode*		_camera;
  irr::scene::IParticleSystemSceneNode*	_fireAnim;
  IEntity*				_warrior;
  IEntity*				_valkyrie;
  IEntity*				_wizard;
  IEntity*				_elf;
  unsigned int				_currentPlayer;
  bool					_stateWarrior;
  bool					_stateValkyrie;
  bool					_stateWizard;
  bool					_stateElf;
  irr::scene::ISceneNode*		_arrowMesh;
  std::vector<int>			_posArrow;
  std::vector<bool>			_isBusy;
  unsigned int				_arrowState;
  bool					_arrow;
  irr::u32				_timeThen;
  irr::u32				_timeFirst;
  bool					stateArrow1;
  bool					stateArrow2;
};

#endif /* !SELECTCHARACTER_HPP_ */
