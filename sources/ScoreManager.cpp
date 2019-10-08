//
// ScoreManager.cpp for scoremanager.cpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
// 
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
// 
// Started on  Thu May  4 17:22:46 2017 Anthony
// Last update Sun Jun 18 22:17:07 2017 Anthony
//

#include <algorithm>
#include "Errors.hpp"
#include "ScoreManager.hpp"

ScoreManager::ScoreManager(std::string const& _teamName)
{
  currentTeamScore.teamName = _teamName;
  currentTeamScore.scoreWarrior = "0";
  currentTeamScore.scoreValkyrie = "0";
  currentTeamScore.scoreWizard = "0";
  currentTeamScore.scoreElf = "0";
  loadScore();
}


ScoreManager::teamScore	ScoreManager::getCurrentTeamScore() const
{
  return (currentTeamScore);
}

ScoreManager::highScore	ScoreManager::getHighScore() const
{
  return (score);
}

void		ScoreManager::loadScore()
{
  std::string	line;
  std::ifstream	file(createFile());

  while	(getline(file, line))
    {
      size_t	found = line.find("[");
      
      if (found != std::string::npos)
	{
	  teamScore	newTeam;
	  size_t	tmp = line.find("]", found) - found;
	  size_t	foundScore;
	  
	  newTeam.teamName = line.substr(found, tmp);
	  getline(file, line);
	  foundScore = line.find("teamScore=", found);
	  newTeam.scoreWarrior = line.substr(foundScore);
	}
    }
}

std::ifstream		ScoreManager::createFile() const
{
  std::ifstream		tmp("./resources/score.ini");
  if (!tmp)
    {
      std::ofstream outfile("./resources/score.ini");
      outfile.close();
    }
  return (tmp);
}

void			ScoreManager::putTeamScore() const
{
  std::ofstream		toWrite;
  std::fstream		file("./resources/score.ini");
  std::stringstream	buf;
  std::string		tmp;
  size_t		found;
  size_t		foundToEnd;
  double		scoreTeam;

  buf << file.rdbuf();
  tmp = buf.str();
  if ((found = tmp.find(currentTeamScore.teamName)) != std::string::npos)
    {
      if ((foundToEnd = tmp.find("[", found)) != std::string::npos)
	{
	  if (found >= 2)
	    tmp = tmp.substr(0, found - 2) + tmp.substr(foundToEnd);
	  else
	    tmp = tmp.substr(0, found - 1) + tmp.substr(foundToEnd);
	}
      else
	{
	  if (found >= 2)
	    tmp = tmp.substr(0, found - 2);
	  else
	    tmp = tmp.substr(0, found - 1);
	}
    }
  scoreTeam = stod(currentTeamScore.scoreWarrior) + stod(currentTeamScore.scoreValkyrie)
    + stod(currentTeamScore.scoreWizard) + stod(currentTeamScore.scoreElf);
  toWrite.open("./resources/score.ini");
  if (tmp != "")
    toWrite << tmp << std::endl
	    << "[" << currentTeamScore.teamName << "]" << std::endl
	    << "teamScore=" << scoreTeam << std::endl;
  else
    toWrite << "[" << currentTeamScore.teamName << "]" << std::endl
	    << "teamScore=" << scoreTeam << std::endl;
  toWrite.close();
}

void			ScoreManager::heroAddScore(std::string const& heroName, int scoreToAdd)
{
  double		tmp;
  std::ostringstream	s;

  if (heroName == "Wizard")
    {
      tmp = std::stod(currentTeamScore.scoreWizard) + scoreToAdd;
      s << tmp;
      currentTeamScore.scoreWizard = std::string(s.str());
    }
  else if (heroName == "Elf")
    {
      tmp = std::stod(currentTeamScore.scoreElf) + scoreToAdd;
      s << tmp;
      currentTeamScore.scoreElf = std::string(s.str());
    }
}

void			ScoreManager::addToScore(std::string const& heroName,
						 int scoreToAdd)
{
  double		tmp;
  std::ostringstream	s;

  if (heroName == "Warrior")
    {
      tmp = std::stod(currentTeamScore.scoreWarrior) + scoreToAdd;
      s << tmp;
      currentTeamScore.scoreWarrior = std::string(s.str());
    }
  else if (heroName == "Valkyrie")
    {
      tmp = std::stod(currentTeamScore.scoreValkyrie) + scoreToAdd;
      s << tmp;
      currentTeamScore.scoreValkyrie = std::string(s.str());
    }
  else
    heroAddScore(heroName, scoreToAdd);
}

ScoreManager::highScore::highScore()
{
  loadTeam();
  sortTeam();
}

ScoreManager::highScore::highScore(highScore const& other) : teamName(other.teamName), teamScore(other.teamScore){}

ScoreManager::highScore ScoreManager::highScore::operator=(highScore const& other)
{
  teamName = other.teamName;
  teamScore = other.teamScore;
  return (*this);
}

ScoreManager::highScore::~highScore()
{
  teamName.clear();
  teamScore.clear();
}

std::string	ScoreManager::highScore::getTeamName(unsigned int rank) const
{
  if (rank < teamName.size())
    return (teamName[rank]);
  return ("");
}


int		ScoreManager::highScore::getSize() const
{
  return (teamScore.size());
}

std::string	ScoreManager::highScore::getTeamScore(unsigned int rank) const
{
  if (rank < teamName.size())
    return (teamScore[rank]);
  return ("");
}

bool		ScoreManager::highScore::verifyScore(std::string score) const
{
  return (std::all_of(score.begin(), score.end(), ::isdigit));
}

void			ScoreManager::highScore::loadTeam()
{
  std::fstream		fs("./resources/score.ini");
  std::stringstream	buf;
  std::string		tmp;
  size_t		found;
  size_t		foundName;
  size_t		foundScore;
  std::string		scoreTmp;

  buf << fs.rdbuf();
  tmp = buf.str();
  found = tmp.find("[");
  while (found != std::string::npos)
    {
      foundName = tmp.find("]", found);
      foundScore = tmp.find("=", foundName);
      scoreTmp = tmp.substr(foundScore + 1, ((tmp.find("[", foundScore) - 1) - foundScore) - 1);
      if (verifyScore(scoreTmp) == 1)
	{
	  teamScore.emplace_back(scoreTmp);
	  teamName.emplace_back(tmp.substr(found + 1, (foundName - found) - 1));
	}
      found = tmp.find("[", foundScore + 1);
    }
}

void		ScoreManager::highScore::sortTeam()
{
  unsigned int	i = 1;
  std::string	tmp;

  if (teamScore.size() >= 2)
    {
      while (i < teamScore.size())
  	{
  	  if (stod(teamScore[i - 1]) < stod(teamScore[i]))
  	    {
  	      tmp = teamScore[i - 1];
  	      teamScore[i - 1] = teamScore[i];
  	      teamScore[i] = tmp;
  	      tmp = teamName[i - 1];
  	      teamName[i - 1] = teamName[i];
  	      teamName[i] = tmp;
  	      i = 1;
  	    }
  	  else
  	    ++i;
  	}
      while (teamScore.size() >= 6)
  	{
	  teamScore.pop_back();
	  teamName.pop_back();
	}
    }
}
