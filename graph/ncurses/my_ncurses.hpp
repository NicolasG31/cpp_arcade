//
// my_ncurses.hpp for  in /home/doremi/rendu/cpp/cpp_arcade/graph
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Wed Mar 22 18:12:37 2017 Guillaume
// Last update Wed Mar 22 18:13:05 2017 Guillaume
//

#ifndef _MY_NCURSES_HPP_
#define _MY_NCURSES_HPP_

#include <iostream>
#include <ncurses.h>

class  my_ncurses
{
    private:

    public:
        my_ncurses();
        ~my_ncurses();
        void     my_get_max_xy(int *x, int *y);
        void    my_printw(int x, int y, std::string str);
        void    my_clear();
        int     my_getch();
        void    my_refresh();
        void    my_start_color();
        void    my_endwin();
        void    my_init_pair(short pair, short t, short b);
        void    my_attron(short pair);
        void    my_attroff(short pair);
        void    my_initscr();
        void    my_noecho();
        void    my_keypad(WINDOW *win, bool b);
        void    my_curs_set(int nb);
        void    my_nodelay(WINDOW *win, bool b);
};


#endif
