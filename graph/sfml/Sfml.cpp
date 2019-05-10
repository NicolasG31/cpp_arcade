//
// Sfml.cpp for Sfml in /home/linh/rendu/cpp/arcade/arcade
// 
// Made by Jerome Dang
// Login   <dang_j@epitech.net>
// 
// Started on  Thu Mar 16 15:41:45 2017 Jerome Dang
// Last update Sun Apr  9 18:58:28 2017 Nicolas Guillon
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#include "Sfml.hpp"

Sfml::Sfml()
{
  _window = NULL;
  _size = 48;
  _status = 0;
  _hasTexture = false;
}

Sfml::~Sfml()
{
}

const std::string	Sfml::getName() const
{
  return (_name);
}

void			Sfml::closeWindow()
{
  _window->close();
  _window = NULL;
}

void	Sfml::startWindow(int width, int height, std::string name)
{
  _window = new sf::RenderWindow(sf::VideoMode(width * _size, height * _size), name, sf::Style::Default);
  if (!_window || !_font.loadFromFile("./textures/Roboto.ttf"))
    exit(1);
  _text.setFont(_font);
  _window->setFramerateLimit(10);
  _game = name;
  if (!name.compare("Pacman") && _texture.loadFromFile("./textures/pacman_sfml.png"))
    _hasTexture = true;
  else if (!name.compare("Snake") && _texture.loadFromFile("./textures/snake_sfml.png"))
    {
      _hasTexture = true;
      _window->setFramerateLimit(10);
    }
  else
    _hasTexture = false;
}

event			Sfml::getEvent()
{
  sf::Event		event;

  while (_window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	return (ESCAPE);
      else if (event.type == sf::Event::Resized)
	_window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    return (ESCAPE);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      return (UP);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    return (DOWN);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    return (LEFT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    return (RIGHT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    return (PREV_LIB);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    return (NEXT_LIB);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    return (PREV_GAME);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    return (NEXT_GAME);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    return (RESTART);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    return (MENU);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    return (PAUSE);
  return (ILLEGAL);
}

void	Sfml::setSprite(sf::Sprite &sprite, map_content content)
{
  if (content == EMPTY)
    sprite.setTextureRect(sf::IntRect(3 * _size, 3 * _size, _size, _size));
  else if (content == BLOCK)
    sprite.setTextureRect(sf::IntRect(2 * _size, 3 * _size, _size, _size));
  else if (content == PLATFORM)
    sprite.setTextureRect(sf::IntRect(2 * _size, 3 * _size, _size, _size));
  else if (content == ITEM)
    sprite.setTextureRect(sf::IntRect(1 * _size, 3 * _size, _size, _size));
  else if (content == S_ITEM)
    sprite.setTextureRect(sf::IntRect(0 * _size, 3 * _size, _size, _size));
}

void	Sfml::setPlayer(character player, sf::Sprite &sprite)
{
  int	x;
  int	y;

  if (player.dir == DOWN)
    {
      x = 0;
      (_status >= 5) ? (y = 1) : (y = 2);
    }
  else if (player.dir == UP)
    {
      x = 1;
      (_status >= 5) ? (y = 1) : (y = 2);
    }
  else if (player.dir == LEFT)
    {
      x = 2;
      (_status >= 5) ? (y = 1) : (y = 2);
    }
  else if (player.dir == RIGHT)
    {
      x = 3;
      (_status >= 5) ? (y = 1) : (y = 2);
    }
  sprite.setTextureRect(sf::IntRect(x * _size, y * _size, _size, _size));
  sprite.setPosition(player.xf * _size, player.yf * _size);
  _window->draw(sprite);
  _status >= 10 ? (_status = 0) : (_status += 2);
}

void	Sfml::setCharacter(character player, sf::Sprite &sprite, int i)
{
  sprite.setTextureRect(sf::IntRect(i * _size, 0, _size, _size));
  sprite.setPosition(player.xf * _size, player.yf * _size);
  _window->draw(sprite);
}

void		Sfml::displayChar(sf::Sprite sprite, map *map)
{
  int		i = 0;
  character	player;

  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).type == PLAYER)
	{
	  player = (*node);
	  setPlayer((*node), sprite);
	}
      else
	if (player.hasBonus > 0)
	  setCharacter((*node), sprite, 4);
	else
	  setCharacter((*node), sprite, i - 1);
      i++;
    }
}

