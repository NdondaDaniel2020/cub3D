# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:25:17 by aquissan          #+#    #+#              #
#    Updated: 2025/03/18 08:15:47 by aquissan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D
BNAME=cub3D_bonus

W ?= 1200
H ?= 800
S ?= 0.02
M ?= "Done"
GAMESET= -DSCREEN_WIDTH=$(W) -DSCREEN_HEIGHT=$(H) -DSPEED=$(S)
FLAGS= -Wall -Wextra -Werror  -g
COMPILE= cc

# DIRS
INC_D = includes
LIBFTPATH = libft
MLXPATH = minilibx-linux
SRC_D=sources
BSRC_D=bonus
OBJ_D=objects

RM=rm -rf 
Mk=mkdir -p 

FILES= main.c get_next_line.c get_next_line_utils.c check_map.c freeze.c gets.c\
		utils_check.c utils.c check_walls.c utils2.c render.c controls.c dda.c\
		extra.c draw.c
SRC=$(addprefix $(SRC_D)/, $(FILES))
OBJ=$(addprefix $(OBJ_D)/, $(FILES:.c=.o))



BFILES= check_map_bonus.c get_next_line_utils_bonus.c check_walls_bonus.c gets_bonus.c \
controls_bonus.c main_bonus.c dda_bonus.c render_bonus.c draw_bonus.c utils2_bonus.c \
extra_bonus.c utils_bonus.c freeze_bonus.c utils_check.c get_next_line_bonus.c
BSRC=$(addprefix $(BSRC_D)/, $(BFILES))
BOBJ=$(addprefix $(OBJ_D)/, $(BFILES:.c=.o))



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

$(OBJ_D)/%.o:$(BSRC_D)/%.c
	@$(Mk) $(OBJ_D)
	$(COMPILE) $(FLAGS) $(GAMESET) -c $< -o $@ 


clean: 
	make clean -C $(LIBFTPATH)
	make clean -C $(MLXPATH)
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)

fclean: clean
	make fclean -C $(LIBFTPATH)
	# make fclean -C $(MLXPATH)
	$(RM) $(NAME)
	$(RM) $(BNAME)

re: fclean all
brun: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make bonus
	clear
	./$(BNAME) "test.cub"

run: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make
	clear
	./$(NAME) "test.cub"

leak: MLX LIBFT
	$(RM) $(OBJ)
	$(RM) $(OBJ_D)
	$(RM) $(NAME)
	make
	clear
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) "test.cub"

push: fclean
	clear
	git status
	git add .
	git status
	git commit -m"$(M)"
	git push

norm:
	norminette $(LIBFTPATH) $(SRC_D) $(INC_D)

.PHONY: all re clean fclean

