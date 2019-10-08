//
// KeySelector.cpp for  in /home/simixay/Desktop/rendu/cpp_indie_studio/sources
//
// Made by Simixay Prakaythong
// Login   <simixay.prakaythong@epitech.eu>
//
// Started on  Fri May 12 14:58:45 2017 Simixay Prakaythong
// Last update Fri Jun 16 18:36:07 2017 Raphaël Martins
//

#include "Errors.hpp"
#include "KeySelector.hpp"

KeySelector::KeySelector()
{
  setDefaultKeys();
  initMaps();
  loadKeys();
}

void			KeySelector::setDefaultKeys()
{
  keysPlayer1.emplace_back(0x51); //left
  keysPlayer1.emplace_back(0x44); //right
  keysPlayer1.emplace_back(0x5A); //up
  keysPlayer1.emplace_back(0x53); //down
  keysPlayer1.emplace_back(0x45); //e attack
  keysPlayer1.emplace_back(0x41); //a use objects
  keysPlayer2.emplace_back(0x4A);
  keysPlayer2.emplace_back(0x4C);
  keysPlayer2.emplace_back(0x49);
  keysPlayer2.emplace_back(0x4B);
  keysPlayer2.emplace_back(0x55);
  keysPlayer2.emplace_back(0x4F);
  keysPlayer3.emplace_back(0x46);
  keysPlayer3.emplace_back(0x48);
  keysPlayer3.emplace_back(0x54);
  keysPlayer3.emplace_back(0x47);
  keysPlayer3.emplace_back(0x59);
  keysPlayer3.emplace_back(0x52);
  joysticksPlayer4.emplace_back(0x82);
  joysticksPlayer4.emplace_back(0x83);
  joysticksPlayer4.emplace_back(0x84);
  joysticksPlayer4.emplace_back(0x85);
  joysticksPlayer4.emplace_back(0x86);
  joysticksPlayer4.emplace_back(0x87);
}

void	KeySelector::initKey()
{
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LBUTTON,"LBUTTON"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RBUTTON, "RBUTTON"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CANCEL,"CANCEL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_MBUTTON,"MBUTTON"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_XBUTTON1,"XBUTTON1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_XBUTTON2, "XBUTTON2"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_BACK, "BACK"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_TAB, "TAB"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CLEAR, "CLEAR"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RETURN, "RETURN"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SHIFT, "SHIFT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CONTROL, "CONTROL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_MENU, "MENU"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PAUSE, "PAUSE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CAPITAL, "CAPITAL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KANA, "KANA"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_HANGUEL, "HANGUEL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_HANGUL, "HANGUL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_JUNJA, "JUNJA"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_FINAL, "FINAL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_HANJA, "HANJA"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KANJI, "KANJI"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_ESCAPE, "ESCAPE"));
}

void     KeySelector::initKeyBinding()
{
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CONVERT, "CONVERT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NONCONVERT, "NONCONVERT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_ACCEPT, "ACCEPT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_MODECHANGE, "MODECHANGE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SPACE, "SPACE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PRIOR, "PRIOR"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NEXT, "NEXT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_END, "END"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_HOME, "HOME"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LEFT, "LEFT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_UP, "UP"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RIGHT, "RIGHT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_DOWN, "DOWN"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SELECT, "SELECT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PRINT, "PRINT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_EXECUT, "EXECUT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_DELETE, "DELETE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_INSERT, "INSERT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_DELETE, "DELETE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_HELP, "HELP"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_0, "0"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_1, "1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_2, "2"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_3, "3"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_4, "4"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_5, "5"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_6, "6"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_7, "7"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_8, "8"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_9, "9"));
}

void	KeySelector::initKeyLetter()
{
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_A, "A"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_B, "B"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_C, "C"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_D, "D"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_E, "E"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_F, "F"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_G, "G"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_H, "H"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_I, "I"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_J, "J"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_K, "K"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_L, "L"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_M, "M"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_N, "N"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_O, "O"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_P, "P"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_Q, "Q"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_R, "R"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_S, "S"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_T, "T"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_U, "U"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_V, "V"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_W, "W"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_X, "X"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_Y, "Y"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_KEY_Z, "Z"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LWIN, "LWIN"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RWIN, "RWIN"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_APPS, "APPS"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SLEEP, "SLEEP"));
}