void	Sfml::displayExt(sf::Sprite sprite, character player, character head, int i)
{
  int	j;

  if (i == 1)
    player.dir = head.dir;
  if (player.dir == DOWN)
    j = 0;
  else if (player.dir == UP)
    j = 1;
  else if (player.dir == LEFT)
    j = 2;
  else if (player.dir == RIGHT)
    j = 3;
  sprite.setTextureRect(sf::IntRect(j * _size, (i + 1) * _size, _size, _size));
  sprite.setPosition(player.xf * _size, player.yf * _size);
  _window->draw(sprite);
}

void	Sfml::displayTrunc(sf::Sprite sprite, character head, character trunc, character tail)
{
  if (head.dir == tail.dir)
    {
      if (head.dir == LEFT || head.dir == RIGHT)
	sprite.setTextureRect(sf::IntRect(4 * _size, 0, _size, _size));
      else if (head.dir == UP || head.dir == DOWN)
	sprite.setTextureRect(sf::IntRect(4 * _size, _size, _size, _size));
    }
  else if (head.dir == trunc.dir)
    {
      if (head.dir == LEFT || head.dir == RIGHT)
	sprite.setTextureRect(sf::IntRect(4 * _size, 0, _size, _size));
      else if (head.dir == UP || head.dir == DOWN)
	sprite.setTextureRect(sf::IntRect(4 * _size, _size, _size, _size));
    }
  else
    {
      if (head.dir == DOWN && tail.dir == LEFT)
      	sprite.setTextureRect(sf::IntRect(0, 0, _size, _size));
      else if (head.dir == RIGHT && tail.dir == UP)
	sprite.setTextureRect(sf::IntRect(0, 0, _size, _size));

      else if (head.dir == LEFT && tail.dir == UP)
      	sprite.setTextureRect(sf::IntRect(1 * _size, 0, _size, _size));
      else if (head.dir == DOWN && tail.dir == RIGHT)
      	sprite.setTextureRect(sf::IntRect(1 * _size, 0, _size, _size));

      else if (head.dir == RIGHT && tail.dir == DOWN)
      	sprite.setTextureRect(sf::IntRect(2 * _size, 0, _size, _size));
      else if (head.dir == UP && tail.dir == LEFT)
      	sprite.setTextureRect(sf::IntRect(2 * _size, 0, _size, _size));

      else if (head.dir == UP && tail.dir == RIGHT)
      	sprite.setTextureRect(sf::IntRect(3 * _size, 0, _size, _size));
      else if (head.dir == LEFT && tail.dir == DOWN)
      	sprite.setTextureRect(sf::IntRect(3 * _size, 0, _size, _size));

      else if (head.dir == RIGHT && tail.dir == LEFT && trunc.dir == UP)
      	sprite.setTextureRect(sf::IntRect(0, 0, _size, _size));
      else if (head.dir == RIGHT && tail.dir == LEFT && trunc.dir == DOWN)
      	sprite.setTextureRect(sf::IntRect(2 * _size, 0, _size, _size));

      else if (head.dir == LEFT && tail.dir == RIGHT && trunc.dir == UP)
      	sprite.setTextureRect(sf::IntRect(_size, 0, _size, _size));
      else if (head.dir == LEFT && tail.dir == RIGHT && trunc.dir == DOWN)
      	sprite.setTextureRect(sf::IntRect(3 * _size, 0, _size, _size));

      else if (head.dir == UP && tail.dir == DOWN && trunc.dir == LEFT)
	sprite.setTextureRect(sf::IntRect(2 * _size, 0, _size, _size));
      else if (head.dir == UP && tail.dir == DOWN && trunc.dir == RIGHT)
	sprite.setTextureRect(sf::IntRect(3 * _size, 0, _size, _size));

      else if (head.dir == DOWN && tail.dir == UP && trunc.dir == LEFT)
	sprite.setTextureRect(sf::IntRect(0, 0, _size, _size));
      else if (head.dir == DOWN && tail.dir == UP && trunc.dir == RIGHT)
	sprite.setTextureRect(sf::IntRect(_size, 0, _size, _size));
    }
  sprite.setPosition(trunc.xf * _size, trunc.yf * _size);
  _window->draw(sprite);
}

