# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:25:17 by aquissan          #+#    #+#              #
#    Updated: 2026/09/24 17:03:00 by nmatondo       ###   ########.fr          #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
BNAME       = cub3D_bonus

# Game Settings (overridable)
W          ?= 1200
H          ?= 800
S          ?= 0.05
PX         ?= 14
GAMESET     = -DSCREEN_WIDTH=$(W) -DSCREEN_HEIGHT=$(H) -DSPEED="$(S)" -DPIXEL_SIZE="$(PX)"

# Compiler & Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Wno-incompatible-pointer-types
RM          = rm -rf
MKDIR       = mkdir -p

# Directories
INC_DIR     = include
SRC_DIR     = src
BUILD_DIR   = build
LIBFT_DIR   = libs/libft
MLX_DIR     = libs/mlx
BASS_DIR    = libs/bass

INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
BINCLUDES   = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(BASS_DIR)

# Mandatory Sources
M_CORE      = main.c controls.c freeze.c extra.c utils.c utils2.c
M_PARSER    = check_map.c check_walls.c gets.c utils_check.c get_next_line.c get_next_line_utils.c
M_RAYCASTER = dda.c
M_RENDER    = render.c draw.c

M_SRCS      = $(addprefix $(SRC_DIR)/core/, $(M_CORE)) \
              $(addprefix $(SRC_DIR)/parser/, $(M_PARSER)) \
              $(addprefix $(SRC_DIR)/raycaster/, $(M_RAYCASTER)) \
              $(addprefix $(SRC_DIR)/render/, $(M_RENDER))

M_OBJS      = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/mandatory/%.o, $(M_SRCS))

# Bonus Sources
B_CORE      = main_bonus.c init_data_bonus.c hooks_bonus.c controls_bonus.c key_exit_bounus.c \
              preload.c preload_init.c extra_bonus.c freeze_1_bonus.c freeze_2_bonus.c \
              utils_bonus.c utils2_bonus.c utils3_bonus.c
B_PARSER    = check_map_bonus.c check_walls_bonus.c gets_bonus.c utils_check_bonus.c \
              get_next_line_bonus.c get_next_line_utils_bonus.c
B_RAYCASTER = dda_bonus.c
B_RENDER    = render_bonus.c render_util_bonus.c draw_bonus.c draw_floor_and_ceil.c \
              draw_crosshair_bonus.c draw_straight_line_bonus.c draw_small_map_bonus.c \
              draw_small_map_util_bonus.c set_small_map_area_value_bouns.c
B_PLAYER    = draw_player_bonus.c mouse_event_bonus.c player_animation_bonus.c \
              load_player_texture_bonus.c player_texture_configuration_bonus.c \
              player_image_path_bonus.c player_image_path_util_bonus.c
B_BONUS     = sound_bonus.c door_bonus.c door_animation_bonus.c door_animation_util_bonus.c \
              door_image_path_bonus.c load_door_texture_bonus.c get_door_image_index_bonus.c \
              get_pos_door_bonus.c get_pos_door_util_1_bonus.c get_pos_door_util_2_bonus.c \
              render_door_bonus.c render_door_util_bonus.c

B_SRCS      = $(addprefix $(SRC_DIR)/core/, $(B_CORE)) \
              $(addprefix $(SRC_DIR)/parser/, $(B_PARSER)) \
              $(addprefix $(SRC_DIR)/raycaster/, $(B_RAYCASTER)) \
              $(addprefix $(SRC_DIR)/render/, $(B_RENDER)) \
              $(addprefix $(SRC_DIR)/player/, $(B_PLAYER)) \
              $(addprefix $(SRC_DIR)/bonus/, $(B_BONUS))

B_OBJS      = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/bonus/%.o, $(B_SRCS))

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(LIBFT) $(MLX) $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L$(BASS_DIR) -lbass -L$(MLX_DIR) -lXext -lX11 -lm -lz -Wl,-rpath,$(BASS_DIR) -o $(BNAME)

# Library Compilation Rules
$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -f $(MLX_DIR)/libmlx.a ]; then make -C $(MLX_DIR); fi

# Object Compilation
$(BUILD_DIR)/mandatory/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(GAMESET) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/bonus/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(GAMESET) $(BINCLUDES) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(BUILD_DIR)/mandatory $(BUILD_DIR)/bonus
	@echo "Cleaned build objects"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME) $(BNAME)
	@echo "Cleaned executables"

re: fclean all

rebonus: fclean bonus

run: all
	./$(NAME) assets/maps/test.cub

brun: bonus
	./$(BNAME) assets/maps/bridge.cub

.PHONY: all bonus clean fclean re rebonus run brun