//
// OpenGL.cpp for opengl in /home/nicolas/arcade/opengl
// 
// Made by Nicolas Guillon
// Login   <nicolas@epitech.net>
// 
// Started on  Wed Mar 15 15:41:05 2017 Nicolas Guillon
// Last update Sun Apr  9 19:10:29 2017 Nicolas Guillon
//

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cmath>

#include "OpenGL.hpp"
#include "sdlglutils.h"

#define ZOOM 40

OpenGL::OpenGL()
{
  time_per_frame = 1000 / 12;
}

OpenGL::~OpenGL()
{
}

void	OpenGL::drawFont(char c)
{
  if (c >= 65 && c <= 90)
    c -= 64;
  else
    c -= 96;
  glBindTexture(GL_TEXTURE_2D, textureFont);
  glBegin(GL_QUADS);
  glTexCoord2d(c * (1.0 / 26) - 1.0 / 26,1);
  glVertex3d(1,1,1);
  glTexCoord2d(c* (1.0 / 26) - 1.0 / 26,0);
  glVertex3d(1,1,-1);
  glTexCoord2d(c * (1.0 / 26),0);
  glVertex3d(-1,1,-1);
  glTexCoord2d(c * (1.0 / 26),1);
  glVertex3d(-1,1,1);
  glEnd();
}

void	OpenGL::drawDigit(char c)
{
  c -= 47;
  glBindTexture(GL_TEXTURE_2D, textureDigit);
  glBegin(GL_QUADS);
  glTexCoord2d(c * (1.0 / 10) - 1.0 / 10,1);
  glVertex3d(1,1,1);
  glTexCoord2d(c* (1.0 / 10) - 1.0 / 10,0);
  glVertex3d(1,1,-1);
  glTexCoord2d(c * (1.0 / 10),0);
  glVertex3d(-1,1,-1);
  glTexCoord2d(c * (1.0 / 10),1);
  glVertex3d(-1,1,1);
  glEnd();
}

void	OpenGL::drawUnder(double x, double y, double z, int len)
{
  int	i = 0;

  glPushMatrix();
  glTranslated(x, y, z);
  while (i != len)
    {
      glBindTexture(GL_TEXTURE_2D, textureUnder);
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(0.15,0.15,0.15);
      glTexCoord2d(0,0);
      glVertex3d(0.15,0.15,-0.15);
      glTexCoord2d(1,0);
      glVertex3d(-0.15,0.15,-0.15);
      glTexCoord2d(1,1);
      glVertex3d(-0.15,0.15,0.15);
      glEnd();

      glTranslated(-0.3, 0, 0);
      i++;
    }
  glPopMatrix();
}

void	OpenGL::drawString(double x, double y, double z, const char *str)
{
  int	i = 0;

  glPushMatrix();
  glTranslated(x, y, z);
  while (str[i])
    {
      drawFont(str[i]);
      glTranslated(-2, 0, 0);
      i++;
    }
  glPopMatrix();
}

void	OpenGL::drawGreyZone(double x, double y, double z)
{
  glPushMatrix();
  glTranslated(x, y, z);

  glBindTexture(GL_TEXTURE_2D, textureGrey);
  glBegin(GL_QUADS);
  glVertex3d(0.5,0.5,1);
  glVertex3d(0.5,0.5,-1);
  glVertex3d(-0.5,0.5,-1);
  glVertex3d(-0.5,0.5,1);
  glTranslated(-5, 0, 0);
  glEnd();
  glPopMatrix();
}

void	OpenGL::drawHScore(double x, double y, double z, int score)
{
  std::string str = std::to_string(score);
  const char *cstr = str.c_str();
  int i = 0;

  glPushMatrix();
  glTranslated(x, y, z);
  while (cstr[i])
    {
      drawDigit(cstr[i]);
      glTranslated(-2, 0, 0);
      i++;
    }
  glPopMatrix();
}

void	OpenGL::drawPick(double x, double y, double z)
{
  glPushMatrix();
  glTranslated(x, y, z);

  glBindTexture(GL_TEXTURE_2D, texturePick);
  glBegin(GL_QUADS);
  glTexCoord2d(0,1);
  glVertex3d(2,2,2);
  glTexCoord2d(0,0);
  glVertex3d(2,2,-2);
  glTexCoord2d(1,0);
  glVertex3d(-2,2,-2);
  glTexCoord2d(1,1);
  glVertex3d(-2,2,2);

  glEnd();
  glPopMatrix();
}

