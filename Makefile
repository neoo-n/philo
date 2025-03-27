NAME	=	philo
SRCS	=	$(addprefix srcs/, main.c philo.c\
								ft_usleep.c utils.c error_clean.c)
OBJS	=	${SRCS:srcs/%.c=${OBJDIR}/%.o}
CC		=	gcc
CFLAGS	=	-Werror -Wextra -Wall -g -lpthread
OBJDIR	=	objets

# Colors and style
END		:= \033[0m
WHITE	:= \033[1;37m
NC		:= \033[0m
RED		:= \033[0;31m
PINK	:= \033[1;35m
GREEN	:= \033[0;32m
BOLD	:= \033[1m
L_PURPLE:= \033[38;5;55m
YELLOW	:= \033[0;33m
BLUE	:= \033[34m

 # Rules
all:	${NAME} header

header:
	@echo "$(L_PURPLE)"
	@echo ".------..------..------..------..------."
	@echo "|P.--. ||H.--. ||I.--. ||L.--. ||O.--. |"
	@echo "| :/\: || :/\: || (\/) || :/\: || :/\: |"
	@echo "| (__) || (__) || :\/: || (__) || :\/: |"
	@echo "| '--'P|| '--'H|| '--'I|| '--'L|| '--'O|"
	@echo "\`------'\`------'\`------'\`------'\`------'"
	@echo "$(END)"	

${NAME}:	${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJDIR}/%.o: srcs/%.c | ${OBJDIR}
	@${CC} ${CFLAGS} -c -o $@ $<

${OBJDIR}:
	@mkdir -p ${OBJDIR}

leaks: ${NAME}
	@valgrind --leak-check=full --log-file=leakslogs.txt --show-leak-kinds=all ./philo

clean:
	@rm -rf ${OBJDIR}

fclean: clean
	@rm -f ${NAME}

re: fclean all

party:
	@echo "$(BOLD)Let's party!"
	@echo "$(RED)  $(BOLD) (^-^) $(END) "
	@sleep 0.5
	@echo "$(L_PURPLE) $(BOLD) \(^-^\) $(END)"
	@sleep 0.5
	@echo "$(YELLOW) $(BOLD) (^-^) $(END)"
	@sleep 0.5
	@echo "$(BLUE) $(BOLD) (/^•^)/ $(END)"
	@sleep 0.5
	@echo "$(PINK) $(BOLD) (^-^) $(END)"
	@sleep 0.5
	@echo "$(GREEN) $(BOLD) \(^-^)/ $(END)"
	@sleep 0.5
	@echo "$(BOLD) Party time is over! Back to work! \n (^-^)7$(END)"

cat:
	@echo "    ⢀⠠⠤⠀⢀⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠐⠀⠐⠀⠀⢀⣾⣿⡇⠀⠀⠀⠀⠀⢀⣼⡇⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⠀⠀⠀⠀⣴⣿⣿⠇⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣇⠀⠀⢀⣾⣿⣿⣿⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠐⠀⡀"
	@echo "⠀⠀⠀⠀⢰⡿⠉⠀⡜⣿⣿⣿⡿⠿⢿⣿⣿⡃⠀⠀⠂⠄⠀"
	@echo "⠀⠀⠒⠒⠸⣿⣄⡘⣃⣿⣿⡟⢰⠃⠀⢹⣿⡇⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠚⠉⠀⠊⠻⣿⣿⣿⣿⣿⣮⣤⣤⣿⡟⠁⠘⠠⠁⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠠⠀⠀⠈⠙⠛⠛⠛⠛⠛⠁⠀⠒⠤⠀⠀⠀⠀"
	@echo "⠨⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠀⠀⠀⠀⠀⠀"
	@echo "⠁⠃⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"

.PHONY: all clean fclean re header