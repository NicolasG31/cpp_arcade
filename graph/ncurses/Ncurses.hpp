//
// Ndk.hpp for opengl in /home/nicolas/arcade/opengl
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Wed Mar 15 14:51:40 2017 Nicolas Guillon
// Last update Tue Apr  4 13:03:49 2017 Guillaume
//

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "../IGraph.hpp"
#include "../../my.hpp"
#include "my_ncurses.hpp"

class Ncurses : public IGraph
{
private:
  const	std::string	_name = "Ncurses";
  my_ncurses        _lib;
  int              _is_pacman;
public:
  Ncurses();
  virtual ~Ncurses();

  virtual const std::string     getName() const;
  // Window handler
  virtual void  startWindow(int width, int height, std::string name);
  virtual void  closeWindow();
  virtual void  displayMap(map *map);
  virtual int  startMenu(t_arcade *menu);
  void  place_item_pacman(int x, int y, map_content content);
  void  place_item_snake(int x, int y, map_content content);
  void	setPlayerSnake(character player, int x, int y, int i);
  void	setPlayerPacman(character player, int x, int y);
  void  setCharacterBonusPacman(character player, int x, int y);
  void  setCharacterPacman(character player, int x, int y, int i);
  void  setCharacterBonusSnake(character player, int x, int y);
  void  setCharacterSnake(character player, int x, int y);
  void  displayChar(map *map, int scalex, int scaley);
  void  displayTitleGame(int x, int y, std::vector<info_lib> lib, std::string name, int pos);
  void  displayTitleLib(int x, int y, std::vector<info_lib> lib, std::string name, int pos);
  void  displayTitleName(int x, int y, std::string name);
  void  displayTitleHscore(int x, int y, std::vector<info_lib> lib, int pos);
  void  displayScore(map *map, int x, int y);
  // Events handler
  virtual event getEvent();
};

#endif
