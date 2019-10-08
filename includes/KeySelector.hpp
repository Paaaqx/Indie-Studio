//
// KeySelector.hpp for  in /home/simixay/Desktop/rendu/cpp_indie_studio/includes
//
// Made by Simixay Prakaythong
// Login   <simixay.prakaythong@epitech.eu>
//
// Started on  Fri May 12 15:03:51 2017 Simixay Prakaythong
// Last update Sun Jun 18 20:48:09 2017 Anthony
//

#ifndef KEYSELECTOR_HPP_
# define KEYSELECTOR_HPP_

# include <irrlicht.h>
# include <vector>
# include <iostream>
# include <fstream>
# include <map>

class					KeySelector
{
public:
  KeySelector();
  ~KeySelector(){};

public:
  std::vector<int>			keysPlayer1;
  std::vector<int>			keysPlayer2;
  std::vector<int>			keysPlayer3;
  std::vector<int>			joysticksPlayer4;
  std::map<int,std::string>		keysStrings;
  std::map<int, std::string>		joysticksStrings;

public:
  std::ifstream				createFile();
  void					loadKeys();
  void					findAndFillKeys(std::string name, std::vector<int> *keys,
							std::string line,std::ifstream& file);
  int					checkVectorKeySize(std::vector<int> keySelector);
  void					saveButtons();
  void					writeToFile(std::string name, std::vector<int> keys, std::ofstream& toWrite);
  bool					is_empty(std::ifstream& pFile);
  void					setDefaultKeys();
  void					initMaps();
  irr::EKEY_CODE			getIrrlichtKey(int key);
  std::string				getTranslatedKey(int key);
  std::string				getTranslatedJoyStick(int key);
  void					initKey();
  void					initKeyBinding();
  void					initKeyLetter();
  void					initSpecialCharacter();
  void					initJoystick();
  void					initLastKey();
};

#endif /* !KEYSELECTOR_HPP_ */
