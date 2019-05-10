//
// init_menu.hpp for  in /home/doremi/rendu/cpp/cpp_arcade
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Thu Mar 30 12:41:15 2017 Guillaume
// Last update Thu Mar 30 12:49:41 2017 Guillaume
//

#ifndef _INIT_MENU_HPP_
#define _INIT_MENUU_HPP

#include <iostream>
#include "my.hpp"
#include "my_open.hpp"

class init_menu
{
private:
  my_open	_lib;
public:
  init_menu();
  ~init_menu();
  std::vector<info_lib>	get_all_libs();
  std::vector<info_lib>	get_all_games();
  void			get_hscore(info_lib *elem);

};

#endif