void	KeySelector::initSpecialCharacter()
{
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD0, "NUMPAD0"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD2, "NUMPAD2"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD1, "NUMPAD1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD3, "NUMPAD3"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD4, "NUMPAD4"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD5, "NUMPAD5"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD6, "NUMPAD6"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD7, "NUMPAD7"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD8, "NUMPAD8"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMPAD9, "NUMPAD9"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_MULTIPLY, "MULTIPLY"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_ADD, "ADD"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SEPARATOR, "SEPARATOR"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SUBTRACT, "SUBTRACT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_DECIMAL, "DECIMAL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_DIVIDE, "DIVIDE"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F1, "F1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F2, "F2"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F3, "F3"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F4, "F4"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F5, "F5"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F6, "F6"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F7, "F7"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F8, "F8"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F9, "F9"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F10, "F10"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F11, "F11"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F12, "F12"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F13, "F13"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F14, "F14"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F15, "F15"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F16, "F16"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F17, "F17"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F18, "F18"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F19, "F19"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F20, "F20"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F21, "F21"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F22, "F22"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F23, "F23"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_F24, "F24"));
}

void	KeySelector::initJoystick()
{
  joysticksStrings.insert(std::make_pair(0x00, "BUTTON_01_X"));
  joysticksStrings.insert(std::make_pair(0x01, "BUTTON_02_O"));
  joysticksStrings.insert(std::make_pair(0x02, "BUTTON_03_SQUARE"));
  joysticksStrings.insert(std::make_pair(0x03, "BUTTON_04_TRIANGLE"));
  joysticksStrings.insert(std::make_pair(0x04, "BUTTON_05_L1"));
  joysticksStrings.insert(std::make_pair(0x05, "BUTTON_06_R1"));
  joysticksStrings.insert(std::make_pair(0x06, "BUTTON_07_SHARE"));
  joysticksStrings.insert(std::make_pair(0x07, "BUTTON_08_OPTIONS"));
  joysticksStrings.insert(std::make_pair(0x08, "BUTTON_09"));
  joysticksStrings.insert(std::make_pair(0x09, "BUTTON_10"));
  joysticksStrings.insert(std::make_pair(0x0A, "BUTTON_11"));
  joysticksStrings.insert(std::make_pair(0x0B, "BUTTON_12"));
  joysticksStrings.insert(std::make_pair(0x0C, "BUTTON_13"));
  joysticksStrings.insert(std::make_pair(0x0D, "BUTTON_14"));
  joysticksStrings.insert(std::make_pair(0x0E, "BUTTON_15"));
  joysticksStrings.insert(std::make_pair(0x0F, "BUTTON_16"));
  joysticksStrings.insert(std::make_pair(0x10, "BUTTON_17"));
  joysticksStrings.insert(std::make_pair(0x11, "BUTTON_18"));
  joysticksStrings.insert(std::make_pair(0x12, "BUTTON_19"));
  joysticksStrings.insert(std::make_pair(0x13, "BUTTON_20"));
  joysticksStrings.insert(std::make_pair(0x14, "BUTTON_21"));
  joysticksStrings.insert(std::make_pair(0x15, "BUTTON_22"));
  joysticksStrings.insert(std::make_pair(0x16, "BUTTON_23"));
  joysticksStrings.insert(std::make_pair(0x17, "BUTTON_24"));
  joysticksStrings.insert(std::make_pair(0x18, "BUTTON_25"));
  joysticksStrings.insert(std::make_pair(0x19, "BUTTON_26"));
  joysticksStrings.insert(std::make_pair(0x1A, "BUTTON_27"));
  joysticksStrings.insert(std::make_pair(0x1B, "BUTTON_28"));
  joysticksStrings.insert(std::make_pair(0x1C, "BUTTON_29"));
  joysticksStrings.insert(std::make_pair(0x1D, "BUTTON_30"));
  joysticksStrings.insert(std::make_pair(0x1E, "BUTTON_31"));
  joysticksStrings.insert(std::make_pair(0x1F, "BUTTON_32"));
  joysticksStrings.insert(std::make_pair(0x20, "LEFT_X_AXIS"));
  joysticksStrings.insert(std::make_pair(0x21, "RIGHT_X_AXIS"));
  joysticksStrings.insert(std::make_pair(0x22, "UP_Y_AXIS"));
  joysticksStrings.insert(std::make_pair(0x23, "DOWN_Y_AXIS"));
}

