//
// interface.hpp for  in /home/sanchez/rendu/tek2/cpp/cpp_arcade
//
// Made by sanchez
// Login   <sanchez@epitech.net>
//
// Started on  Tue Mar 14 16:08:37 2017 sanchez
// Last update Tue Apr  4 13:02:07 2017 Guillaume
//

#ifndef IGRAPH_HPP_
# define IGRAPH_HPP_

#include "../my.hpp"

class		IGraph
{
public:
  virtual	~IGraph() {};

  virtual const std::string	getName() const = 0;
  // Window handler
  virtual void	startWindow(int width, int height, std::string name) = 0;
  virtual void	closeWindow() = 0;
  virtual void	displayMap(map *map) = 0;
  virtual int  startMenu(t_arcade *menu) = 0;

  // Events handler
  virtual event	getEvent() = 0;
};

#endif
