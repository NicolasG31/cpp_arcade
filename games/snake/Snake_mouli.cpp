//
// Snake_mouli.cpp for  in /home/doremi/rendu/cpp/cpp_arcade/games/snake
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Mon Apr  3 20:15:30 2017 Guillaume
// Last update Sat Apr  8 10:10:49 2017 Guillaume Doremieux
//


#include "../../my.hpp"
#include "../../Protocol.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include "../my_read.hpp"


void  show_get_map(map *map, arcade::CommandType com)
{
  my_read   mread;

  arcade::GetMap *gmap = new arcade::GetMap[sizeof(arcade::CommandType) + sizeof(uint16_t) * 2 + map->height * map->width * sizeof(arcade::TileType)];
  int x = 0;
  int y = 0;
  int index = 0;

  gmap->type = com;
  gmap->width = map->width;
  gmap->height = map->height;
  while (x < map->height)
  {
    y = 0;
    while (y < map->width)
    { 
      index = x * map->width + y;
      if (map->map[x][y] == EMPTY)
        gmap->tile[index] = arcade::TileType::EMPTY;
      else if (map->map[x][y] == BLOCK) 
        gmap->tile[index] = arcade::TileType::BLOCK;
      else if (map->map[x][y] == ITEM) 
        gmap->tile[index] = arcade::TileType::POWERUP;
      y++;
    }
    x++;
  }
  mread.my_write_mouli(1, gmap, sizeof(arcade::CommandType) + sizeof(uint16_t) * 2 + map->height * map->width * sizeof(arcade::TileType));
}

void  show_where_an_i(map *map, arcade::CommandType com)
{
  my_read   mread;

  arcade::WhereAmI *where = new arcade::WhereAmI[sizeof(arcade::CommandType) + sizeof(uint16_t) + (sizeof(arcade::Position) * map->player.size())];
  int i = 0;
  arcade::Position pos;

  where->type = com;
  where->lenght = map->player.size();
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node) 
  {
    pos.x = (*node).x;
    pos.y = (*node).y;
    where->position[i] = pos;
    i++;
  }
  mread.my_write_mouli(1, where, sizeof(arcade::CommandType) + sizeof(uint16_t) + (sizeof(arcade::Position) * map->player.size()));
}

event	go_Up(map *map, event _dir)
{
  if (_dir != DOWN)
    _dir = UP;
  return (_dir);
}

event	go_Down(map *map, event _dir)
{
  if (_dir != UP)
    _dir = DOWN;
  return (_dir);
}

event go_Left(map *map, event _dir)
{
  if (_dir != RIGHT)
    _dir = LEFT;
  return (_dir);
}

event	go_Right(map *map, event _dir)
{
  if (_dir != LEFT)
    _dir = RIGHT;
  return (_dir);
}

void	gen_Item(map *map)
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

void	check_Map(map *map)
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
    gen_Item(map);
  if (map->player.front().x == 0 || map->player.front().x == 16 || map->player.front().y == 0 || map->player.front().y == 16)
    {
      map->hasLost = true;
    }
  count = 0;
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if (count > 2 && map->player.front().x == (*node).x && map->player.front().y == (*node).y)
  	{
  	  map->hasLost = true;
  	}
      count++;
    }
}

void	run_Game(map *map, event _dir)
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

      check_Map(map);
    }
}

map	*create_Map()
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

  check_Map(nmap);

  return nmap;
}

extern "C"
void	Play()
{
  my_read mread;
  arcade::CommandType command;
  map       *map; 
  event     _dir = RIGHT; 

  map = create_Map();
  while (mread.my_read_mouli(0, &command, sizeof(arcade::CommandType)))
  {
    if (command == arcade::CommandType::WHERE_AM_I)
      show_where_an_i(map, command);
    else if (command == arcade::CommandType::GET_MAP)
      show_get_map(map, command);
    else if (command == arcade::CommandType::GO_UP)
      _dir = go_Up(map, _dir);
    else if (command == arcade::CommandType::GO_DOWN)
      _dir = go_Down(map, _dir);
    else if (command == arcade::CommandType::GO_LEFT)
      _dir = go_Left(map, _dir);
    else if (command == arcade::CommandType::GO_RIGHT)
      _dir = go_Right(map, _dir);
    else if (command == arcade::CommandType::PLAY)
      run_Game(map, _dir);
  }
}
