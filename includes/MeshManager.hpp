//
// MeshManager.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Wed May 31 16:06:12 2017 Mex
// Last update Sun Jun 18 11:56:33 2017 Mex
//

#ifndef MESHMANAGER_HPP_
# define MESHMANAGER_HPP_

#include "Map.hpp"

class					MeshManager
{
public:
  MeshManager(irr::scene::IAnimatedMeshSceneNode* mesh, irr::s32 ID, Core* core);
  ~MeshManager();

public:
  irr::scene::IAnimatedMeshSceneNode*	getMesh(void) const;
  irr::s32				getID(void) const;

private:
  irr::scene::IAnimatedMeshSceneNode*   _mesh;
  irr::s32                              _ID;
  Core*					_core;
};

#endif /* !MESHMANAGER_HPP_ */
