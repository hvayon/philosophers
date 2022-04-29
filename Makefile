NAME	=	philo
HEAD	=	philo.h
CC		=	cc
CFLAGS	=	#-Wall -Werror -Wextra
SRC		=	philo.c philo_utils.c
OBJ		=	$(SRC:%.c=%.o)
D_FILES =	$(SRC:%.c=%.d)
RM		=	rm -f
all: $(NAME)
$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
%.o:	%.c
		$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include $(wildcard $(D_FILES))

clean:
	@$(RM) $(OBJ) $(D_FILES)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
