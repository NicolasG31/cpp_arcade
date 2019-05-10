//
// my_open.hpp for  in /home/doremi/rendu/cpp/cpp_arcade
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Wed Mar 29 18:53:26 2017 Guillaume
// Last update Wed Mar 29 19:06:10 2017 Guillaume
//

#ifndef _MY_OPEN_HPP_
#define _MY_OPEN_HPP_

#include <iostream>
#include <dirent.h>

class my_open
{
private:

public:
  my_open();
  ~my_open();
  DIR *my_opendir(char *path);
  void my_closedir(DIR *dir);
  struct dirent *my_readdir(DIR *dir);
};

#endif
