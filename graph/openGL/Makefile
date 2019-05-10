##
## Makefile for OpenGL in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/graph/openGL
## 
## Made by Jerome Dang
## Login   <dang_j@epitech.net>
## 
## Started on  Wed Mar 29 18:53:13 2017 Jerome Dang
## Last update Sun Apr  9 11:52:01 2017 Nicolas Guillon
##

NAME		= 	lib_arcade_opengl.so

CC		= 	g++

RM		= 	rm -f

SRCS		= 	./OpenGL.cpp \
			./my_memcpy.cpp \
	  		./sdlglutils.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS        +=      -fPIC \
                        -std=c++11 \

LDFLAGS         =       -lSDL \
			-lSDL_image \
			-lGL \
			-lGLU \
			-ldl \
			-shared \

all:                    $(NAME)

$(NAME):		$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
			cp $(NAME) ..

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
