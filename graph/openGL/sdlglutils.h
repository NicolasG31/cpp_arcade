/*
** sdlglutils.h for sdlutils in /home/nicolas/arcade/cpp_arcade/graph
** 
** Made by Nicolas Guillon
** Login   <nicolas@epitech.net>
** 
** Started on  Wed Mar 29 14:17:58 2017 Nicolas Guillon
** Last update Sun Apr  9 11:53:27 2017 Nicolas Guillon
*/

#ifndef SDLGLUTILS_H
#define SDLGLUTILS_H

#include <GL/gl.h>
#include <SDL/SDL.h>
#include "my_memcpy.hpp"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLuint loadTexture(const char * filename,bool useMipMap = true);
int takeScreenshot(const char * filename);
void drawAxis(double scale = 1);
int initFullScreen(unsigned int * width = NULL,unsigned int * height = NULL);
int XPMFromImage(const char * imagefile, const char * XPMfile);
SDL_Cursor * cursorFromXPM(const char * xpm[]);

#endif //SDLGLUTILS_H
