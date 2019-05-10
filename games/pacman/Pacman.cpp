//
//man.cpp for pacman in /home/nicolas/arcade/cpp_arcade/libs/games
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Thu Mar 16 10:32:07 2017 Nicolas Guillon
// Last update Sun Apr  9 18:43:17 2017 Jerome Dang
//

#include <stdlib.h>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

#include "../../my.hpp"
#include "Pacman.hpp"

Pacman::Pacman()
{

}

Pacman::~Pacman()
{

}

const std::string	Pacman::getName() const
{
  return ("Pacman");
}

void	Pacman::checkMap(map *map)
{
  int	x;
  int	y;
  int	count;

  y = 0;
  count = 0;
  while (y < map->height)
    {
      x = 0;
      while (x < map->width)
	{
	  if (map->map[y][x] == ITEM || map->map[y][x] == S_ITEM)
	    count++;
	  x++;
	}
      y++;
    }

  character	player;
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER)
	player = (*node);
      else if ((*node).type == CHARACTER)
	{
	  if (player.x == (*node).x && player.y == (*node).y)
	    {
	      if (player.hasBonus == 0)
		map->hasLost = true;
	      else
		{
		  (*node).y = 7;
		  (*node).x = 10;
		  (*node).yf = 7.0;
		  (*node).xf = 10.0;
		  (*node).hasBonus = clock();
		}
	    }
	}
    }
  if (count == 0)
    map->hasWon = true;
}

void	Pacman::runPlayer(character &player, map *map)
{
  if (player.yf != (double) player.y || player.xf != (double) player.x)
    {
      if (player.yf < (double) player.y)
	{
	  player.y -= 1;
	  player.yf -= 0.5;
	}
      else if (player.yf > (double) player.y)
	{
	  player.y += 1;
	  player.yf += 0.5;
	}
      else if (player.xf < (double) player.x)
	{
	  player.x -= 1;
	  player.xf -= 0.5;
	}
      else if (player.xf > (double) player.x)
	{
	  player.x += 1;
	  player.xf += 0.5;
	}
      if (map->map[player.y][player.x] == ITEM)
	map->current_score.score += 10;
      else if (map->map[player.y][player.x] == S_ITEM)
	{
	  map->current_score.score += 50;
	  player.hasBonus = clock();
	}
      map->map[player.y][player.x] = EMPTY;
    }
  else
    if (player.dir == UP && map->map[player.y - 1][player.x] != BLOCK
	&& map->map[player.y - 1][player.x] != PLATFORM)
      player.yf -= 0.5;
    else if (player.dir == DOWN && map->map[player.y + 1][player.x] != BLOCK
	     && map->map[player.y + 1][player.x] != PLATFORM)
      player.yf += 0.5;
    else if (player.dir == LEFT && map->map[player.y][player.x - 1] != BLOCK
	     && map->map[player.y][player.x - 1] != PLATFORM)
      {
	player.xf -= 0.5;
	if (player.xf < -1.0)
	  {
	    player.xf = 20.0;
	    player.x = 20;
	  }
      }
    else if (player.dir == RIGHT && map->map[player.y][player.x + 1] != BLOCK
	     && map->map[player.y][player.x + 1] != PLATFORM)
      {
	player.xf += 0.5;
	if (player.xf > 21.0)
	  {
	    player.xf = 0.0;
	    player.x = 0;
	  }
      }

  // Bonus 10secs
  if (player.hasBonus != 0)
    {
      clock_t	actTime = clock();
      double	timeSecs = (actTime - player.hasBonus) / (double) CLOCKS_PER_SEC;
      if (timeSecs > 0.10)
	player.hasBonus = 0;
    }
}