void	Sfml::displaySnake(sf::Sprite sprite, map *map)
{
  int	i;

  i = 0;
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if (i == 0 || i == map->player.size() - 1)
	i == 0 ? displayExt(sprite, (*node), (*node), 0) : displayExt(sprite, (*node), map->player.at(i - 1), 1);
      else
	displayTrunc(sprite, map->player.at(i - 1), (*node), map->player.at(i + 1));
      i++;
    }
}

void			Sfml::displayCharNoT(map *map)
{
  int			i;
  sf::CircleShape	circle(24.0);

  i = 0;
  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end(); ++node)
    {
      if ((*node).hasBonus != 0)
  	i = 5;
      if ((*node).type == PLAYER)
  	circle.setFillColor(sf::Color::Yellow);
      else if ((*node).type == CHARACTER && i == 1)
	circle.setFillColor(sf::Color::Red);
      else if ((*node).type == CHARACTER && i == 2)
	circle.setFillColor(sf::Color(255, 192, 203));
      else if ((*node).type == CHARACTER && i == 3)
	circle.setFillColor(sf::Color(0, 255, 255));
      else if ((*node).type == CHARACTER && i == 4)
	circle.setFillColor(sf::Color::Yellow);
      else
  	circle.setFillColor(sf::Color::Blue);
      circle.setPosition((*node).x * 48, (*node).y * 48);
      _window->draw(circle);
      i++;
    }
}

void		Sfml::displayMapNoT(map_content map, int x, int y)
{
  sf::RectangleShape	rect(sf::Vector2f(48, 48));

  rect.setPosition(x * 48, y * 48);
  if (map == BLOCK)
    rect.setFillColor(sf::Color(174, 137, 118));
  else if (map == ITEM)
    {
      rect.setSize(sf::Vector2f(10, 10));
      rect.setPosition((x ) * 48 + 19, (y ) * 48 + 19);
      rect.setFillColor(sf::Color::Yellow);
    }
  else if (map == S_ITEM)
    {
      rect.setSize(sf::Vector2f(20, 20));
      rect.setPosition((x ) * 48 + 14, (y ) * 48 + 14);
      rect.setFillColor(sf::Color::Yellow);
    }
  else
    rect.setFillColor(sf::Color::Black);
  _window->draw(rect);
}

void	Sfml::displayMap(map *map)
{
  int	x;
  int	y;
  sf::Sprite sprite;

  if (_window != NULL)
    {
      if (_hasTexture == true)
	sprite.setTexture(_texture);
      _window->clear();
      y = 0;
      while (y < map->height)
	{
	  x = 0;
	  while (x < map->width)
	    {
	      if (_hasTexture == true)
		{
		  setSprite(sprite, map->map[y][x]);
		  sprite.setPosition(x * _size, y * _size);
		  _window->draw(sprite);
		}
	      else
		displayMapNoT(map->map[y][x], x, y);
	      x++;
	    }
	  y++;
	}
      if (_hasTexture == true && !_game.compare("Pacman"))
	displayChar(sprite, map);
      else if (_hasTexture == true && !_game.compare("Snake"))
	displaySnake(sprite, map);
      else
	displayCharNoT(map);
      setText(std::to_string(map->current_score.score), 10, 10, 1);
      _window->display();
    }
  else
    std::cerr << "Error, graphical library is not set" << std::endl;
}

void	Sfml::setText(std::string str, int x, int y, int color)
{
  _text.setString(str);
  _text.setCharacterSize(20);
  _text.setPosition(x, y);
  if (color == 0)
    _text.setFillColor(sf::Color::White);
  // _text.setFillColor(sf::Color::White);
  else if (color == 1)
    _text.setFillColor(sf::Color::Yellow);
  _window->draw(_text);
}

