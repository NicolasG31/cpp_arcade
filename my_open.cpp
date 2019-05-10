//
// my_open.cpp for  in /home/doremi/rendu/cpp/cpp_arcade
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Wed Mar 29 18:55:46 2017 Guillaume
// Last update Wed Mar 29 19:07:31 2017 Guillaume
//

#include "my_open.hpp"

my_open::my_open()
{

}

my_open::~my_open()
{

}

DIR	*my_open::my_opendir(char *path)
{
  return (opendir(path));
}

void	my_open::my_closedir(DIR *dir)
{
  closedir(dir);
}

struct dirent *my_open::my_readdir(DIR *dir)
{
  return (readdir(dir));
}
