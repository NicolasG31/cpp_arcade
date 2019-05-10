//
// IGame.hpp for  in /home/sanchez/rendu/tek2/cpp/cpp_arcade
//
// Made by sanchez
// Login   <sanchez@epitech.net>
//
// Started on  Tue Mar 14 18:22:46 2017 sanchez
// Last update Thu Mar 23 13:53:08 2017 Jerome Dang
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include "../my.hpp"

class		IGame
{
public:
  virtual	~IGame() {};

  // Game
  virtual const std::string	getName() const = 0;
  virtual void			runGame(map *map) = 0;
  virtual void			stopGame() = 0;
  virtual map			*createMap() = 0;
  virtual void			addScore(int point, map *map) = 0;
  virtual void			checkMap(map *map) = 0;

  // Event
  virtual int	goUp(map *map) = 0;
  virtual int	goDown(map *map) = 0;
  virtual int	goLeft(map *map) = 0;
  virtual int	goRight(map *map) = 0;
};

#endif
