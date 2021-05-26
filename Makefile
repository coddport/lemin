NAME	= lem_in

CC		= gcc
FLAG	= -Wall -Wextra -Werror

DIR_S	= sources
DIR_H	= includes
DIR_L	= libft

LIB		= $(addprefix $(DIR_L)/, libft.a)

SOURCES	= lem_in.c io_parse.c io_print.c bfs_dfs.c move_ants.c utils.c struct_del.c struct_init.c struct_modify.c 
SRCS	= $(addprefix $(DIR_S)/, $(SOURCES))
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(LIB):
	@- make -C $(DIR_L)

$(OBJS):	%.o: %.c
	@$(CC) -c $(FLAGS) -I $(DIR_H) $< -o $@

$(NAME):	$(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make -C $(DIR_L) clean

fclean: clean
	@rm -rf $(OBJS)
	@rm -f $(NAME)
	@make -C $(DIR_L) fclean

re:	fclean all

.PHONY:	all clean fclean re
