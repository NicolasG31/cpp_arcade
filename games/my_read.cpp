//
// my_read.cpp for  in /home/doremi/rendu/cpp/cpp_arcade/games
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Tue Apr  4 13:18:09 2017 Guillaume
// Last update Tue Apr  4 13:29:42 2017 Guillaume
//

#include "my_read.hpp"


my_read::my_read()
{

}

my_read::~my_read()
{

}

int	my_read::my_read_mouli(int fd, void *core, long size)
{
  return (read(fd, core, size));
}

int	my_read::my_write_mouli(int fd, void *core, long size)
{
  return (write(fd, core, size));
}
