//
// OpenGL.cpp for opengl in /home/nicolas/arcade/opengl
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Wed Mar 15 15:41:05 2017 Nicolas Guillon
// Last update Sun Apr  9 09:20:05 2017 Guillaume Doremieux
//

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
  this->_is_pacman = 0;
}

Ncurses::~Ncurses()
{
  this->_lib.my_endwin();
}

const std::string	Ncurses::getName() const
{
  return (std::string("Ncurses"));
}

event	Ncurses::getEvent()
{
  int i;

  i = this->_lib.my_getch();
  if (i == 27)
    return (ESCAPE);
  else if (i == KEY_UP)
    return (UP);
  else if (i == KEY_DOWN)
    return (DOWN);
  else if (i == KEY_LEFT)
    return (LEFT);
  else if (i == KEY_RIGHT)
    return (RIGHT);
  else if (i == 'a')
    return (PREV_LIB);
  else if (i == 'z')
    return (NEXT_LIB);
  else if (i == 'q')
    return (PREV_GAME);
  else if (i == 's')
    return (NEXT_GAME);
  else if (i == 'r')
    return (RESTART);
  else if (i == 'm')
    return (MENU);
  else if (i == 'p')
    return (PAUSE);
  return (ILLEGAL);
}

void	Ncurses::closeWindow()
{
  this->_lib.my_endwin();
}

void	Ncurses::startWindow(int width, int height, std::string name)
{
  if (!name.compare("Pacman"))
    this->_is_pacman = 1;
  else if (!name.compare("Snake"))
    this->_is_pacman = 0;
  this->_lib.my_initscr();
  this->_lib.my_noecho();
  this->_lib.my_keypad(stdscr, true);
  this->_lib.my_curs_set(0);
  this->_lib.my_nodelay(stdscr, true);
  this->_lib.my_start_color();
}

void  Ncurses::place_item_pacman(int x, int y, map_content content)
{
  if (content == ITEM)
  {
    this->_lib.my_init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    this->_lib.my_attron(4);
    this->_lib.my_printw(x, y, ".");
    this->_lib.my_attroff(4);
  }
  else if (content == S_ITEM)
  {
    this->_lib.my_init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    this->_lib.my_attron(4);
    this->_lib.my_printw(x, y, "@");
    this->_lib.my_attroff(4);
  }
  else if (content == BLOCK)
  {
    this->_lib.my_init_pair(2, COLOR_BLUE, COLOR_BLACK);
    this->_lib.my_attron(2);
    this->_lib.my_printw(x, y, "X");
    this->_lib.my_attroff(2);
  }    
}

void  Ncurses::place_item_snake(int x, int y, map_content content)
{
  if (content == ITEM)
    {
      this->_lib.my_init_pair(3, COLOR_RED, COLOR_BLACK);
      this->_lib.my_attron(3);
      this->_lib.my_printw(x, y, "@");
      this->_lib.my_attroff(3);
    }
  else if (content == BLOCK)
    {
      this->_lib.my_init_pair(2, COLOR_BLUE, COLOR_BLACK);
      this->_lib.my_attron(2);
      this->_lib.my_printw(x, y, "X");
      this->_lib.my_attroff(2);
    }
}

void	Ncurses::setPlayerSnake(character player, int x, int y, int i)
{
    this->_lib.my_init_pair(6, COLOR_GREEN, COLOR_BLACK);
    this->_lib.my_attron(6);
  if (i == 0)
    {
      if (player.dir == DOWN)
        this->_lib.my_printw(player.x + x, player.y + y, "v");
      else if (player.dir == UP)
        this->_lib.my_printw(player.x + x, player.y + y, "^");
      else if (player.dir == LEFT)
      this->_lib.my_printw(player.x + x, player.y + y, "<");
      else if (player.dir == RIGHT)
      this->_lib.my_printw(player.x + x, player.y + y, ">");
    }
  else 
   {
      this->_lib.my_printw(player.x + x, player.y + y, "O");
   }
    this->_lib.my_attroff(6);
}

void	Ncurses::setPlayerPacman(character player, int x, int y)
{
  this->_lib.my_init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  this->_lib.my_attron(4);
  this->_lib.my_printw(player.x + x, player.y + y, "O");
  this->_lib.my_attroff(4);
}

void  Ncurses::setCharacterBonusPacman(character player, int x, int y)
{
  this->_lib.my_init_pair(5, COLOR_CYAN, COLOR_BLACK);
  this->_lib.my_attron(5);
  this->_lib.my_printw(player.x + x, player.y + y, "&");  
  this->_lib.my_attroff(5);
}

