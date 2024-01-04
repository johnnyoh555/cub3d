CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRC			= all_directions color_identifier info \
			main make_map map_size utils check_valid_map\
			cub3d_init mouse camera keyboard move rendering\
			raycast minimap door door_motion sprite moon_name moon
SRCS		= $(addsuffix .c, $(addprefix ./src/, $(SRC)))
SRCS_B		= $(addsuffix _bonus.c, $(addprefix ./bonus/, $(SRC)))
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
NAME		= cub3D
NAME_B		= cub3D_bonus
LIBFT_DIR 	= libft
LIBFT 		= libft.a

all			: $(NAME)

$(NAME)		: $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lmlx -framework Appkit -framework OpenGL -lft -L./$(LIBFT_DIR)

bonus		: $(NAME_B)

$(NAME_B)	: $(OBJS_B)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME_B) $^ -lmlx -framework Appkit -framework OpenGL -lft -L./$(LIBFT_DIR)

$(OBJS)		: %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_B)	: %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(OBJS_B)

fclean		: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_B)

re			: 
	make fclean
	make all

.PHONY		: all clean fclean re bonus