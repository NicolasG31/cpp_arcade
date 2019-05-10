##
## Makefile for SFML in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/graph/sfml
## 
## Made by Jerome Dang
## Login   <dang_j@epitech.net>
## 
## Started on  Wed Mar 29 16:44:09 2017 Jerome Dang
## Last update Tue Apr  4 15:14:16 2017 Jerome Dang
##

NAME		= 	lib_arcade_sfml.so

CC		= 	g++

RM		= 	rm -f

SRCS		=	./Sfml.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-fPIC \
			-std=c++11

LDFLAGS		=	-shared

all: 			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system
			cp $(NAME) ..

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
