//
// Player.cpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Mon May 22 16:43:17 2017 Mex
// Last update Sun Jun 18 21:59:26 2017 Anthony
//

#include "Player.hpp"

Player::Player()
{
  _entity = NULL;
  _entityName = "Unknown";
  _active = false;
  _IA = false;
}

Player::~Player(){}

IEntity*	Player::getEntity(void) const
{
  return (_entity);
}

void	Player::setEntity(IEntity* entity)
{
  _entity = entity;
  _active = true;
}

std::string	Player::getEntityName(void) const
{
  return (_entityName);
}

void	Player::setEntityName(const std::string entityName)
{
  _entityName = entityName;
}

std::vector<int> const&	Player::getKeys(void) const
{
  return (_keys);
}

void	Player::setKeys(std::vector<int> const& keys)
{
  _keys = keys;
}

bool const&	Player::isActive(void) const
{
  return (_active);
}

bool const& Player::isOccupied(void) const
{
  return (_isOccupied);
}

bool const& Player::isIA(void) const
{
  return (_IA);
}

void	Player::setOccupied(bool const& state)
{
  _isOccupied = state;
}

void	Player::setIA(bool ia)
{
  _IA = ia;
}

bool 	Player::getAI() const
{
  return (_IA);
}
