NAME = 			libft.a

OBJECTDIR =		objs
HEADERDIR =		includes

SRCS =			$(shell	find . -name '*.c')
OBJS =			$(SRCS:.%.c=$(OBJECTDIR)%.o)

CC =			gcc
CFLAGS =		-Wall -Werror -Wextra

RM =			rm -rf
AR =			ar -rcs

ARRUTILSDIR =	arr_utils
GNLDIR =		get_next_line
ISDIR =			is
LINKEDLISTDIR =	linked_list
MEMORYDIR =		memory
PRINTFDIR =		printf
PUTDIR	 =		put
STRINGDIR =		string
GARBAGEDIR =	garbage
NUMBERDIR =		numbers
EXTRASDIR =		extras

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(OBJECTDIR)/%.o:	./%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -I $(HEADERDIR) -c $< -o $@

clean:
	@$(RM)	$(OBJECTDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
