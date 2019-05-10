//
// sfml.hpp for sfml in /home/linh/rendu/cpp/arcade/arcade
// 
// Made by Jerome Dang
// Login   <dang_j@epitech.net>
// 
// Started on  Thu Mar 16 14:11:51 2017 Jerome Dang
// Last update Fri Apr  7 15:21:30 2017 Jerome Dang
//

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>

#include "../IGraph.hpp"
#include "../../my.hpp"

class Sfml : public IGraph
{
private:
  std::string		_game;
  sf::RenderWindow	*_window;
  sf::Texture		_texture;
  bool			_hasTexture;
  sf::Font		_font;
  sf::Text		_text;
  int			_size;
  int			_status;
  const std::string	_name = "SFML";

public:
  Sfml();
  virtual ~Sfml();

  virtual const std::string	getName() const;

  virtual void	startWindow(int width, int height, std::string name);
  virtual void	closeWindow();

  virtual void	displayMap(map *map);
  void		displayMapNoT(map_content map, int x, int y);
  virtual void	displayChar(sf::Sprite sprite, map *map);
  void		displayCharNoT(map *map);
  virtual int	startMenu(t_arcade *menu);
  void		displayMenu(t_arcade *menu, int pos);
  void		displayExt(sf::Sprite sprite, character player, character head, int i);
  void		displayTrunc(sf::Sprite sprite, character head, character trunc, character tail);
  void		displaySnake(sf::Sprite sprite, map *map);

  void		setText(std::string str, int x, int y, int color);
  void		setSprite(sf::Sprite &sprite, map_content content);
  void		setPlayer(character player, sf::Sprite &sprite);
  void		setCharacter(character player, sf::Sprite &sprite, int i);

  virtual event	getEvent();
};

#endif