void	KeySelector::initLastKey()
{
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_NUMLOCK, "NUMLOCK"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_SCROLL, "SCROLL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LSHIFT, "LSHIFT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RSHIFT, "RSHIFT"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LCONTROL, "LCONTROL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RCONTROL, "RCONTROL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_LMENU, "LMENU"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_RMENU, "RMENU"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_1, "OEM_1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PLUS, "PLUS"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_COMMA, "COMMA"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_MINUS, "MINUS"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PERIOD, "PERIOD"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_2, "OEM_2"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_3, "OEM_3"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_4, "OEM_4"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_5, "OEM_5"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_6, "OEM_6"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_7, "OEM_7"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_8, "OEM_8"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_AX, "OEM_AX"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_102, "OEM_102"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_ATTN, "ATTN"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_CRSEL, "CRSEL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_EXSEL, "EXSEL"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_EREOF, "EREOF"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PLAY, "PLAY"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_ZOOM, "ZOOM"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_PA1, "PA1"));
  keysStrings.insert(std::make_pair(irr::EKEY_CODE::KEY_OEM_CLEAR, "OEM_CLEAR"));
}

void	KeySelector::initMaps()
{
  initKey();
  initKeyBinding();
  initKeyLetter();
  initSpecialCharacter();
  initJoystick();
  initLastKey();
}

void			KeySelector::loadKeys()
{
  std::string		line;
  std::ifstream		file(createFile());

  while (getline(file, line))
    {
      size_t		found = line.find("[");

      if (found != std::string::npos)
	{
	  findAndFillKeys("PLAYER1", &keysPlayer1,line,file);
	  findAndFillKeys("PLAYER2", &keysPlayer2,line,file);
	  findAndFillKeys("PLAYER3", &keysPlayer3,line,file);
	  findAndFillKeys("PLAYER4", &joysticksPlayer4,line,file);
	}
    }
}

std::ifstream		KeySelector::createFile()
{
  std::ifstream		tmp("./resources/keybindings.ini");

  if (!tmp)
    {
      std::ofstream	outfile("./resources/keybindings.ini");

      outfile.close();
      saveButtons();
    }
  return (tmp);
}

bool			KeySelector::is_empty(std::ifstream& pFile)
{
  return (pFile.peek() == std::ifstream::traits_type::eof());
}

void			KeySelector::findAndFillKeys(std::string name, std::vector<int> *keysPlayer,
						     std::string line, std::ifstream& file)
{
  size_t		found = line.find("[");
  size_t		tmp = line.find("]");

  if (line.substr(found + 1,tmp - 1).compare(name) == 0)
    {
      getline(file,line);
      (*keysPlayer).at(0) = stoi(line.substr(7));
      getline(file,line);
      (*keysPlayer).at(1) = stoi(line.substr(8));
      getline(file,line);
      (*keysPlayer).at(2) = stoi(line.substr(5));
      getline(file,line);
      (*keysPlayer).at(3) = stoi(line.substr(7));
      getline(file,line);
      (*keysPlayer).at(4) = stoi(line.substr(7));
      getline(file,line);
      (*keysPlayer).at(5) = stoi(line.substr(11));
    }
  if (checkVectorKeySize((*keysPlayer)) == 1)
    {
      setDefaultKeys();
      saveButtons();
    }
}

int			KeySelector::checkVectorKeySize(std::vector<int> keySelector)
{
  if (keySelector.size() != 6)
    return (1);
  return (0);
}

void		KeySelector::saveButtons()
{
  std::ofstream	toWrite;

  toWrite.open("./resources/keybindings.ini");
  writeToFile("[PLAYER1]", keysPlayer1,toWrite);
  writeToFile("[PLAYER2]", keysPlayer2,toWrite);
  writeToFile("[PLAYER3]", keysPlayer3,toWrite);
  writeToFile("[PLAYER4]", joysticksPlayer4,toWrite);
  toWrite.close();
};

irr::EKEY_CODE	KeySelector::getIrrlichtKey(int key)
{
  return ((irr::EKEY_CODE)key);
}

std::string	KeySelector::getTranslatedKey(int key)
{
  auto it = keysStrings.find(key);
  return (it->second);
}

std::string	KeySelector::getTranslatedJoyStick(int key)
{
  auto it = joysticksStrings.find(key);
  return (it->second);
}

void	KeySelector::writeToFile(std::string name,std::vector<int> keysPlayer, std::ofstream& toWrite)
{
  toWrite << name << std::endl
	  << "goLeft=" << keysPlayer.at(0) << std::endl
	  << "goRight=" << keysPlayer.at(1) << std::endl
	  << "goUp=" << keysPlayer.at(2) << std::endl
	  << "goDown=" << keysPlayer.at(3) << std::endl
	  << "attack=" << keysPlayer.at(4) << std::endl
	  << "useObjects=" << keysPlayer.at(5) << std::endl;
}
