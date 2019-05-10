##
## Makefile for arcade in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade
## 
## Made by Jerome Dang
## Login   <dang_j@epitech.net>
## 
## Started on  Wed Mar 29 20:05:41 2017 Jerome Dang
## Last update Sun Apr  9 09:10:57 2017 Guillaume Doremieux
##

NAME	= 	arcade

CC	= 	g++

RM	= 	rm -f

SRCS	= 	./main.cpp \
		./init_menu.cpp \
		./my_open.cpp \
		./my_dl.cpp \

CPPFLAGS = -std=c++11

OBJS	= 	$(SRCS:.cpp=.o)

all: 		$(NAME)

$(NAME):
		make -C ./games

graph:		$(NAME)  $(OBJS)
	 	$(CC) $(OBJS) -lSDL -lSDL_image -lGL -lGLU -ldl -o $(NAME)
		make -C ./graph


clean:
		$(RM) $(OBJS)
		make clean -C ./graph
		make clean -C ./games


fclean: 	clean
		$(RM) $(NAME)
		make fclean -C ./graph
		make fclean -C ./games

re: 		fclean all

.PHONY: 	all clean fclean re
