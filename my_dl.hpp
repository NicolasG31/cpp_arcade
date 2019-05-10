//
// my_dl.hpp for  in /home/doremi_g/arcade/cpp_arcade
//
// Made by Guillaume Doremieux
// Login   <doremi_g@epitech.net>
//
// Started on  Sun Apr  9 09:02:13 2017 Guillaume Doremieux
// Last update Sun Apr  9 09:12:21 2017 Guillaume Doremieux
//


#ifndef _DL_HPP_
#define _DL_HPP_

#include <dlfcn.h>

class my_dl
{
public:
    my_dl();
    ~my_dl();
  void *my_dlsym(void *handle, const char *name);
  void *my_dlopen(const char *file, int mod);
};


#endif
