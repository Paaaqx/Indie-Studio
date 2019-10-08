//
// Player.hpp for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
//
// Made by Mex
// Login   <maximilien.oteifeh-pfennig@epitech.eu>
//
// Started on  Wed May 10 15:04:25 2017 Mex
// Last update Sun Jun 18 21:29:45 2017 Anthony
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP

# include "IEntity.hpp"

class				Player
{
public:
  Player();
  ~Player();

public:
  IEntity*			getEntity(void) const;
  void				setEntity(IEntity* entity);
  std::string			getEntityName(void) const;
  void				setEntityName(const std::string entityName);
  std::vector<int> const&	getKeys(void) const;
  void				setKeys(std::vector<int> const& keys);
  bool				getAI() const;
  bool const&			isActive(void) const;
  bool const&			isOccupied(void) const;
  void 				setOccupied(bool const& state);
  void 				setIA(bool ia);
  bool const&			isIA() const;

private:
  IEntity*			_entity;
  std::string			_entityName;
  std::vector<int>		_keys;
  bool				_active;
  bool				_IA;
  bool				_isOccupied;
};

#endif /* !PLAYER_HPP_ */