void	OpenGL::drawMenu(t_arcade *core, int pos, int choice, std::string muser)
{
  drawString(7, -20, 27, "arcade");
  drawString(48, -30, 23, "libraires");
  drawUnder(50, -30, 21.5, 60);
  drawString(20, -30, 23, "jeux");
  drawUnder(21, -30, 21.5, 25);
  drawString(-2, -30, 23, "pseudo");
  drawUnder(-1, -30, 21.5, 40);
  drawString(-38, -30, 23, "highscore");
  drawUnder(-38, -30, 21.5, 60);

  if (choice == 0)
    drawPick(52, -30, 23 - ((pos + 1) * 10));
  else if (choice == 1)
    drawPick(24, -30, 23 - ((pos + 1) * 10));
  else if (choice == 2)
    drawGreyZone(1, -30, 13.25);

  if (muser != "return")
    drawString(-1, -30, 13, muser.c_str());

  for (std::vector<info_lib>::iterator node = core->libs.begin(); node != core->libs.end(); node++)
    {
      drawString(48, -30, 23 - (((*node).pos + 1) * 10), (*node).name.c_str());
      if (choice > 0 && ((*node).pos == core->pos_graph))
	drawGreyZone(51, -30, 23.25 - (((*node).pos + 1) * 10));
    }

  for (std::vector<info_lib>::iterator node = core->games.begin(); node != core->games.end(); node++)
    {
      drawString(20, -30, 23 - (((*node).pos + 1) * 10), (*node).name.c_str());
      drawHScore(-38, -30, 23 - (((*node).pos + 1) * 10), (*node).hscore);
      drawString(-38, -30, 20 - (((*node).pos + 1) * 10), (*node).hscore_name.c_str());
      if (choice > 1 && ((*node).pos == core->pos_game))
	drawGreyZone(23, -30, 23.25 - (((*node).pos + 1) * 10));
    }
}

int	OpenGL::startMenu(t_arcade *core)
{
  std::string muser = "";
  std::string tmp;
  SDL_Surface *ecran;
  SDL_Event event;
  int pos = 0;
  int choice = 0;

  int nbGames = core->games.size();
  int nbGraph = core->libs.size();

  SDL_Init(SDL_INIT_VIDEO);

  SDL_WM_SetCaption("Arcade", NULL);
  ecran = SDL_SetVideoMode(1300, 900, 32, SDL_OPENGL);// | SDL_FULLSCREEN);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90,(double)1300/900,1,1000);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  textureUnder = loadTexture("textures/openGL/under.jpg");
  textureFont = loadTexture("textures/openGL/font.png");
  texturePick = loadTexture("textures/openGL/pick.png");
  textureDigit = loadTexture("textures/openGL/digit.png");
  textureGrey = loadTexture("textures/openGL/grey.jpg");

  while (SDL_WaitEvent(&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  exit(0);
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      exit(-1);
	      break;

		// UP BUTTON
	    case SDLK_UP:
	      if ((pos == 0 && choice == 0) ||
		  (pos == 0 && choice == 1))
		pos = nbGraph - 1;
	      else
		pos -= 1;
		break;

		// DOWN BUTTON
	    case SDLK_DOWN:
	      if ((choice == 0 && pos == nbGraph - 1) ||
		  (choice == 1 && pos == nbGames - 1))
		pos = 0;
	      else
		  pos += 1;
	      break;

	      // RIGHT BUTTON
	    case SDLK_RIGHT:
	      if (choice == 0)
		{
		  core->pos_graph = pos;
		  choice++;
		  pos = 0;
		}
	      else if (choice == 1)
		{
		  core->pos_game = pos;
		  choice++;
		  pos = 0;
		}
	      else if (choice == 2)
		{
		  core->user = muser;
		  closeWindow();
		  return (0);
		}
	      break;

	      // LEFT BUTTON
	    case SDLK_LEFT:
	      if (choice == 1)
		{
		  pos = core->pos_graph;
		  core->pos_graph = 0;
		  choice--;
		}
	      else if (choice == 2)
		{
		  muser = "";
		  pos = core->pos_game;
		  core->pos_game = 0;
		  choice--;
		}
	      break;


	      // ENTER BUTTON
	    case SDLK_RETURN:
	      if (choice == 0)
		{
		  core->pos_graph = pos;
		  choice++;
		  pos = 0;
		}
	      else if (choice == 1)
		{
		  core->pos_game = pos;
		  choice++;
		  pos = 0;
		}
	      else if (choice == 2)
		{
		  core->user = muser;
		  closeWindow();
		  return (0);
		}

	      // BACKSPACE
	    case SDLK_BACKSPACE:
	      if (muser.size() > 0)
		muser.pop_back();

	      // AUTRE TOUCHE
	    default:
	      if (choice == 2)
		{
		  tmp = SDL_GetKeyName(event.key.keysym.sym);
		  if (tmp.size() > 1)
		    break;
		  if (muser.size() < 15)
		    muser += SDL_GetKeyName(event.key.keysym.sym);
		}
	      break;
	    }
	  break;
	}
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 15, 0, 0, 0, 0, 0, 0, 1);
      drawMenu(core, pos, choice, muser);
      glFlush();
      SDL_GL_SwapBuffers();
    }
}

