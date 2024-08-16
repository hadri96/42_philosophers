NAME = 			philo

INCLUDES =		includes
MAKEFLAGS =		--no-print-directory

SRCS = 			srcs/philo_utils.c \
				srcs/display_utils.c \
				srcs/philo_safe_utils.c \
				srcs/philo_init.c \
				srcs/philo_sim_utils.c \
				srcs/philo_sim.c \
				srcs/time_utils.c \
				srcs/philo_str_utils.c \
				srcs/ft_atol.c \
				srcs/getters_setters.c \
				srcs/synchronization.c \
				srcs/parsing.c \
				srcs/main.c

CC = 			gcc

R =			\033[0;31m
GR =			\033[0;32m
Y =		\033[0;33m
BL =			\033[0;34m
MG =		\033[0;35m
CY =			\033[0;36m
WHITE =			\033[0;37m
RST =			\033[0m

CFLAGS = 		-Wall -Wextra -Werror -pthread -I $(INCLUDES)

#SANITIZE= -g3 -fsanitize=address
SANITIZE= -g -O0

all:	$(NAME)

$(NAME):	$(SRCS)
	@$(CC) $(CFLAGS) -o $@ $^ $(SANITIZE)
	@echo "$(GR) ✅ Compilation done! ✅$(RST)"

clean:
	@rm -rf objs
	@echo "$(R) 🗑️ Object files deleted! 🗑️$(RST)"

fclean:		clean
	@rm $(NAME)
	@echo "$(R) 🗑️ Executable deleted! 🗑️$(RST)"


re:			fclean all

.PHONY: all clean fclean re
