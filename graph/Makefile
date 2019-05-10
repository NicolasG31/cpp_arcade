all:
		make -C ./sfml/.
		make -C ./openGL/.
		make -C ./ncurses/.

clean:
		make clean -C ./sfml/.
		make clean -C ./openGL/.
		make clean -C ./ncurses/.

fclean:
		make fclean -C ./sfml/.
		make fclean -C ./openGL/.
		make fclean -C ./ncurses/.

re: 		fclean all

.PHONY: 	all clean fclean re
