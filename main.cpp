/*
** main.c for bootstrap in /home/nicolas/opengl
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Tue Mar  7 14:06:20 2017 Nicolas Guillon
// Last update Sun Apr  9 09:24:14 2017 Guillaume Doremieux
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "graph/IGraph.hpp"
#include "games/IGame.hpp"
#include "my.hpp"
#include "my_dl.hpp"
#include "init_menu.hpp"

typedef  IGraph *(*maker_graph)();
typedef  IGame *(*maker_game)();

t_arcade	*set_core(IGraph *default_graph, char *path)
{
  /*
    INITIALISATION DU COEUR ARCADE
   */
  t_arcade	*ncore;
  std::vector<info_lib> games;
  std::vector<info_lib> libs;
  init_menu		menu;

  ncore = new t_arcade();
  ncore->libs = menu.get_all_libs();
  ncore->games = menu.get_all_games();
  ncore->_current_graph = default_graph; // Graph chargée en arg
  ncore->_current_game = NULL;
  ncore->_current_map = NULL;
  ncore->pos_graph = 0; // Position 0, première lib graph
  ncore->pos_game = 0; // Position -1, pas encore init
  ncore->user = "";

  return ncore;
}

info_lib  getTheGoodOne(std::vector<info_lib> lib, int pos)
{
  int i = 0;

  for (std::vector<info_lib>::iterator node = lib.begin(); node != lib.end(); ++node)
  {
    if (i == pos)
      return ((*node));
    i++;
  }
}

int	changeLib(t_arcade *core)
{
  info_lib lib;
  info_lib lib_game;
  my_dl	   dl;

  lib_game = getTheGoodOne(core->games, core->pos_game);
  lib = getTheGoodOne(core->libs, core->pos_graph);

  //Recuperation de la bonne lib  void		*handle;
  maker_graph	maker;

  core->handle_lib = dl.my_dlopen(lib.path.c_str(), RTLD_LAZY);
  if (!core->handle_lib)
    {
      fprintf(stderr, "%s\n", dlerror());
      return (-1);
    }

  void *create_syml = dl.my_dlsym(core->handle_lib, "create_graph");
  if (create_syml == NULL)
    {
      std::cerr << "Wrong library :(" << std::endl;
      return (-1);
    }
  maker = (maker_graph)create_syml;
  core->_current_graph = maker();

  //recuperation du bon jeu

  core->handle_game = dl.my_dlopen(lib_game.path.c_str(), RTLD_LAZY);
  if (!core->handle_game)
    {
      fprintf(stderr, "%s\n", dlerror());
      return (-1);
    }

  void *create_sym = dl.my_dlsym(core->handle_game, "create_game");
  if (create_sym == NULL)
    {
      std::cerr << "Wrong game :(" << std::endl;
      return (-1);
    }
  maker_game makerg = (maker_game)create_sym;
  IGame *game = makerg();

  core->_current_game = game;
  core->_current_map = game->createMap();
}

int  nextGame(t_arcade *core)
{
  info_lib lib_game;
  my_dl	   dl;

  lib_game = getTheGoodOne(core->games, core->pos_game);

  core->_current_graph->closeWindow();

  core->handle_game = dl.my_dlopen(lib_game.path.c_str(), RTLD_LAZY);
  if (!core->handle_game)
    {
      fprintf(stderr, "%s\n", dlerror());
      return (-1);
    }

  void *create_sym = dl.my_dlsym(core->handle_game, "create_game");
  if (create_sym == NULL)
    {
      std::cerr << "Wrong game :(" << std::endl;
      core->_current_graph->closeWindow();
      return (-1);
    }
  maker_game makerg = (maker_game)create_sym;
  IGame *game = makerg();

  core->_current_game = game;
  core->_current_map = game->createMap();
  core->_current_graph->startWindow(core->_current_map->width, core->_current_map->height, core->_current_game->getName());
  return (0);
}

int  nextLib(t_arcade *core)
{
  info_lib lib;
  my_dl	   dl;

  lib = getTheGoodOne(core->libs, core->pos_graph);
  core->_current_graph->closeWindow();

  maker_graph	maker;

  core->handle_lib = dl.my_dlopen(lib.path.c_str(), RTLD_LAZY);
  if (!core->handle_lib)
    {
      fprintf(stderr, "%s\n", dlerror());
      return (-1);
    }

  void *create_syml = dl.my_dlsym(core->handle_lib, "create_graph");
  if (create_syml == NULL)
    {
      std::cerr << "Wrong lib :(" << std::endl;
      return (-1);
    }
  maker = (maker_graph)create_syml;
  core->_current_graph = maker();
  core->_current_graph->startWindow(core->_current_map->width, core->_current_map->height, core->_current_game->getName());
  return (0);
}