void	Sfml::displayMenu(t_arcade *menu, int pos)
{
  int	       hScore = 0;
  int		i;

  _window->clear();
  setText("Arcade", 6 * _size, 1 * _size, 0);
  pos == 0 ? setText("Libraries", 1 * _size, 2 * _size, 1) :
    setText("Libraries", 1 * _size, 2 * _size, 0);;
  pos == 1 ? setText("Games", 4 * _size, 2 * _size, 1) :
    setText("Games", 4 * _size, 2 * _size, 0);
  pos == 2 ? setText("Username", 7 * _size, 2 * _size, 1) :
    setText("Username", 7 * _size, 2 * _size, 0);
  setText("Highscore", 10 * _size, 2 * _size, 0);
  pos == 3 ? setText("Go", 13 * _size, 2 * _size, 1) :
    setText("Go", 13 * _size, 2 * _size, 0);

  setText(menu->user, 7 * _size, 3 * _size, 0);
  //Libraries
  i = 3;
  for (std::vector<info_lib>::iterator node = menu->libs.begin(); node != menu->libs.end(); ++node)
    {
      if (menu->pos_graph == i - 3)
	setText((*node).name, 1 * _size, i * _size, 1);
      else
	setText((*node).name, 1 * _size, i * _size, 0);
      i++;
    }
  //Games
  i = 3;
  for (std::vector<info_lib>::iterator node = menu->games.begin(); node != menu->games.end(); ++node)
    {
      if (menu->pos_game == i - 3)
	{
	  setText((*node).name, 4 * _size, i * _size, 1);
	  hScore = (*node).hscore;
	  setText(std::to_string(hScore), 10 * _size, 3 * _size, 0);
	}
      else
	setText((*node).name, 4 * _size, i * _size, 0);
      i++;
    }
  _window->display();
}

int		Sfml::startMenu(t_arcade *menu)
{
  int		i = 0;
  sf::Event	event;


  _window = new sf::RenderWindow(sf::VideoMode(15 * _size, 10 * _size), "MENU", sf::Style::Default);
  if (!_window || !_font.loadFromFile("./textures/Roboto.ttf"))
    return (-1);
  _window->setFramerateLimit(10);
  _window->setKeyRepeatEnabled(false);
  _text.setFont(_font);
  menu->pos_graph = 0;
  menu->pos_game = -1;
  while (i < 4)
    {
      while (_window->pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    return (-1);
	  else if (event.type == sf::Event::Resized)
	    _window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	return (-1);

      if (i < 2)
	menu->user = "";
      if (i > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	  if (i == 1)
	    menu->pos_game = -1;
	  i--;
	}
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
	       sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	  if (i == 0)
	    {
	      menu->pos_game = menu->pos_graph;
	      if (menu->pos_game >= menu->games.size())
		menu->pos_game = menu->games.size() - 1;
	    }
	  i++;
	}
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
	  if (i == 0)
	    {
	      if (menu->pos_graph > 0)
		menu->pos_graph--;
	    }
	  else if (i == 1)
	    if (menu->pos_game > 0)
	      menu->pos_game--;
	}
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	  if (i == 0)
	    {
	      if (menu->pos_graph < menu->libs.size() - 1)
		menu->pos_graph++;
	    }
	  else if (i == 1)
	    if (menu->pos_game < menu->games.size() - 1)
	      menu->pos_game++;
	}

      if (i == 2 && menu->user.length() < 12)
	{
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	    menu->user.append("a");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	    menu->user.append("b");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	    menu->user.append("c");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	    menu->user.append("d");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	    menu->user.append("e");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	    menu->user.append("f");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	    menu->user.append("g");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	    menu->user.append("h");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	    menu->user.append("i");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	    menu->user.append("j");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	    menu->user.append("k");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	    menu->user.append("l");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	    menu->user.append("m");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	    menu->user.append("n");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	    menu->user.append("o");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	    menu->user.append("p");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	    menu->user.append("q");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	    menu->user.append("r");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	    menu->user.append("s");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	    menu->user.append("t");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	    menu->user.append("u");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	    menu->user.append("v");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	    menu->user.append("w");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	    menu->user.append("x");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	    menu->user.append("y");
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	    menu->user.append(" ");
	}
      if (i == 2 && menu->user.size() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	menu->user.erase(menu->user.size() - 1);
      displayMenu(menu, i);
    }
  _window->close();
  _window = NULL;
}

extern "C"
class Sfml	*create_graph()
{
  return new Sfml();
}
