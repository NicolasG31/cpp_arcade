//
// Snake.cpp for Snake in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/games
// 
// Made by Jerome Dang
// Login   <dang_j@epitech.net>
// 
// Started on  Mon Mar 27 16:20:40 2017 Jerome Dang
// Last update Sat Apr  8 10:27:54 2017 Guillaume Doremieux
//

#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

#include "Snake.hpp"

Snake::Snake()
{
  _dir = RIGHT;
}

Snake::~Snake()
{

}

const std::string	Snake::getName() const
{
  return ("Snake");
}

void	Snake::genItem(map *map)
{
  int	status = 1;
  int	state = 0;
  int	x;
  int	y;

  while (status == 1)
    {
      y = rand() % 15 + 1;
      x = rand() % 15 + 1;

      state = 0;
      for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
	{
	  if ((*node).x == x && (*node).y == y)
	    state = 1;
	}
      if (state == 0)
	{
	  map->map[y][x] = ITEM;
	  status = 0;
	}
    }
}

void	Snake::checkMap(map *map)
{
  character	player;
  int		x;
  int		y;
  int		count = 0;;

  srand(time(NULL));
  y = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  if (map->map[y][x] == ITEM)
	    count++;
	  x++;
	}
      y++;
    }
  if (count == 0)
    genItem(map);
  if (map->player.front().x == 0 || map->player.front().x == 16 || map->player.front().y == 0 || map->player.front().y == 16)
    map->hasLost = true;
  count = 0;
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if (count > 2 && map->player.front().x == (*node).x && map->player.front().y == (*node).y)
	map->hasLost = true;
      count++;
    }
}

void	Snake::runGame(map *map)
{
  character	player;

  if (map->hasWon == false && map->hasLost == false)
    {
      player = map->player.back();
      player.dir = _dir;
      player.x = map->player.front().x;
      player.y = map->player.front().y;

      if (_dir == UP)
	player.y = map->player.front().y - 1;
      else if (_dir == DOWN)
	player.y = map->player.front().y + 1;
      else if (_dir == LEFT)
	player.x = map->player.front().x - 1;
      else if (_dir == RIGHT)
	player.x = map->player.front().x + 1;

      player.xf = player.x;
      player.yf = player.y;

      if (map->map[player.y][player.x] == ITEM)
	{
	  map->map[player.y][player.x] = EMPTY;
	  map->player.push_back(map->player.back());
	  map->current_score.score += 50;
	}

      map->player.insert(map->player.begin(), player);
      map->player.pop_back();

      checkMap(map);
    }
}

void	Snake::stopGame()
{

}

map	*Snake::createMap()
{
  map	*nmap;
  int	i;
  int	j;

  nmap = new map();
  nmap->map = new map_content *[17];
  i = 0;
  while (i < 17)
    {
      j = 0;
      nmap->map[i] = new map_content[17];
      while (j < 17)
	{
	  if (i == 0 || i == 16 || j == 0 || j == 16)
	    nmap->map[i][j] = BLOCK;
	  else
	    nmap->map[i][j] = EMPTY;
	  j++;
	}
      i++;
    }

  character	player1;
  character	player2;
  character	player3;
  character	player4;

  player1.x = 5;
  player1.y = 11;
  player1.xf = 5.0;
  player1.yf = 11.0;
  player1.dir = RIGHT;
  player1.type = PLAYER;
  player1.hasBonus = 0;
  player2.x = 6;
  player2.y = 11;
  player2.xf = 6.0;
  player2.yf = 11.0;
  player2.dir = RIGHT;
  player2.type = PLAYER;
  player2.hasBonus = 0;
  player3.x = 7;
  player3.y = 11;
  player3.xf = 7.0;
  player3.yf = 11.0;
  player3.dir = RIGHT;
  player3.type = PLAYER;
  player3.hasBonus = 0;
  player4.x = 8;
  player4.y = 11;
  player4.xf = 8.0;
  player4.yf = 11.0;
  player4.dir = RIGHT;
  player4.type = PLAYER;
  player4.hasBonus = 0;

  nmap->player.push_back(player4);
  nmap->player.push_back(player3);
  nmap->player.push_back(player2);
  nmap->player.push_back(player1);

  nmap->startTime = clock();
  nmap->height = 17;
  nmap->width = 17;
  nmap->current_score.score = 0;
  nmap->hasWon = false;
  nmap->hasLost = false;
  nmap->save = false;
  this->_dir = RIGHT;

  checkMap(nmap);
  return nmap;
}

void	Snake::addScore(int point, map *map)
{

}

int	Snake::goUp(map *map)
{
  if (_dir != DOWN)
    _dir = UP;
}

int	Snake::goDown(map *map)
{
  if (_dir != UP)
    _dir = DOWN;
}

int	Snake::goLeft(map *map)
{
  if (_dir != RIGHT)
    _dir = LEFT;
}

int	Snake::goRight(map *map)
{
  if (_dir != LEFT)
    _dir = RIGHT;
}

extern "C"
class Snake	*create_game()
{
  return new Snake();
}
