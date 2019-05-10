//
// my_dl.cpp for  in /home/doremi_g/arcade/cpp_arcade
//
// Made by Guillaume Doremieux
// Login   <doremi_g@epitech.net>
//
// Started on  Sun Apr  9 09:08:04 2017 Guillaume Doremieux
// Last update Sun Apr  9 11:51:17 2017 Nicolas Guillon
//

#include "my_memcpy.hpp"


my_memcpy::my_memcpy()
{

}

my_memcpy::~my_memcpy()
{

}

void	*my_memcpy::my_memcpydo(void *dest, const void *src, size_t n)
{
  return (memcpy(dest, src, n));
}
