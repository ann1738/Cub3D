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

SRC = cub3d.c get_next_line.c drawing.c minimap.c \
    hooks.c rotation.c line.c ray_cast.c floor.c ceiling.c redraw.c \
	initiate.c math_utils.c time.c check_user_input.c full_map_save.c \
	rgb_to_hex.c map_checks.c pars_utils.c texture.c color.c jump_n_look.c animation.c
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: $(NAME)

-include $(addprefix dep/,$(DEP))

$(NAME): obj dep $(addprefix obj/,$(OBJ)) $(LIBFT_STATIC_LIB) $(MLX_STATIC_LIB)
	@printf "\033[1;33mLinking..\n\033[2;33m"
	$(CC) $(addprefix obj/,$(OBJ)) $(LINK_MLX) $(LINK_LIBFT) -o $(NAME)
	@printf "\x1B[0m\033[1;33mCompilation and Linking Done!!\e[0m\n"

obj/%.o: src/%.c
# ifneq ("$(wildcard $(./obj))","")
# 	@printf "\e[92mCompiling cub3d's $@ ..\n\e[94m"
# else
# 	@printf "\033[2;34m"
# endif
	@printf "\033[2;34m"
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
# @printf "\e[92mCleaning..\e[0m\n"
	@make -sC $(LIBFT_LIB) fclean
	@make -sC $(MLX_LIB) clean
	@rm -f $(NAME)

re: fclean all
