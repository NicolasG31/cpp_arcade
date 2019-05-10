//
// my_ncurses.cpp for  in /home/doremi/rendu/cpp/cpp_arcade/graph
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Wed Mar 22 18:12:06 2017 Guillaume
// Last update Thu Mar 30 12:38:20 2017 Guillaume
//

#include "my_ncurses.hpp"

my_ncurses::my_ncurses()
{
}

my_ncurses::~my_ncurses()
{
}

void    my_ncurses::my_get_max_xy(int *x, int *y)
{
  int row;
  int col;

  getmaxyx(stdscr, row, col);
  *x = col;
    *y = row;
}

void    my_ncurses::my_printw(int x, int y, std::string str)
{
    mvprintw(y, x, str.c_str());
}

void    my_ncurses::my_clear()
{
    clear();
}

int     my_ncurses::my_getch()
{
    return (getch());
}

void    my_ncurses::my_refresh()
{
    refresh();
}

void    my_ncurses::my_start_color()
{
    start_color();
}

void    my_ncurses::my_endwin()
{
    endwin();
}

void    my_ncurses::my_init_pair(short pair, short t, short b)
{
    init_pair(pair, t, b);
}

void    my_ncurses::my_attron(short pair)
{
    attron(COLOR_PAIR(pair));
}

void    my_ncurses::my_attroff(short pair)
{
    attron(COLOR_PAIR(pair));
}

void    my_ncurses::my_initscr()
{
    initscr();
}

void    my_ncurses::my_noecho()
{
    noecho();
}

void    my_ncurses::my_keypad(WINDOW *win, bool b)
{
    keypad(win, b);
}

void    my_ncurses::my_curs_set(int nb)
{
    curs_set(nb);
}

void    my_ncurses::my_nodelay(WINDOW *win, bool b)
{
    nodelay(win, b);
}