void  Ncurses::setCharacterPacman(character player, int x, int y, int i)
{
  if (i == 1)
  {
    this->_lib.my_init_pair(3, COLOR_RED, COLOR_BLACK);
    this->_lib.my_attron(3);
    this->_lib.my_printw(player.x + x, player.y + y, "&");  
    this->_lib.my_attroff(3);
  }
  else if (i == 2)
  {
    this->_lib.my_init_pair(6, COLOR_GREEN, COLOR_BLACK);
    this->_lib.my_attron(6);
    this->_lib.my_printw(player.x + x, player.y + y, "&");  
    this->_lib.my_attroff(6);
  }
  else if (i == 3)
  {
    this->_lib.my_init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    this->_lib.my_attron(7);
    this->_lib.my_printw(player.x + x, player.y + y, "&");  
    this->_lib.my_attroff(7);
  }
  else if (i == 4)
  {
    this->_lib.my_init_pair(8, COLOR_WHITE, COLOR_BLACK);
    this->_lib.my_attron(8);
    this->_lib.my_printw(player.x + x, player.y + y, "&");  
    this->_lib.my_attroff(8);
  }
}

void  Ncurses::setCharacterBonusSnake(character player, int x, int y)
{
  this->_lib.my_printw(player.x + x, player.y + y, "O");  
}

void  Ncurses::setCharacterSnake(character player, int x, int y)
{
  this->_lib.my_printw(player.x + x, player.y + y, "O");  
}

void  Ncurses::displayChar(map *map, int scalex, int scaley)
{
   int		i = 0;
  character player;

  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER)
	      {
          player = (*node);
	        if (this->_is_pacman == 1)
            setPlayerPacman((*node), scalex, scaley);
          else
            setPlayerSnake((*node), scalex, scaley, i);
	      }
      else if (player.hasBonus > 0)
      {
        if (this->_is_pacman == 1)
          setCharacterBonusPacman((*node), scalex, scaley);
       else
      	  setCharacterBonusSnake((*node), scalex, scaley);
      }
	    else
      {
       if (this->_is_pacman == 1)
          setCharacterPacman((*node), scalex, scaley, i);
       else
      	  setCharacterSnake((*node), scalex, scaley);
      }
      i++;
    }
}

void  Ncurses::displayScore(map *map, int x, int y)
{
  std::string hscore = "Score : ";

  hscore += std::to_string(map->current_score.score);
  this->_lib.my_init_pair(6, COLOR_GREEN, COLOR_BLACK);
  this->_lib.my_attron(6);
  this->_lib.my_printw(x, y, hscore);
  this->_lib.my_attroff(6);
}

void	Ncurses::displayMap(map *map)
{
  int   row = 50;
  int   col = 50;
  int   x = 0;
  int   y = 0;
  int   scalex = 0;
  int   scaley = 0;

  timeout(200);
  this->_lib.my_clear();
  this->_lib.my_get_max_xy(&row, &col);
  if (col >= 30 && row >= 30)
  {
    scalex = (row - (map->width / 2)) / 2;
    scaley = (col - (map->width / 2)) / 2;
    while (y < map->height)
      {
        x = 0;
        while(x <= map->width)
          {
            if (this->_is_pacman == 1)
              place_item_pacman(x + scalex, y + scaley, map->map[y][x]);          
            else
              place_item_snake(x + scalex, y + scaley, map->map[y][x]);                    
            x++;
          }
          y++;
      }
      this->displayChar(map, scalex, scaley);
      displayScore(map, scalex, y + scaley + 1);
  }
  else
  {
    this->_lib.my_init_pair(3, COLOR_RED, COLOR_BLACK);
    this->_lib.my_attron(3);
    this->_lib.my_printw(5, 5, "La fenetre est trop petite");    
    this->_lib.my_attroff(3);
  }
   this->_lib.my_refresh();
}

void  Ncurses::displayTitleGame(int x, int y, std::vector<info_lib> lib, std::string name, int pos)
{
  this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
  this->_lib.my_attron(10);
  this->_lib.my_printw(x, y - 3, "Games");
  this->_lib.my_printw(x, y - 2, "-------");
  this->_lib.my_attroff(10);

  int i = 0;
  for (std::vector<info_lib>::iterator node = lib.begin(); node != lib.end(); ++node)
  {
    if(i == pos)
      {
        //il est selectioné
        this->_lib.my_init_pair(9, COLOR_BLACK, COLOR_WHITE);
        this->_lib.my_attron(9);
        this->_lib.my_printw(x, y, (*node).name);
        this->_lib.my_attroff(9);
      }
    else
      {
        this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
        this->_lib.my_attron(10);
        this->_lib.my_printw(x, y, (*node).name);
        this->_lib.my_attroff(10);
      }
    y += 2;
    i++;
  }
}

void  Ncurses::displayTitleLib(int x, int y, std::vector<info_lib> lib, std::string name, int pos)
{
  this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
  this->_lib.my_attron(10);
  this->_lib.my_printw(x, y - 3, "Libs");
  this->_lib.my_printw(x, y - 2, "-------");
  this->_lib.my_attroff(10);
  
  int i = 0;
  for (std::vector<info_lib>::iterator node = lib.begin(); node != lib.end(); ++node)
  {
    if(i == pos)
      {
        //il est selectioné
        this->_lib.my_init_pair(9, COLOR_BLACK, COLOR_WHITE);
        this->_lib.my_attron(9);
        this->_lib.my_printw(x, y, (*node).name);
        this->_lib.my_attroff(9);
      }
    else
      {
        this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
        this->_lib.my_attron(10);
        this->_lib.my_printw(x, y, (*node).name);
        this->_lib.my_attroff(10);
      }
    y += 2;
    i++;
  }
}

