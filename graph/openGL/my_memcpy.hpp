//
// my_dl.hpp for  in /home/doremi_g/arcade/cpp_arcade
//
// Made by Guillaume Doremieux
// Login   <doremi_g@epitech.net>
//
// Started on  Sun Apr  9 09:02:13 2017 Guillaume Doremieux
// Last update Sun Apr  9 11:51:02 2017 Nicolas Guillon
//


#ifndef _MEMCPY_HPP_
#define _MEMCPY_HPP_

#include <string.h>
#include <stdlib.h>

class my_memcpy
{
public:
    my_memcpy();
    ~my_memcpy();
  void *my_memcpydo(void *dest, const void *src, size_t n);
};


#endif
