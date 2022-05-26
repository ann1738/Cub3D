NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra -c
LINK_LIBFT = -Llibft -lft
LIBFT_LIB = libft

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -Imlx
	LINK_MLX = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
	MLX_LIB = mlx_macos
else ifeq ($(shell uname -s), Linux)
	CFLAGS += -Imlx
	LINK_MLX = -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX_LIB = mlx_linux
endif

MLX_STATIC_LIB = $(MLX_LIB)/libmlx.a
LIBFT_STATIC_LIB = $(LIBFT_LIB)/libft.a

SRC = cub3d.c get_next_line.c drawing.c minimap.c collision.c\
    hooks.c line.c ray_cast.c redraw.c initiate.c \
	math_utils.c check_user_input.c full_map_save.c \
	check_map.c pars_utils.c texture.c color.c exit.c \
	toggle.c animation.c floor_n_celling.c minimap_utils.c \
	ray_cast_utils.c sprite_cast.c check_file_validity.c
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: $(NAME)

bonus: all

-include $(addprefix dep/,$(DEP))

$(NAME): obj dep $(addprefix obj/,$(OBJ)) $(LIBFT_STATIC_LIB) $(MLX_STATIC_LIB)
	@printf "\x1B[0m\033[1;33mLinking..\n\033[2;33m"
	$(CC) $(addprefix obj/,$(OBJ)) $(LINK_MLX) $(LINK_LIBFT) -o $(NAME)
	@printf "\x1B[0m\033[1;32mCompilation and Linking Done!!\e[0m\n"
	@printf "\n\033[1;31m+------+.   \033[1;33m   +------+   \033[1;32m    +------+  \033[1;34m     +------+  \033[1;35m    .+------+\n"
	@printf "\033[1;31m|\`.    | \`. \033[1;33m   |\     |\   \033[1;32m   |      |  \033[1;34m    /|     /|  \033[1;35m  .' |    .'|\n"
	@printf "\033[1;31m|  \`+--+---+  \033[1;33m | +----+-+  \033[1;32m   +------+   \033[1;34m  +-+----+ |  \033[1;35m +---+--+\'  |\n"
	@printf "\033[1;31m|   |  |   |   \033[1;33m| |    | |   \033[1;32m  |      |    \033[1;34m | |    | |  \033[1;35m |   |  |   |\n"
	@printf "\033[1;31m+---+--+.  |   \033[1;33m+-+----+ |   \033[1;32m  +------+    \033[1;34m | +----+-+  \033[1;35m |  .+--+---+\n"
	@printf "\033[1;31m \`. |    \`.| \033[1;33m   \|     \|  \033[1;32m   |      |  \033[1;34m   |/     |/  \033[1;35m  |.'    | .'\n"
	@printf "\033[1;31m   \`+------+  \033[1;33m   +------+   \033[1;32m  +------+   \033[1;34m  +------+   \033[1;35m  +------+'\n\n\x1B[0m"
	@printf "              ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n"
	@printf "             ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n"
	@printf "             ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n"
	@printf "             ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n"
	@printf "             ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n"
	@printf "              ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n\n"

obj/%.o: src/%.c
	@printf "\033[1;34m\033[2;34m"
	$(CC) $(CFLAGS) $< -o $@ -MMD -MP -MF $(@:obj/%.o=dep/%.d)

$(LIBFT_STATIC_LIB):
	@printf "\x1B[0m\033[1;34mCompiling libft..\e[0m\n"
	@make -sC $(LIBFT_LIB)

$(MLX_STATIC_LIB): 
	@printf "\033[1;34mCompiling mlx..\e[0m\n"
	@make -sC $(MLX_LIB)

obj:
	@mkdir obj

dep:
	@printf "\033[1;34mCompiling cub3d..\n\033[2;34m"
	@mkdir dep

clean:
	@printf "\033[1;32mCleaning..\e[0m\n"
	@make -sC $(LIBFT_LIB) clean
	@make -sC $(MLX_LIB) clean
	@rm -rf $(addprefix obj/,$(OBJ)) $(addprefix dep/,$(DEP)) obj dep

fclean: clean
	@make -sC $(LIBFT_LIB) fclean
	@make -sC $(MLX_LIB) clean
	@rm -f $(NAME)

re: fclean all
