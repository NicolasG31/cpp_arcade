##
## Makefile for OpenGL in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/graph/openGL
## 
## Made by Jerome Dang
## Login   <dang_j@epitech.net>
## 
## Started on  Wed Mar 29 18:53:13 2017 Jerome Dang
## Last update Tue Apr  4 13:36:23 2017 Guillaume
##

NAME		= 	lib_arcade_pacman.so

CC		= 	g++

RM		= 	rm -f

SRCS		= 	./Pacman.cpp \
			./Pacman_mouli.cpp \
			../my_read.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS        +=      -fPIC \
                        -std=c++11

LDFLAGS         =       -shared

all:                    $(NAME)

$(NAME):		$(OBJS)
			$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
			cp $(NAME) ..

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
