NAME = 			philo

INCLUDES =		includes

SRCS = 			srcs/philo_utils.c \
				srcs/main.c

CC = 			gcc

RED =			\033[0;31m
GREEN =			\033[0;32m
YELLOW =		\033[0;33m
BLUE =			\033[0;34m
MAGENTA =		\033[0;35m
CYAN =			\033[0;36m
WHITE =			\033[0;37m
RESET =			\033[0m

CFLAGS = 		-Wall -Wextra -Werror -I $(INCLUDES)

LIBFT =			libft
LIBFT_LIB =		$(LIBFT)/libft.a

#SANITIZE= -g3 -fsanitize=address
SANITIZE= -g

all:	$(NAME)

$(NAME):	$(SRCS)
	@make -C $(LIBFT) all
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB) $(SANITIZE)
	@echo "$(GREEN) ✅ Compilation done! ✅$(RESET)"

clean:
	rm -rf objs
	@echo "$(RED) 🗑️ Object files deleted! 🗑️$(RESET)"

fclean:		clean
	@make -C $(LIBFT) fclean
	@rm $(NAME)
	@echo "$(RED) 🗑️ Executable deleted! 🗑️$(RESET)"


re:			fclean all

.PHONY: all clean fclean re
