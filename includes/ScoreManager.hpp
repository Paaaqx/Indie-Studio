//
// ScoreManager.hpp for scoremanager.hpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Thu May  4 17:23:04 2017 Anthony
// Last update Fri Jun 16 12:01:33 2017 Anthony
//

#ifndef SCOREMANAGER_HPP_
# define SCOREMANAGER_HPP_

# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>

class				ScoreManager
{
public:
  class				teamScore
  {
  public:
    std::string			teamName;
    std::string			scoreWarrior;
    std::string			scoreValkyrie;
    std::string			scoreWizard;
    std::string			scoreElf;
  };
  class				highScore
  {
  public:
    highScore();
    highScore(highScore const& other);
    highScore operator=(highScore const& other);
    ~highScore();

  public:
    std::string			getTeamName(unsigned int rank) const;
    std::string			getTeamScore(unsigned int rank) const;
    int				getSize() const;

  private:
    void			loadTeam();
    void			sortTeam();

  private:
   bool				verifyScore(std::string score) const;
    
  private:
    std::vector<std::string>	teamName;
    std::vector<std::string>	teamScore;

  };

public:
  ScoreManager(std::string const& _teamName);
  ~ScoreManager(){};

public:
  teamScore			getCurrentTeamScore() const;
  highScore			getHighScore() const;
  void				loadScore();
  std::ifstream			createFile() const;
  void				putTeamScore() const;
  void				addToScore(std::string const& heroName,
					   int scoreToAdd);

private:
  void				heroAddScore(std::string const& heroName,
					     int scoreToAdd);

private:
  highScore			score;
  teamScore			currentTeamScore;
};

#endif /* !SCOREMANAGER_HPP_ */
