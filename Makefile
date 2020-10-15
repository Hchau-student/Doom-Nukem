# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: f0rsunka <f0rsunka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 17:57:04 by cvernius          #+#    #+#              #
#    Updated: 2020/06/12 14:54:24 by f0rsunka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/zsh

PINK = \033[38;2;200;150;200m
BLUE = \033[38;2;200;200;250m
DEFAULT = "\033[0;0m"
GREEN = "\033[0;32m"
DEEP_BLUE = "\033[0;34m"

NAME = doom_nukem

SRC_DIR = ./src
ENGINE_DIR = ./src/engine
PARSE_DIR = ./src/parse
MENU_DIR = ./src/menu
MEMORY_DIR = ./src/memory_management
DRAW_3D_DIR = ./src/engine/draw_3d
LEV_EDITOR_DIR = ./src/level_editor

# SRC_3D_DIR = ./s

OBJ_DIR = ./obj

INCL_DIR = ./includes

C_FILES = main.c \
		  safe_call.c \
		  main_loop.c \
		  scale_image.c \
		  update_texture.c \
		  clear_keysum.c \
		  remove_alpha.c \
		  key_event.c \
		  mouse_event.c \
		  buttons_work.c

ENGINE_FILES = start_the_game.c \
               draw_hud.c \
               tools_weapon.c \
               draw_minimap.c \
               draw_minimap_tools.c \
               drawing_line.c \
               is_inside.c \
               condition.c

LEV_EDITOR_FILES = level_editor.c \
                   init_default_map.c \
                   condition.c \
                   draw_wall1.c \
                   init_level_editor.c

DRAW_3D_FILES = draw_3d_main.c \
                draw_3d_wall.c \
                wall_horizontal_clipping.c \
                draw_3d_walls_preparations.c \
                draw_portal.c \
                sort_walls.c

MENU_FILES = menu.c \
             load_game.c \
             condition.c

PARSE_FILES = parse.c \
              parse_wall.c \
              parse_sector_2.c \
              parse_sector_line_2.c \
              tools.c \
              parse_obj.c \
              parse_single_object.c \
              parse_single_wall.c \
              parse_player.c \
              parse_player_line.c \
              parse_hud.c \
              check_parsed_walls.c \
              check_parsed_objects.c \
              check_parsed_sectors.c \
              check_portal_data.c \
              safe_call.c \
              parse_struct.c

MEMORY_FILES = init_player.c \
              init_weapon.c \
              init_engine.c \
		      init_window.c \
		      init_data.c \
		      init_textures.c \
		      init_hud.c \
		      init_window_layer.c
# C_FILES_3D =

OBJ_FILES = $(C_FILES:.c=.o)
# OBJ_FILES_3D = $(C_FILES_3D:.c=.o)
OBJ_LEV_EDITOR = $(LEV_EDITOR_FILES:.c=.o)
OBJ_FILES_ENGINE = $(ENGINE_FILES:.c=.o)
OBJ_FILES_PARSE = $(PARSE_FILES:.c=.o)
OBJ_FILES_MENU = $(MENU_FILES:.c=.o)
OBJ_FILES_MEMORY = $(MEMORY_FILES:.c=.o)
OBJ_DRAW_3D = $(DRAW_3D_FILES:.c=.o)

RAW_OBJ_FILES = $(addprefix $(OBJ_DIR)/1_,$(OBJ_FILES))
# RAW_OBJ_FILES_3D = $(addprefix $(OBJ_DIR)/2_,$(OBJ_FILES_3D))
RAW_OBJ_FILES_ENGINE = $(addprefix $(OBJ_DIR)/3_,$(OBJ_FILES_ENGINE))
RAW_OBJ_FILES_PARSE = $(addprefix $(OBJ_DIR)/4_,$(OBJ_FILES_PARSE))
RAW_OBJ_FILES_MENU = $(addprefix $(OBJ_DIR)/5_,$(OBJ_FILES_MENU))
RAW_OBJ_FILES_MEMORY = $(addprefix $(OBJ_DIR)/6_,$(OBJ_FILES_MEMORY))
RAW_OBJ_FILES_DRAW_3D = $(addprefix $(OBJ_DIR)/7_,$(OBJ_DRAW_3D))
RAW_OBJ_LEV_EDITOR = $(addprefix $(OBJ_DIR)/8_,$(OBJ_LEV_EDITOR))

DEPS = $(RAW_OBJ_FILES:.o=.d)
# DEPS_PARSING = $(RAW_OBJ_FILES_3D:.o=.d)
# DEPS_PARSING = $(RAW_OBJ_FILES_3D:.o=.d)

SDL_DIR		=	./SDL
SDL_DIST	=	$(PWD)/SDL/dist
SDL_INCLUDE =	$(SDL_DIR)/dist/include/SDL2
SDL_LINK	=	`$(SDL_DIST)/bin/sdl2-config --cflags --libs`

LIBFT_FLAGS = -L ./libft -lft

detected_OS := $(shell uname)

ifeq ($(detected_OS),Linux)

	SDL_FLAGS := -lOpenCL

endif

ifeq ($(detected_OS),Darwin) 

	SDL_FLAGS = -framework OpenCL

endif

CFLAGS_ERRORS = -Wall -Wextra #-Werror
CFLAGS_DEPENDENCIES = -MMD -MP
CFLAGS_INCLUDES = -I $(INCL_DIR) -I $(SDL_INCLUDE) -I ./libft/include

CFLAGS_FINAL =	$(CFLAGS_INTERNAL) \
				$(CFLAGS_ERRORS) \
				$(CFLAGS_DEPENDENCIES) $(CFLAGS_INCLUDES) \
				$(CFLAGS)

LDFLAGS =	$(LIBFT_FLAGS) $(LIBVECTOR_FLAGS) -lm $(SDL_LINK)

.PHONY: all clean clean_libs clean_SDL clean_self fclean re

all:
	@echo "$(BLUE)" "Making libft" $(DEFAULT)
	@echo -n $(DEEP_BLUE)
	$(MAKE) -C ./libft
	@echo -n $(DEFAULT)

	@echo "$(BLUE)" "Start your engine! Making game" $(DEFAULT)
# 	@sh /Users/hchau/Desktop/hohow/priv.sh
	@echo -n $(GREEN)
	$(MAKE) $(NAME)
	@echo -n $(DEFAULT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): ./libft/libft.a $(SDL_DIST) $(RAW_OBJ_FILES) \
	$(RAW_OBJ_FILES_ENGINE) $(RAW_OBJ_FILES_PARSE) $(RAW_OBJ_FILES_MENU) \
	$(RAW_OBJ_FILES_MEMORY) $(RAW_OBJ_FILES_DRAW_3D) $(RAW_OBJ_LEV_EDITOR)
	gcc -o $(NAME) $(RAW_OBJ_FILES) $(RAW_OBJ_FILES_MEMORY) \
	$(RAW_OBJ_FILES_ENGINE) $(RAW_OBJ_FILES_PARSE) \
	$(RAW_OBJ_FILES_MENU) $(RAW_OBJ_FILES_DRAW_3D) \
	$(RAW_OBJ_LEV_EDITOR) $(LDFLAGS)
	@echo "$(PINK)(*≧ω≦*)  $(BLUE)Mama, ya sobralsya  $(PINK)(*≧ω≦*)"
# 	@sh /Users/hchau/Desktop/hohow/priv.sh

$(SDL_DIST):
	$(info ************ Compiling SDL *************)
	$(info --prefix=$(SDL_DIST))
	mkdir -p $(SDL_DIR)/tmp
	cd $(SDL_DIR)/tmp; ../configure --prefix=$(SDL_DIST)
	make -C $(SDL_DIR)/tmp
	make -C $(SDL_DIR)/tmp install > /dev/null
	$(info SDL_LINK: $(SDL_LINK))

#### К о м п и л я ц и я ####

-include $(DEPS)
$(OBJ_DIR)/1_%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

# -include $(DEPS)
# $(OBJ_DIR)/2_%.o: $(SRC_3D_DIR)/%.c | $(OBJ_DIR)
# 	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/3_%.o: $(ENGINE_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/4_%.o: $(PARSE_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/5_%.o: $(MENU_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/6_%.o: $(MEMORY_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/7_%.o: $(DRAW_3D_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

-include $(DEPS)
$(OBJ_DIR)/8_%.o: $(LEV_EDITOR_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS_FINAL) -c $< -o $@

clean: clean_libs clean_SDL clean_self

clean_libs:
	$(MAKE) -C ./libft clean

clean_SDL:
	rm -rf $(SDL_DIR)/tmp

clean_self:
	rm -rfv $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C ./libft fclean
	rm -rf $(SDL_DIST)

re: fclean all