std::string getGameName(std::vector<info_lib> lib, int pos)
{
  int i = 0;

  for (std::vector<info_lib>::iterator node = lib.begin(); node != lib.end(); ++node)
  {
    if (i == pos)
      return ((*node).name);
    i++;
  }
  return "Error";
}

void  saveScore(t_arcade *core)
{
  std::string nscore = "";
  std::ofstream file;
  std::string game_name = getGameName(core->games, core->pos_game);
  std::string file_name;

  nscore = core->user + " : ";
  file_name = "." + game_name  + ".score";

  file.open(file_name.c_str(), std::ios::app);

  if (file.is_open())
  {
    file << nscore;
    file << core->_current_map->current_score.score;
    file << "\n";
  }
  else
  {
    std::cerr << "No file score" << std::endl;
  }
  file.close();
}

int	main_loop(t_arcade *core)
{
  int	pause = 0;
  if (core->_current_graph->startMenu(core) == -1)
  {
    core->_current_graph->closeWindow();
    return (0);
  }
  if (changeLib(core) == -1)
    return (0);
  core->_current_graph->startWindow(core->_current_map->width, core->_current_map->height, core->_current_game->getName());
  while (42)
    {
      switch (core->_current_graph->getEvent())
  	{
  	case ESCAPE:
  	  core->_current_graph->closeWindow();
	  return (0);
  	  break;
  	case UP:
	  if (pause == 0)
	    core->_current_game->goUp(core->_current_map);
  	  break;
  	case DOWN:
	  if (pause == 0)
	    core->_current_game->goDown(core->_current_map);
  	  break;
  	case RIGHT:
	  if (pause == 0)
	    core->_current_game->goRight(core->_current_map);
  	  break;
  	case LEFT:
	  if (pause == 0)
	    core->_current_game->goLeft(core->_current_map);
  	  break;
  	case RESTART:
	  core->_current_map = core->_current_game->createMap();
  	  break;
  	case PAUSE:
	  if (pause == 0)
	    pause = 1;
	  else
	    pause = 0;
  	  break;
  	case MENU:
    	  core->_current_graph->closeWindow();
	  main_loop(core);
        return (0);
  	  break;
  	case NEXT_LIB:
      if (core->pos_graph < core->libs.size() - 1)
        core->pos_graph++;
      else
        core->pos_graph = 0;
      if (nextLib(core) == -1)
	return (-1);
  	  break;
  	case PREV_LIB:
      if (core->pos_graph > 0)
        core->pos_graph--;
      else
        core->pos_graph = core->libs.size() - 1;
      if (nextLib(core) == -1)
	return (-1);
  	  break;
  	case NEXT_GAME:
      if (core->pos_game < core->games.size() - 1)
        core->pos_game++;
      else
        core->pos_game = 0;
      if (nextGame(core) == -1)
	return (-1);
  	  break;
  	case PREV_GAME:
      if (core->pos_game > 0)
        core->pos_game--;
      else
        core->pos_game = core->games.size() - 1;
      if (nextGame(core) == -1)
	return (-1);
  	  break;
  	case ILLEGAL:
  	  break;
  	}
      core->_current_graph->displayMap(core->_current_map);
      if (pause == 0)
	core->_current_game->runGame(core->_current_map);
      if ((core->_current_map->hasWon == true || core->_current_map->hasLost == true) && core->_current_map->save == false)
      {
        saveScore(core);
        core->_current_map->save = true;
      }
    }
  return (0);
}

int	l_arcade(IGraph *default_graph, char *path)
{
  t_arcade	*core;

  core = set_core(default_graph, path);

  main_loop(core);
  return (1);
}

int	open_lib(char *lib)
{
  void		*handle;
  maker_graph	maker;
  my_dl		dl;

  handle = dl.my_dlopen(lib, RTLD_LAZY);
  if (!handle)
    {
      fprintf(stderr, "%s\n", dlerror());
      return (0);
    }

  void *create_sym = dl.my_dlsym(handle, "create_graph");
  if (create_sym == NULL)
    {
      std::cerr << "Wrong library :(" << std::endl;
      return (-1);
    }
  maker = (maker_graph)create_sym;
  IGraph *graph = maker();

  // Envoie la lib lancée par défaut et le path
  l_arcade(graph, lib);
  dlclose(handle);
  return (1);
}

int	main(int ac, char **av)
{
  if (ac > 1)
    return (open_lib(av[1]));
  std::cout << "./arcade [LIB Path]" << std::endl;
  return (0);
}
