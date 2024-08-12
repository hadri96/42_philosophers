NAME = 			philo

INCLUDES =		includes

SRCS = 			srcs/philo_utils.c \
				srcs/display_utils.c \
				srcs/philo_safe_utils.c \
				srcs/philo_init.c \
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

LIBFT =			libft
LIBFT_LIB =		$(LIBFT)/libft.a

SANITIZE= -g3 -fsanitize=address
#SANITIZE= -g

all:	$(NAME)

$(NAME):	$(SRCS)
	@make -C $(LIBFT) all
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB) $(SANITIZE)
	@echo "$(GR) ✅ Compilation done! ✅$(RST)"

clean:
	rm -rf objs
	@echo "$(R) 🗑️ Object files deleted! 🗑️$(RST)"

fclean:		clean
	@make -C $(LIBFT) fclean
	@rm $(NAME)
	@echo "$(R) 🗑️ Executable deleted! 🗑️$(RST)"


re:			fclean all

.PHONY: all clean fclean re