void	Pacman::tryTurning(character &ghost, map *map)
{
  if (ghost.yf == (double) ghost.y && ghost.xf == (double) ghost.x)
    {
      int			i = 0;
      std::map<int, event>	dir;
      event	lastdir;

      srand(time(NULL));

      // Position actuelle
      if (ghost.dir == UP && map->map[ghost.y - 1][ghost.x] != BLOCK)
	dir[i++] = UP;
      else if (ghost.dir == DOWN && map->map[ghost.y + 1][ghost.x] != BLOCK)
	dir[i++] = DOWN;
      else if (ghost.dir == LEFT && map->map[ghost.y][ghost.x - 1] != BLOCK)
	dir[i++] = LEFT;
      else if (ghost.dir == RIGHT && map->map[ghost.y][ghost.x + 1] != BLOCK)
	dir[i++] = RIGHT;

      // Positions possibles
      if (ghost.dir != UP && ghost.dir != DOWN && map->map[ghost.y - 1][ghost.x] != BLOCK)
	dir[i++] = UP;
      if (ghost.dir != DOWN && ghost.dir != UP && map->map[ghost.y + 1][ghost.x] != BLOCK)
	  dir[i++] = DOWN;
      if (ghost.dir != LEFT && ghost.dir != RIGHT && map->map[ghost.y][ghost.x - 1] != BLOCK)
	dir[i++] = LEFT;
      if (ghost.dir != RIGHT && ghost.dir != LEFT && map->map[ghost.y][ghost.x + 1] != BLOCK)
	dir[i++] = RIGHT;

      lastdir = ghost.dir;
      if (i > 0)
	ghost.dir = dir[(rand() % i)];
    }
}

void	Pacman::runGhost(character &ghost, map *map)
{
  if (ghost.hasBonus != 0)
    {
      clock_t	actTime = clock();
      double	timeSecs = (actTime - ghost.hasBonus) / (double) CLOCKS_PER_SEC;
      if (timeSecs > 0.05)
	ghost.hasBonus = 0;
    }
  else
    if (ghost.yf != (double) ghost.y || ghost.xf != (double) ghost.x)
      {
	if (ghost.yf < (double) ghost.y)
	  {
	    ghost.y -= 1;
	    ghost.yf -= 0.5;
	  }
	else if (ghost.yf > (double) ghost.y)
	  {
	    ghost.y += 1;
	    ghost.yf += 0.5;
	  }
	else if (ghost.xf < (double) ghost.x)
	  {
	    ghost.x -= 1;
	    ghost.xf -= 0.5;
	  }
	else if (ghost.xf > (double) ghost.x)
	  {
	    ghost.x += 1;
	    ghost.xf += 0.5;
	  }
      }
    else
      if (ghost.dir == UP && map->map[ghost.y - 1][ghost.x] != BLOCK)
	ghost.yf -= 0.5;
      else if (ghost.dir == DOWN && map->map[ghost.y + 1][ghost.x] != BLOCK)
	ghost.yf += 0.5;
      else if (ghost.dir == LEFT && map->map[ghost.y][ghost.x - 1] != BLOCK)
	{
	  ghost.xf -= 0.5;
	  if (ghost.xf < 0.0)
	    {
	      ghost.xf = 20.0;
	      ghost.x = 20;
	    }
	}
      else if (ghost.dir == RIGHT && map->map[ghost.y][ghost.x + 1] != BLOCK)
	{
	  ghost.xf += 0.5;
	  if (ghost.xf > 20.0)
	    {
	      ghost.xf = 0.0;
	      ghost.x = 0;
	    }
	}
  tryTurning(ghost, map);
}

void	Pacman::runGame(map *map)
{
  character	player;
  int		i;

  i = 0;
  if (map->hasWon == false && map->hasLost == false)
    {
      for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
	{
	  if ((*node).type == PLAYER)
	    {
	      runPlayer((*node), map);
	      player = (*node);
	    }
	  else if ((*node).type == CHARACTER)
	    {
	      if (map->current_score.score > i * 200)
		runGhost((*node), map);
	    }
	  i++;
	}
      clock_t	actTime = clock();
      double	timeSeconds = (actTime - map->startTime) / (double) CLOCKS_PER_SEC;
      if (timeSeconds > 0.10)
	map->map[7][10] = PLATFORM;
      checkMap(map);
    }
}

void	Pacman::stopGame()
{

}

