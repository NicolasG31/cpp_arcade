//
// my.hpp for arcade in /home/nicolas/arcade/cpp_arcade
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Thu Mar 16 11:14:19 2017 Nicolas Guillon
// Last update Tue Apr  4 11:18:08 2017 Guillaume
//

#ifndef MY_H_
# define MY_H_

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>

typedef enum    event
  {
    ESCAPE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    PAUSE,
    NEXT_LIB,
    PREV_LIB,
    NEXT_GAME,
    PREV_GAME,
    RESTART,
    MENU,
    ILLEGAL
  }             event;

typedef enum    map_content
  {
    EMPTY,
    BLOCK,
    CHARACTER,
    ITEM,
    S_ITEM,
    PLAYER,
    PLATFORM
  }             map_content;

typedef struct  score
{
  int           score;
  char		name[255];
}               score;

typedef struct  character
{
  int		x;
  int		y;
  double	xf;
  double	yf;
  event         dir;
  map_content	type;
  clock_t	hasBonus;
}               character;

typedef struct			map
{
  clock_t			startTime;
  bool				hasWon;
  bool				hasLost;
  bool        save;
  score				current_score;
  map_content			**map;
  std::vector<character>	player;
  int				width;
  int				height;
}				map;

typedef struct	info_lib
{
  void		*handle;
  std::string	path;
  std::string	name;
  std::string hscore_name;
  int		pos;
  int		hscore;
}		info_lib;

typedef struct	t_arcade
{
  class IGraph	*_current_graph;
  class IGame	*_current_game;
  map		*_current_map;

  std::vector<info_lib>	games;
  std::vector<info_lib>	libs;

  int		pos_graph;
  int		pos_game;
  void  *handle_lib;
  void  *handle_game;
  std::string	user;
}		t_arcade;


#endif
