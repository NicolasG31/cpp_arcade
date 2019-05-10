//
// my_dl.cpp for  in /home/doremi_g/arcade/cpp_arcade
//
// Made by Guillaume Doremieux
// Login   <doremi_g@epitech.net>
//
// Started on  Sun Apr  9 09:08:04 2017 Guillaume Doremieux
// Last update Sun Apr  9 09:12:37 2017 Guillaume Doremieux
//

#include "my_dl.hpp"


my_dl::my_dl()
{

}

my_dl::~my_dl()
{

}

void	*my_dl::my_dlopen(const char *file, int mod)
{
  return (dlopen(file, mod));
}

void	*my_dl::my_dlsym(void *handle, const char *name)
{
  return (dlsym(handle, name));
}