void	OpenGL::drawChara()
{
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, textureCharaBody);
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(1,1,1);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(1,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(1,1);
      glVertex3d(-1,1,1);
      glEnd();
      glRotated(90,0,0,1);
    }
  glBindTexture(GL_TEXTURE_2D, textureChara);
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3d(1,-1,1);
  glTexCoord2d(1,0);
  glVertex3d(1,1,1);
  glTexCoord2d(1,1);
  glVertex3d(-1,1,1);
  glTexCoord2d(0,1);
  glVertex3d(-1,-1,1);

  glEnd();
  glPopMatrix();
}

void		OpenGL::setPlayer(character player)
{
  glPushMatrix();
  glTranslatef((-player.xf * 2) - 2, player.yf * 2, 0);
  drawSphere();
  glPopMatrix();
}

void		OpenGL::setCharacter(character chara, int type)
{
  if (type == 0)
    {
      textureChara = loadTexture("textures/openGL/gred.png");
      textureCharaBody = loadTexture("textures/openGL/gredbody.png");
    }
  else if (type == 1)
    {
      textureChara = loadTexture("textures/openGL/gblue.png");
      textureCharaBody = loadTexture("textures/openGL/gbluebody.png");
    }
  else if (type == 2)
    {
      textureChara = loadTexture("textures/openGL/gpink.png");
      textureCharaBody = loadTexture("textures/openGL/gpinkbody.png");
    }
  else if (type == 3)
    {
      textureChara = loadTexture("textures/openGL/gyellow.png");
      textureCharaBody = loadTexture("textures/openGL/gyellowbody.png");
    }
  else if (type == 4)
    {
      textureChara = loadTexture("textures/openGL/gbonus.png");
      textureCharaBody = loadTexture("textures/openGL/gbonusbody.png");
    }
  glPushMatrix();
  glTranslatef((-chara.xf * 2) - 2, chara.yf * 2, 0);
  drawChara();
  glPopMatrix();
}

const std::string	OpenGL::getName() const
{
  return (std::string("OpenGL"));
}

event	OpenGL::getEvent()
{
  SDL_Event event;

  if (SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  return (ESCAPE);
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      return (ESCAPE);
	      break;
	    case SDLK_UP:
	      return (UP);
	      break;
	    case SDLK_DOWN:
	      return (DOWN);
	      break;
	    case SDLK_RIGHT:
	      return (RIGHT);
	      break;
	    case SDLK_LEFT:
	      return (LEFT);
	      break;
	    case SDLK_a:
	      return (PREV_LIB);
	      break;
	    case SDLK_z:
	      return (NEXT_LIB);
	      break;
	    case SDLK_q:
	      return (PREV_GAME);
	      break;
	    case SDLK_s:
	      return (NEXT_LIB);
	      break;
	    case SDLK_r:
	      return (RESTART);
	      break;
	    case SDLK_m:
	      return (MENU);
	      break;
	    case SDLK_p:
	      return (PAUSE);
	      break;
	    }
	}
    }
  return (ILLEGAL);
}

void	OpenGL::closeWindow()
{
  SDL_Quit();
}

void	OpenGL::startWindow(int width, int height, std::string name)
{
  SDL_Surface *ecran;
  const char *cname = name.c_str();

  SDL_Init(SDL_INIT_VIDEO);

  SDL_WM_SetCaption(cname, NULL);
  ecran = SDL_SetVideoMode(1800, 1000, 32, SDL_OPENGL);// | SDL_FULLSCREEN);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75,(double)width/height,1,1000);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  texture1 = loadTexture("textures/openGL/caisse.jpg");
  texture2 = loadTexture("textures/openGL/tiles_ctf05r.jpg");
  texture3 = loadTexture("textures/openGL/ball_texture.jpg");
  textureItem = loadTexture("textures/openGL/coin.jpg");
  textureSItem = loadTexture("textures/openGL/scoin.jpg");

  last_time = SDL_GetTicks();
}

