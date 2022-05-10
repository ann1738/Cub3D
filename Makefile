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

SRC = cub3d.c get_next_line.c temp_parser.c drawing.c minimap.c check_user_input.c full_map_save.c rgb_to_hex.c map_checks.c pars_utils.c
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: $(NAME)

-include $(addprefix dep/,$(DEP))

$(NAME): obj dep $(addprefix obj/,$(OBJ)) $(LIBFT_STATIC_LIB) $(MLX_STATIC_LIB)
	@printf "\e[92mLinking..\n\e[95m"
	$(CC) $(addprefix obj/,$(OBJ)) $(LINK_MLX) $(LINK_LIBFT) -o $(NAME)
	@printf "\e[92mCompilation and Linking Done!\e[0m\n"

obj/%.o: src/%.c
	@printf "\e[92mCompiling cub3d..\n\e[94m"
	$(CC) $(CFLAGS) $< -o $@ -MMD -MP -MF $(@:obj/%.o=dep/%.d)

$(LIBFT_STATIC_LIB):
	@printf "\e[92mCompiling libft..\e[0m\n"
	@make -sC $(LIBFT_LIB)

$(MLX_STATIC_LIB): 
	@printf "\e[92mCompiling mlx..\e[0m\n"
	@make -sC $(MLX_LIB)

obj:
	mkdir obj

dep:
	mkdir dep

clean:
	@printf "\e[93mCleaning..\e[0m\n"
	@make -sC $(LIBFT_LIB) clean
	@make -sC $(MLX_LIB) clean
	@rm -rf $(addprefix obj/,$(OBJ)) $(addprefix dep/,$(DEP)) dep obj

fclean: clean
	@printf "\e[92mCleaning..\e[0m\n"
	@make -sC $(LIBFT_LIB) fclean
	@make -sC $(MLX_LIB) clean
	@rm -f $(NAME)

re: fclean all