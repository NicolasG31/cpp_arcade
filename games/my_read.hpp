//
// my_read.hpp for  in /home/doremi/rendu/cpp/cpp_arcade/games
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Tue Apr  4 13:24:23 2017 Guillaume
// Last update Tue Apr  4 13:30:44 2017 Guillaume
//

#ifndef _MY_READ_HPP_
#define _MY_READ_HPP

#include <unistd.h>

class my_read
{
public:
    my_read();
    ~my_read();

  int my_read_mouli(int fd, void *core, long size);
  int my_write_mouli(int fd, void *core, long size);
};


#endif
