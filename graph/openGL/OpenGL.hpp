//
// OpenGL.hpp for opengl in /home/nicolas/arcade/opengl
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Wed Mar 15 14:51:40 2017 Nicolas Guillon
// Last update Tue Apr  4 16:26:57 2017 Nicolas Guillon
//

#ifndef OPENGL_HPP_
#define OPENGL_HPP_

#include "../IGraph.hpp"
#include "../../my.hpp"

class OpenGL : public IGraph
{
private:
  GLuint texture1;
  GLuint texture2;
  GLuint texture3;
  GLuint textureItem;
  GLuint textureUnder;
  GLuint textureSItem;
  GLuint textureChara;
  GLuint textureCharaBody;
  GLuint textureFont;
  GLuint texturePick;
  GLuint textureDigit;
  GLuint textureGrey;

  Uint32 last_time;
  Uint32 current_time;
  Uint32 ellapsed_time;
  Uint32 start_time;
  Uint32 stop_time;
  Uint32 time_per_frame;

public:
  OpenGL();
  virtual ~OpenGL();

  virtual const std::string     getName() const;
  // Window handler
  virtual void  startWindow(int width, int height, std::string name);
  virtual void  closeWindow();
  virtual void  displayMap(map *map);
  virtual int	startMenu(t_arcade *arcade);

  // Events handler
  virtual event getEvent();

  void	drawFont(char c);
  void	drawDigit(char c);
  void	drawUnder(double x, double y, double z, int len);
  void	drawString(double x, double y, double z, const char *str);
  void	drawGreyZone(double x, double y, double z);
  void	drawHScore(double x, double y, double z, int score);
  void	drawPick(double x, double y, double z);
  void	drawMenu(t_arcade *core, int pos, int choice, std::string muser);
  void	drawChara();
  void	setPlayer(character player);
  void	setCharacter(character chara, int type);
  void	drawSphere();
  void	drawItem();
  void	drawSItem();
  void	drawCase();
  void	drawGround(map *map);
  void	displayChar(map *map);
  void	DrawGL(map *map);
};

#endif