map	*Pacman::createMap()
{
  map	*nmap;
  int	i = 0;

  nmap = new map();
  nmap->map = new map_content *[25];
  while (i != 25)
    {
      nmap->map[i] = new map_content[25];
      i++;
    }
  nmap->map[0][0] = EMPTY; nmap->map[0][1] = EMPTY; nmap->map[0][2] = EMPTY; nmap->map[0][3] = BLOCK; nmap->map[0][4] = BLOCK; nmap->map[0][5] = BLOCK; nmap->map[0][6] = BLOCK; nmap->map[0][7] = BLOCK; nmap->map[0][8] = BLOCK; nmap->map[0][9] = BLOCK; nmap->map[0][10] = BLOCK; nmap->map[0][11] = BLOCK; nmap->map[0][12] = BLOCK; nmap->map[0][13] = BLOCK; nmap->map[0][14] = BLOCK; nmap->map[0][15] = BLOCK; nmap->map[0][16] = BLOCK; nmap->map[0][17] = BLOCK; nmap->map[0][18] = EMPTY; nmap->map[0][19] = EMPTY; nmap->map[0][20] = EMPTY;

  nmap->map[1][0] = BLOCK; nmap->map[1][1] = BLOCK; nmap->map[1][2] = BLOCK; nmap->map[1][3] = BLOCK; nmap->map[1][4] = ITEM; nmap->map[1][5] = ITEM; nmap->map[1][6] = ITEM; nmap->map[1][7] = BLOCK; nmap->map[1][8] = BLOCK; nmap->map[1][9] = BLOCK; nmap->map[1][10] = BLOCK; nmap->map[1][11] = BLOCK; nmap->map[1][12] = BLOCK; nmap->map[1][13] = BLOCK; nmap->map[1][14] = ITEM; nmap->map[1][15] = ITEM; nmap->map[1][16] = ITEM; nmap->map[1][17] = BLOCK; nmap->map[1][18] = BLOCK; nmap->map[1][19] = BLOCK; nmap->map[1][20] = BLOCK;

  nmap->map[2][0] = BLOCK; nmap->map[2][1] = ITEM; nmap->map[2][2] = ITEM; nmap->map[2][3] = ITEM; nmap->map[2][4] = ITEM; nmap->map[2][5] = BLOCK; nmap->map[2][6] = ITEM; nmap->map[2][7] = ITEM; nmap->map[2][8] = ITEM; nmap->map[2][9] = ITEM; nmap->map[2][10] = ITEM; nmap->map[2][11] = ITEM; nmap->map[2][12] = ITEM; nmap->map[2][13] = ITEM; nmap->map[2][14] = ITEM; nmap->map[2][15] = BLOCK; nmap->map[2][16] = ITEM; nmap->map[2][17] = ITEM; nmap->map[2][18] = ITEM; nmap->map[2][19] = ITEM; nmap->map[2][20] = BLOCK;

  nmap->map[3][0] = BLOCK; nmap->map[3][1] = S_ITEM; nmap->map[3][2] = BLOCK; nmap->map[3][3] = BLOCK; nmap->map[3][4] = ITEM; nmap->map[3][5] = BLOCK; nmap->map[3][6] = ITEM; nmap->map[3][7] = BLOCK; nmap->map[3][8] = BLOCK; nmap->map[3][9] = BLOCK; nmap->map[3][10] = BLOCK; nmap->map[3][11] = BLOCK; nmap->map[3][12] = BLOCK; nmap->map[3][13] = BLOCK; nmap->map[3][14] = ITEM; nmap->map[3][15] = BLOCK; nmap->map[3][16] = ITEM; nmap->map[3][17] = BLOCK; nmap->map[3][18] = BLOCK; nmap->map[3][19] = S_ITEM; nmap->map[3][20] = BLOCK;

  nmap->map[4][0] = BLOCK; nmap->map[4][1] = ITEM; nmap->map[4][2] = ITEM; nmap->map[4][3] = ITEM; nmap->map[4][4] = ITEM; nmap->map[4][5] = BLOCK; nmap->map[4][6] = ITEM; nmap->map[4][7] = ITEM; nmap->map[4][8] = ITEM; nmap->map[4][9] = ITEM; nmap->map[4][10] = BLOCK; nmap->map[4][11] = ITEM; nmap->map[4][12] = ITEM; nmap->map[4][13] = ITEM; nmap->map[4][14] = ITEM; nmap->map[4][15] = BLOCK; nmap->map[4][16] = ITEM; nmap->map[4][17] = ITEM; nmap->map[4][18] = ITEM; nmap->map[4][19] = ITEM; nmap->map[4][20] = BLOCK;

  nmap->map[5][0] = BLOCK; nmap->map[5][1] = BLOCK; nmap->map[5][2] = BLOCK; nmap->map[5][3] = BLOCK; nmap->map[5][4] = ITEM; nmap->map[5][5] = BLOCK; nmap->map[5][6] = BLOCK; nmap->map[5][7] = BLOCK; nmap->map[5][8] = BLOCK; nmap->map[5][9] = ITEM; nmap->map[5][10] = BLOCK; nmap->map[5][11] = ITEM; nmap->map[5][12] = BLOCK; nmap->map[5][13] = BLOCK; nmap->map[5][14] = BLOCK; nmap->map[5][15] = BLOCK; nmap->map[5][16] = ITEM; nmap->map[5][17] = BLOCK; nmap->map[5][18] = BLOCK; nmap->map[5][19] = BLOCK; nmap->map[5][20] = BLOCK;

  nmap->map[6][0] = EMPTY; nmap->map[6][1] = EMPTY; nmap->map[6][2] = EMPTY; nmap->map[6][3] = BLOCK; nmap->map[6][4] = ITEM; nmap->map[6][5] = BLOCK; nmap->map[6][6] = BLOCK; nmap->map[6][7] = ITEM; nmap->map[6][8] = ITEM; nmap->map[6][9] = ITEM; nmap->map[6][10] = ITEM; nmap->map[6][11] = ITEM; nmap->map[6][12] = ITEM; nmap->map[6][13] = ITEM; nmap->map[6][14] = BLOCK; nmap->map[6][15] = BLOCK; nmap->map[6][16] = ITEM; nmap->map[6][17] = BLOCK; nmap->map[6][18] = EMPTY; nmap->map[6][19] = EMPTY; nmap->map[6][20] = EMPTY;

  nmap->map[7][0] = EMPTY; nmap->map[7][1] = EMPTY; nmap->map[7][2] = EMPTY; nmap->map[7][3] = BLOCK; nmap->map[7][4] = ITEM; nmap->map[7][5] = BLOCK; nmap->map[7][6] = BLOCK; nmap->map[7][7] = ITEM; nmap->map[7][8] = BLOCK; nmap->map[7][9] = BLOCK; nmap->map[7][10] = BLOCK; nmap->map[7][11] = BLOCK; nmap->map[7][12] = BLOCK; nmap->map[7][13] = ITEM; nmap->map[7][14] = BLOCK; nmap->map[7][15] = BLOCK; nmap->map[7][16] = ITEM; nmap->map[7][17] = BLOCK; nmap->map[7][18] = EMPTY; nmap->map[7][19] = EMPTY; nmap->map[7][20] = EMPTY;

  nmap->map[8][0] = BLOCK; nmap->map[8][1] = BLOCK; nmap->map[8][2] = BLOCK; nmap->map[8][3] = BLOCK; nmap->map[8][4] = ITEM; nmap->map[8][5] = BLOCK; nmap->map[8][6] = BLOCK; nmap->map[8][7] = ITEM; nmap->map[8][8] = BLOCK; nmap->map[8][9] = EMPTY; nmap->map[8][10] = EMPTY; nmap->map[8][11] = EMPTY; nmap->map[8][12] = BLOCK; nmap->map[8][13] = ITEM; nmap->map[8][14] = BLOCK; nmap->map[8][15] = BLOCK; nmap->map[8][16] = ITEM; nmap->map[8][17] = BLOCK; nmap->map[8][18] = BLOCK; nmap->map[8][19] = BLOCK; nmap->map[8][20] = BLOCK;

  nmap->map[9][0] = EMPTY; nmap->map[9][1] = EMPTY; nmap->map[9][2] = EMPTY; nmap->map[9][3] = EMPTY; nmap->map[9][4] = ITEM; nmap->map[9][5] = ITEM; nmap->map[9][6] = ITEM; nmap->map[9][7] = ITEM; nmap->map[9][8] = BLOCK; nmap->map[9][9] = EMPTY; nmap->map[9][10] = EMPTY; nmap->map[9][11] = EMPTY; nmap->map[9][12] = BLOCK; nmap->map[9][13] = ITEM; nmap->map[9][14] = ITEM; nmap->map[9][15] = ITEM; nmap->map[9][16] = ITEM; nmap->map[9][17] = EMPTY; nmap->map[9][18] = EMPTY; nmap->map[9][19] = EMPTY; nmap->map[9][20] = EMPTY;

  nmap->map[10][0] = BLOCK; nmap->map[10][1] = BLOCK; nmap->map[10][2] = BLOCK; nmap->map[10][3] = BLOCK; nmap->map[10][4] = ITEM; nmap->map[10][5] = BLOCK; nmap->map[10][6] = BLOCK; nmap->map[10][7] = ITEM; nmap->map[10][8] = BLOCK; nmap->map[10][9] = BLOCK; nmap->map[10][10] = BLOCK; nmap->map[10][11] = BLOCK; nmap->map[10][12] = BLOCK; nmap->map[10][13] = ITEM; nmap->map[10][14] = BLOCK; nmap->map[10][15] = BLOCK; nmap->map[10][16] = ITEM; nmap->map[10][17] = BLOCK; nmap->map[10][18] = BLOCK; nmap->map[10][19] = BLOCK; nmap->map[10][20] = BLOCK;

  nmap->map[11][0] = EMPTY; nmap->map[11][1] = EMPTY; nmap->map[11][2] = EMPTY; nmap->map[11][3] = BLOCK; nmap->map[11][4] = ITEM; nmap->map[11][5] = ITEM; nmap->map[11][6] = ITEM; nmap->map[11][7] = ITEM; nmap->map[11][8] = ITEM; nmap->map[11][9] = ITEM; nmap->map[11][10] = EMPTY; nmap->map[11][11] = ITEM; nmap->map[11][12] = ITEM; nmap->map[11][13] = ITEM; nmap->map[11][14] = ITEM; nmap->map[11][15] = ITEM; nmap->map[11][16] = ITEM; nmap->map[11][17] = BLOCK; nmap->map[11][18] = EMPTY; nmap->map[11][19] = EMPTY; nmap->map[11][20] = EMPTY;

  nmap->map[12][0] = EMPTY; nmap->map[12][1] = EMPTY; nmap->map[12][2] = EMPTY; nmap->map[12][3] = BLOCK; nmap->map[12][4] = ITEM; nmap->map[12][5] = BLOCK; nmap->map[12][6] = BLOCK; nmap->map[12][7] = BLOCK; nmap->map[12][8] = BLOCK; nmap->map[12][9] = ITEM; nmap->map[12][10] = BLOCK; nmap->map[12][11] = ITEM; nmap->map[12][12] = BLOCK; nmap->map[12][13] = BLOCK; nmap->map[12][14] = BLOCK; nmap->map[12][15] = BLOCK; nmap->map[12][16] = ITEM; nmap->map[12][17] = BLOCK; nmap->map[12][18] = EMPTY; nmap->map[12][19] = EMPTY; nmap->map[12][20] = EMPTY;

  nmap->map[13][0] = BLOCK; nmap->map[13][1] = BLOCK; nmap->map[13][2] = BLOCK; nmap->map[13][3] = BLOCK; nmap->map[13][4] = ITEM; nmap->map[13][5] = BLOCK; nmap->map[13][6] = ITEM; nmap->map[13][7] = ITEM; nmap->map[13][8] = ITEM; nmap->map[13][9] = ITEM; nmap->map[13][10] = BLOCK; nmap->map[13][11] = ITEM; nmap->map[13][12] = ITEM; nmap->map[13][13] = ITEM; nmap->map[13][14] = ITEM; nmap->map[13][15] = BLOCK; nmap->map[13][16] = ITEM; nmap->map[13][17] = BLOCK; nmap->map[13][18] = BLOCK; nmap->map[13][19] = BLOCK; nmap->map[13][20] = BLOCK;

  nmap->map[14][0] = BLOCK; nmap->map[14][1] = ITEM; nmap->map[14][2] = ITEM; nmap->map[14][3] = ITEM; nmap->map[14][4] = ITEM; nmap->map[14][5] = BLOCK; nmap->map[14][6] = ITEM; nmap->map[14][7] = BLOCK; nmap->map[14][8] = BLOCK; nmap->map[14][9] = BLOCK; nmap->map[14][10] = BLOCK; nmap->map[14][11] = BLOCK; nmap->map[14][12] = BLOCK; nmap->map[14][13] = BLOCK; nmap->map[14][14] = ITEM; nmap->map[14][15] = BLOCK; nmap->map[14][16] = ITEM; nmap->map[14][17] = ITEM; nmap->map[14][18] = ITEM; nmap->map[14][19] = ITEM; nmap->map[14][20] = BLOCK;

  nmap->map[15][0] = BLOCK; nmap->map[15][1] = S_ITEM; nmap->map[15][2] = BLOCK; nmap->map[15][3] = BLOCK; nmap->map[15][4] = ITEM; nmap->map[15][5] = BLOCK; nmap->map[15][6] = ITEM; nmap->map[15][7] = ITEM; nmap->map[15][8] = ITEM; nmap->map[15][9] = ITEM; nmap->map[15][10] = ITEM; nmap->map[15][11] = ITEM; nmap->map[15][12] = ITEM; nmap->map[15][13] = ITEM; nmap->map[15][14] = ITEM; nmap->map[15][15] = BLOCK; nmap->map[15][16] = ITEM; nmap->map[15][17] = BLOCK; nmap->map[15][18] = BLOCK; nmap->map[15][19] = S_ITEM; nmap->map[15][20] = BLOCK;

  nmap->map[16][0] = BLOCK; nmap->map[16][1] = ITEM; nmap->map[16][2] = ITEM; nmap->map[16][3] = ITEM; nmap->map[16][4] = ITEM; nmap->map[16][5] = ITEM; nmap->map[16][6] = ITEM; nmap->map[16][7] = BLOCK; nmap->map[16][8] = BLOCK; nmap->map[16][9] = BLOCK; nmap->map[16][10] = BLOCK; nmap->map[16][11] = BLOCK; nmap->map[16][12] = BLOCK; nmap->map[16][13] = BLOCK; nmap->map[16][14] = ITEM; nmap->map[16][15] = ITEM; nmap->map[16][16] = ITEM; nmap->map[16][17] = ITEM; nmap->map[16][18] = ITEM; nmap->map[16][19] = ITEM; nmap->map[16][20] = BLOCK;

  nmap->map[17][0] = BLOCK; nmap->map[17][1] = BLOCK; nmap->map[17][2] = BLOCK; nmap->map[17][3] = BLOCK; nmap->map[17][4] = BLOCK; nmap->map[17][5] = BLOCK; nmap->map[17][6] = BLOCK; nmap->map[17][7] = BLOCK; nmap->map[17][8] = BLOCK; nmap->map[17][9] = BLOCK; nmap->map[17][10] = BLOCK; nmap->map[17][11] = BLOCK; nmap->map[17][12] = BLOCK; nmap->map[17][13] = BLOCK; nmap->map[17][14] = BLOCK; nmap->map[17][15] = BLOCK; nmap->map[17][16] = BLOCK; nmap->map[17][17] = BLOCK; nmap->map[17][18] = BLOCK; nmap->map[17][19] = BLOCK; nmap->map[17][20] = BLOCK;


  character	player;
  character	ghost1;
  character	ghost2;
  character	ghost3;
  character	ghost4;

  player.x = 10;
  player.y = 11;
  player.xf = 10.0;
  player.yf = 11.0;
  player.dir = RIGHT;
  player.type = PLAYER;
  player.hasBonus = 0;

  ghost1.x = 9;
  ghost1.y = 8;
  ghost1.xf = 9.0;
  ghost1.yf = 8.0;
  ghost1.dir = UP;
  ghost1.type = CHARACTER;
  ghost1.hasBonus = 0;

  ghost2.x = 10;
  ghost2.y = 8;
  ghost2.xf = 10.0;
  ghost2.yf = 8.0;
  ghost2.dir = UP;
  ghost2.type = CHARACTER;
  ghost2.hasBonus = 0;

  ghost3.x = 11;
  ghost3.y = 8;
  ghost3.xf = 11.0;
  ghost3.yf = 8.0;
  ghost3.dir = UP;
  ghost3.type = CHARACTER;
  ghost3.hasBonus = 0;

  ghost4.x = 10;
  ghost4.y = 9;
  ghost4.xf = 10.0;
  ghost4.yf = 9.0;
  ghost4.dir = UP;
  ghost4.type = CHARACTER;
  ghost4.hasBonus = 0;

  nmap->player.push_back(player);
  nmap->player.push_back(ghost1);
  nmap->player.push_back(ghost2);
  nmap->player.push_back(ghost3);
  nmap->player.push_back(ghost4);


  nmap->startTime = clock();
  nmap->height = 18;
  nmap->width = 21;
  nmap->current_score.score = 0;
  nmap->hasWon = false;
  nmap->hasLost = false;
  nmap->save = false;

  return nmap;
}

void	Pacman::addScore(int point, map *map)
{

}



int	Pacman::goUp(map *map)
{
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER && (*node).dir != UP)
	{
	  (*node).dir = UP;
	  return (0);
	}
    }
  return (1);
}

int	Pacman::goDown(map *map)
{
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER && (*node).dir != DOWN)
	{
	  (*node).dir = DOWN;
	  return (0);
	}
    }
  return (1);
}

int	Pacman::goLeft(map *map)
{
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER && (*node).dir != LEFT)
	{
	  (*node).dir = LEFT;
	  return (0);
	}
    }
  return (1);
}

int	Pacman::goRight(map *map)
{
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER && (*node).dir != RIGHT)
	{
	  (*node).dir = RIGHT;
	  return (0);
	}
    }
  return (1);
}

extern "C"
class Pacman	*create_game()
{
  return new Pacman();
}
