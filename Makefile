# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:25:17 by aquissan          #+#    #+#              #
#    Updated: 2025/04/11 20:41:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BNAME = cub3D_bonus

W ?= 1200
H ?= 800
S ?= 0.02
M ?= "Done"
PX ?= 18
# PX ?= $(shell echo "$(W) * 0.2 / 11" | bc)

GAMESET = -DSCREEN_WIDTH=$(W) -DSCREEN_HEIGHT=$(H) -DSPEED="$(S)" -DPIXEL_SIZE="$(PX)"
FLAGS = -Wall -Wextra -Werror -g
COMPILE = cc

# DIRS
INC_D = includes
LIBFTPATH = libft
MLXPATH = minilibx-linux
SRC_D=sources
BSRC_D=source_bonus
OBJ_D=objects
BOBJ_D=object_bonus

RM=rm -rf 
Mk=mkdir -p 
FILES= main.c get_next_line.c get_next_line_utils.c check_map.c freeze.c gets.c\
		utils_check.c utils.c check_walls.c utils2.c render.c controls.c dda.c\
		extra.c draw.c 
SRC=$(addprefix $(SRC_D)/, $(FILES))
OBJ=$(addprefix $(OBJ_D)/, $(FILES:.c=.o))

BFILES= check_map_bonus.c get_next_line_utils_bonus.c check_walls_bonus.c gets_bonus.c \
controls_bonus.c main_bonus.c dda_bonus.c render_bonus.c draw_bonus.c utils2_bonus.c \
extra_bonus.c utils_bonus.c freeze_1_bonus.c freeze_2_bonus.c utils_check.c get_next_line_bonus.c \
mouse_event_bonus.c set_small_map_area_value_bouns.c draw_straight_line_bonus.c \
draw_small_map_bonus.c hooks_bonus.c draw_player_bonus.c load_player_texture_bonus.c \
player_image_path_bonus.c player_image_path_util_bonus.c init_data_bonus.c draw_crosshair_bonus.c \
player_animation_bonus.c player_texture_configuration_bonus.c door_image_path_bonus.c \
load_door_texture_bonus.c key_exit_bounus.c door_bonus.c render_door_bonus.c render_util_bonus.c \
render_door_util_bonus.c
BSRC=$(addprefix $(BSRC_D)/, $(BFILES))
BOBJ=$(addprefix $(BOBJ_D)/, $(BFILES:.c=.o))

all: MLX LIBFT $(NAME)

MLX:
	make -C $(MLXPATH)
LIBFT:
	make -C $(LIBFTPATH)

$(NAME): $(OBJ)
	$(COMPILE) $(FLAGS)  -Iincludes -Imimilibx-linux $(OBJ) -L./$(MLXPATH) -lmlx -L./$(LIBFTPATH) -lft -I$(MLXPATH) -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_D)/%.o:$(SRC_D)/%.c
	@$(Mk) $(OBJ_D)
	$(COMPILE) $(FLAGS) $(GAMESET) -c $< -o $@ 


bonus: MLX LIBFT $(BNAME)

$(BNAME): $(BOBJ)
	$(COMPILE) $(FLAGS)  -Iincludes -Imimilibx-linux $(BOBJ) -L./$(MLXPATH) -lmlx -L./$(LIBFTPATH) -lft -I$(MLXPATH) -lXext -lX11 -lm -lz -o $(BNAME)

$(BOBJ_D)/%.o:$(BSRC_D)/%.c
	@$(Mk) $(BOBJ_D)
	$(COMPILE) $(FLAGS) $(GAMESET) -c $< -o $@ 


clean: 
	make clean -C $(LIBFTPATH)
	make clean -C $(MLXPATH)
	$(RM) $(OBJ)
	$(RM) $(BOBJ)
	$(RM) $(OBJ_D)
	$(RM) $(BOBJ_D)

fclean: clean
	make fclean -C $(LIBFTPATH)
	# make fclean -C $(MLXPATH)
	$(RM) $(NAME)
	$(RM) $(BNAME)

re: fclean all

run: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make
	clear
	./$(NAME) "test.cub"

brun: MLX LIBFT
	$(RM) $(BOBJ)
	$(RM) $(BOBJ_D)
	$(RM) $(BNAME)
	make bonus
	clear
	./$(BNAME) "test.cub"

leak: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(BNAME)
	make bonus
	clear
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(BNAME) "test.cub"

push: fclean
	clear
	git status
	git add .
	git status
	git commit -m"$(M)"
	git push

norm:
	norminette $(LIBFTPATH) $(SRC_D) $(BSRC_D) $(INC_D)

.PHONY: all re clean fclean