void  Ncurses::displayTitleHscore(int x, int y, std::vector<info_lib> lib, int pos)
{
  std::string tot = "";
  this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
  this->_lib.my_attron(10);
  this->_lib.my_printw(x, y - 3, "High Score");
  this->_lib.my_printw(x, y - 2, "-------");
  this->_lib.my_attroff(10);

  int i = 0;
  for (std::vector<info_lib>::iterator node = lib.begin(); node != lib.end(); ++node)
  {
    if (pos == i)
      {
        this->_lib.my_init_pair(12, COLOR_BLACK, COLOR_WHITE);
        this->_lib.my_attron(12);
        tot = (*node).hscore_name;
        tot += " : ";
        tot += std::to_string((*node).hscore);
        this->_lib.my_printw(x, y, tot);
        this->_lib.my_attroff(12);
      }
    i++;
  }
}


void  Ncurses::displayTitleName(int x, int y, std::string name)
{
  this->_lib.my_init_pair(10, COLOR_WHITE, COLOR_BLACK);
  this->_lib.my_attron(10);
  this->_lib.my_printw(x, y - 3, "Pseudo");
  this->_lib.my_printw(x, y - 2, "-------");
  this->_lib.my_attroff(10);

  this->_lib.my_init_pair(11, COLOR_WHITE, COLOR_BLUE);
  this->_lib.my_attron(11);
  this->_lib.my_printw(x, y, "                   ");
  this->_lib.my_printw(x, y, name);
  this->_lib.my_attroff(11);
}

int  Ncurses::startMenu(t_arcade *menu)
{
  int row = 300;
  int col = 300;
  int x = 5;
  int y = 5;
  int ch = 0;
  int pos_game = 0;
  int pos_lib = -2;
  int pos_curs = 0;
  std::string name = "|";

  this->startWindow(100, 100, "Menu");
  while (pos_curs != 3 && ch != 27)
  {
    ch = this->_lib.my_getch();
    this->_lib.my_clear();
    this->_lib.my_get_max_xy(&col, &row);
    x = (col - 90) / 2;
    y = (row - 20) / 2;
    if (col < 90)
    {
      this->_lib.my_printw(5, 5, "La fenetre est trop petite");
    }
    else if (row < 30)
    {
      this->_lib.my_printw(5, 5, "La fenetre est trop petite");
    }
    else
    {
      if (ch == '\n')
      {
        if (pos_curs == 0)
          pos_lib = 0;
        pos_curs++;
      }
      else if (ch == KEY_UP)
      {
        if (pos_curs == 0 && pos_game != 0)
        {
          pos_game--;
        }
        else if (pos_curs == 1 && pos_lib != 0)
        {
          pos_lib--;
        }
      }
      else if (ch == KEY_DOWN)
      {
        if (pos_curs == 0 && pos_game < (menu->games.size() - 1))
        {
          pos_game++;
        }
        else if (pos_curs == 1 && pos_lib < (menu->libs.size() - 1))
        {
          pos_lib++;
        }
      }
      else if (ch == KEY_LEFT)
      {
        if (pos_curs == 1)
          {
            pos_lib = -2;
            pos_curs--; 
          }
        else if (pos_curs != 0)
        {
          pos_curs--;
        }
      }
      else if (ch == KEY_RIGHT)
      {
        if (pos_curs == 0)
          pos_lib = 0;
          pos_curs++;
      }
    else if (pos_curs == 2 && ch == KEY_BACKSPACE && name.size() > 1)
    {
      name.erase(name.size() - 1);
      name.erase(name.size() - 1);
      name += '|';
    }
    else if (pos_curs == 2 && ch < 127 && ch > 31 && name.size() < 15)
      {
        name.erase(name.size() - 1);
        name += (char)ch;
        name += '|';
      }
      timeout(200);
      displayTitleGame(x, y, menu->games, "Games", pos_game);
      displayTitleLib(x + 20, y, menu->libs, "Libs", pos_lib);
      displayTitleName(x + 40, y, name);
      displayTitleHscore(x + 70, y, menu->games, pos_game);
    }
   this->_lib.my_refresh();
  }
  if (ch == 27)
    return (-1);
  if (pos_lib == -2)
    menu->pos_graph = 0;
  else
    menu->pos_graph = pos_lib;
  menu->pos_game = pos_game;
  name.erase(name.size() - 1);
  if (name.size() == 0)
    name = "Anonymous";
  menu->user = name;
  this->closeWindow();
  return (0);
}

extern "C"
class Ncurses	*create_graph()
{
  return new Ncurses();
}
