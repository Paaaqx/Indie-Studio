//
// Intro.hpp for  in /home/marti7/rendu/c++/cpp_indie_studio
//
// Made by Raphaël Martins
// Login   <raphael.martins@epitech.eu>
//
// Started on  Tue Jun  6 16:53:48 2017 Raphaël Martins
// Last update Sun Jun 18 20:59:55 2017 Anthony
//

#ifndef INTRO_HPP_
# define INTRO_HPP_

#include "Core.hpp"

class					 Intro : public IGamePhase
{

public:
    Intro(Core* core);
    ~Intro();
    void				init(void) override;
    void				run(void) override;
    void				stop(void) override;
    Core*				getCore(void);
    irr::video::IVideoDriver*		getDriver(void);
    irr::IrrlichtDevice*		getDevice(void);
    irr::scene::ISceneManager*		getScene(void);
    void				runTitle(void);
    void				verifTime(void);
    void				setPosition(irr::core::vector3df pos);
    void				fist_mesh(irr::core::vector3df pos, irr::core::vector3df rot);
    irrklang::ISoundEngine*		getSoundEngine(void) const;
    void				setSoundEngine(irrklang::ISoundEngine* _sound);

  private:
    Core*				_core;
    irr::IrrlichtDevice*		_device;
    irr::video::IVideoDriver*		_driver;
    irr::scene::ISceneManager*		_smgr;
    irr::scene::IAnimatedMeshSceneNode*	_fist_mesh;
    irr::core::vector3df		_pos;
    irr::video::ITexture*		_intro_title;
    irr::video::ITexture*		_introLogo;
    irr::scene::ICameraSceneNode*	_camera;
    bool				_state;
    irr::u32				_timeStart;
    int					_alpha;
};

#endif
