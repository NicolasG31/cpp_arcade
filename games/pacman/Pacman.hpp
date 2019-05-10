//
// Pacman.hpp for pacman in /home/nicolas/arcade/cpp_arcade/libs/games
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Thu Mar 16 10:29:21 2017 Nicolas Guillon
// Last update Wed Mar 29 19:18:36 2017 Jerome Dang
//

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../IGame.hpp"
#include "../../my.hpp"

class		Pacman : public IGame
{
public:
  Pacman();
  virtual	~Pacman();

  // Game
  virtual const std::string     getName() const;
  virtual void			runGame(map *map);
  void				runPlayer(character &player, map *map);
  void				tryTurning(character &ghost, map *map);
  void				runGhost(character &ghost, map *map);
  virtual void			stopGame();
  virtual map			*createMap();
  virtual void			addScore(int point, map *map);
  virtual void			checkMap(map *map);

  // Event
  virtual int   goUp(map *map);
  virtual int   goDown(map *map);
  virtual int   goLeft(map *map);
  virtual int   goRight(map *map);
};


#endif
