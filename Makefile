CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= ./src/all_directions.c ./src/color_identifier.c ./src/info.c \
./src/main.c ./src/make_map.c ./src/map_size.c ./src/utils.c ./src/check_valid_map.c\
./src/cub3d_init.c ./src/mouse.c ./src/camera.c ./src/keyboard.c ./src/move.c ./src/rendering.c\
./src/raycast.c ./src/minimap.c ./src/sprit_door.c ./src/door_motion.c
OBJS		= $(SRCS:.c=.o)
NAME		= cub3d
LIBFT_DIR 	= libft
LIBFT 		= libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lmlx -framework Appkit -framework OpenGL -lft -L./$(LIBFT_DIR)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re