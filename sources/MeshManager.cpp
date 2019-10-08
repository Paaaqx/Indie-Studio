//
// MeshManager.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
// 
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
// 
// Started on  Wed May 31 15:52:26 2017 Mex
// Last update Wed May 31 16:09:27 2017 Mex
//

#include "MeshManager.hpp"

MeshManager::MeshManager(irr::scene::IAnimatedMeshSceneNode* mesh, irr::s32 ID, Core* core) : _mesh(mesh), _ID(ID), _core(core){}

MeshManager::~MeshManager(){}

irr::scene::IAnimatedMeshSceneNode*	MeshManager::getMesh(void) const
{
  return (_mesh);
}

irr::s32	MeshManager::getID(void) const
{
  return (_ID);
}
										
