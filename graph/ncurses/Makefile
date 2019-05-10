##
## Makefile for Ncurses in /home/linh/rendu/cpp/arcade/arcade/cpp_arcade/graph/ncurses
## 
## Made by Jerome Dang
## Login   <dang_j@epitech.net>
## 
## Started on  Wed Mar 29 19:07:54 2017 Jerome Dang
## Last update Wed Mar 29 19:13:51 2017 Jerome Dang
##

NAME		= 	lib_arcade_ncurses.so

CC		= 	g++

RM		= 	rm -f

SRCS		= 	./my_ncurses.cpp \
	  		./Ncurses.cpp

OBJS            =       $(SRCS:.cpp=.o)

CPPFLAGS        +=      -fPIC \
                        -std=c++11

LDFLAGS         =       -shared

all:                    $(NAME)

$(NAME):		$(OBJS)
			$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) -lncurses
			cp $(NAME) ..

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)


re: fclean all

.PHONY: all clean re
