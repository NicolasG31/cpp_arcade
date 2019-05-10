//
// Snake.hpp for Snake in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/games
// 
// Made by Jerome Dang
// Login   <dang_j@epitech.net>
// 
// Started on  Mon Mar 27 16:14:29 2017 Jerome Dang
// Last update Wed Mar 29 20:01:36 2017 Jerome Dang
//

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "../IGame.hpp"
#include "../../my.hpp"

class		Snake : public IGame
{
private:
  event		_dir;

public:
  Snake();
  virtual	~Snake();

  // Game
  virtual const std::string     getName() const;
  virtual void			runGame(map *map);
  void				genItem(map *map);
  virtual void			stopGame();
  virtual map			*createMap();
  virtual void			addScore(int point, map *map);
  virtual void			checkMap(map *map);

  // EVENT
  virtual int   goUp(map *map);
  virtual int   goDown(map *map);
  virtual int   goLeft(map *map);
  virtual int   goRight(map *map);
};


#endif