void    OpenGL::drawSphere()
{
  glBindTexture(GL_TEXTURE_2D,texture3);

  GLUquadric* params = gluNewQuadric();

  glPushMatrix();
  gluQuadricDrawStyle(params,GLU_FILL);
  gluQuadricTexture(params,GL_TRUE);
  gluSphere(params,1,20,20);

  gluDeleteQuadric(params);
  glPopMatrix();
}

void    OpenGL::drawItem()
{
  glBindTexture(GL_TEXTURE_2D,textureItem);

  GLUquadric* params = gluNewQuadric();

  glPushMatrix();
  gluQuadricDrawStyle(params,GLU_FILL);
  gluQuadricTexture(params,GL_TRUE);
  gluSphere(params,0.25,10,10);

  gluDeleteQuadric(params);
  glPopMatrix();
}

void    OpenGL::drawSItem()
{
  glBindTexture(GL_TEXTURE_2D,textureSItem);

  GLUquadric* params = gluNewQuadric();

  glPushMatrix();
  gluQuadricDrawStyle(params,GLU_FILL);
  gluQuadricTexture(params,GL_TRUE);
  gluSphere(params,0.40,10,10);

  gluDeleteQuadric(params);
  glPopMatrix();
}

void	OpenGL::drawCase()
{
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture1);
  // même face 4 fois avec une rotation
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(1,1,1);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(1,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(1,1);
      glVertex3d(-1,1,1);
      glEnd();
      glRotated(90,0,0,1);
    }
  //puis le dessus (pas besoin du dessous grâce au sol)
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3d(1,-1,1);
  glTexCoord2d(1,0);
  glVertex3d(1,1,1);
  glTexCoord2d(1,1);
  glVertex3d(-1,1,1);
  glTexCoord2d(0,1);
  glVertex3d(-1,-1,1);

  glEnd();
  glPopMatrix();
}

void	OpenGL::drawGround(map *map)
{
  glBindTexture(GL_TEXTURE_2D, texture2);
  glBegin(GL_QUADS);
  glColor3ub(193,150,150);
  glTexCoord2i(0,0);
  glVertex3i(-map->width,-map->height,-1);
  glColor3ub(240,230,230);
  glTexCoord2i(10,0);
  glVertex3i(map->width,-map->height,-1);
  glColor3ub(170,160,156);
  glTexCoord2i(10,10);
  glVertex3i(map->width,map->height,-1);

  glTexCoord2i(0,10);
  glVertex3i(-map->width,map->height,-1);
  glEnd();

  glColor3ub(255,255,255);
}

void		OpenGL::displayChar(map *map)
{
  int           i = 0;
  character     player;

  for (std::vector<character>::iterator node = map->player.begin(); node != map->player.end()
; ++node)
    {
      if ((*node).type == PLAYER)
        {
          player = (*node);
          setPlayer((*node));
        }
      else
       	{
	  if (player.hasBonus > 0)
	    setCharacter((*node), 4);
	  else
	    setCharacter((*node), i - 1);
	}
      i++;
    }
}

void	OpenGL::DrawGL(map *map)
{
  int	i = 0;
  int	j;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 3, ZOOM, 0, 0, 0, 0, 0, 1);

  drawGround(map);
  glTranslated(-map->width, -map->height, 0);

  while (i != map->height)
    {
      j = map->width - 1;
      while (j >= 0)
	{
	  if (map->map[i][j] == BLOCK)
	    drawCase();
	  else if (map->map[i][j] == PLAYER)
	    drawSphere();
	  else if (map->map[i][j] == ITEM)
	    drawItem();
	  else if (map->map[i][j] == S_ITEM)
	    drawSItem();
	  glTranslated(2, 0, 0);
	  j--;
	}
      glTranslated(((map->width) * -2), 2, 0);
      i++;
    }

  glTranslated(map->width * 2, -map->height * 2, 0);
  displayChar(map);

  glFlush();
  SDL_GL_SwapBuffers();
}

void	OpenGL::displayMap(map *map)
{
  current_time = SDL_GetTicks();
  ellapsed_time = current_time - last_time;
  last_time = current_time;

  DrawGL(map);

  stop_time = SDL_GetTicks();
  if ((stop_time - last_time) < time_per_frame)
    {
      SDL_Delay(time_per_frame - (stop_time - last_time));
    }
}

extern "C"
class OpenGL	*create_graph()
{
  return new OpenGL();
}
