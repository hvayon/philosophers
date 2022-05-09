NAME	=	philo_bonus
HEAD	=	philo_bonus.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MMD
SRC		=	philo_bonus.c main_bonus.c philo_utils_bonus.c \
			philo_life_bonus.c
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