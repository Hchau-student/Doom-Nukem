//
// Created by Hugor Chau on 10/9/20.
//

#ifndef DOOM_NUKEM_STRUCTURE_LEVEL_EDITOR_H
#define DOOM_NUKEM_STRUCTURE_LEVEL_EDITOR_H

#include "map_struct.h"

void		init_default_map(t_data *data);

typedef enum		e_button_edit
{
	BL_DRAW_OBJ,
	BL_MOVE_OBJ,
	BL_DEL_OBJ,
	BL_SAVE,
	BL_EXIT,
//	BL_GO_3D,
	BL_CONTRL_MAX
}					t_button_edit;

#define LEVEL_EDITOR_BUTTONS_NAMES	{"draw_obj", "move_obj", "del_obj", "save", "le_exit"}

typedef enum		e_pallette_data
{
	PD_WALL,
	PD_PLAYER,

	PD_ENEMY,

	PD_MEDICINE,
	PD_ARMOR,
	PD_POISON,
	PD_CARABINE_BULLETS,
	PD_CARABINE_WEAPON,

	PD_BULLETS,
	PD_COUNT
}					t_pallete_data;

#define PALETTE_DATA_NAMES {"pb_wall", "pb_player", "pb_enemy", "pb_medicine", "pb_armor", \
							"pb_poison", "pb_carabine_bullets", "pb_carabine_weapon", \
							"pb_bullets"}

typedef struct		s_palette
{
	t_texture		*background;
	t_button		choose_data[PD_COUNT];//wall/enemies/
	t_button		slider;
	int8_t			curr_obj;
}					t_palette;

typedef struct		s_control_buttons
{
	t_button		buttons[BL_CONTRL_MAX];
	int8_t			curr_button;
	int8_t			pressed_button;
}					t_control_buttons;

typedef struct		s_draw_data
{
	int8_t			chosen_data;
	t_texture		*dot;
}					t_draw_data;

typedef struct		s_level_editor
{
	t_texture			*background;
	void				(*curr_action)(t_data *data);
	t_control_buttons	control_buttons[BL_CONTRL_MAX];
	t_palette			palette;
	t_draw_data			draw_data;
}					t_level_editor;

void		level_editor_condition(t_data *data);
void		le_draw_walls(t_data *data);
void		init_level_editor(t_data *data);
void		prepare_sector(t_data *data);

/*
**		add_new_wall.c
*/

void		add_new_wall(t_data *data, t_wall *wall);
void		draw_changed_wall(t_wall *wall, t_data *data);

/*
**		wall_making_process.c
*/

int			new_point(t_data *data, t_vec3 *point, t_wall *wall);

/*
**		draw_wall_dots.c
*/

void		draw_wall_dots(t_data *data, t_wall *new_wall);

#endif //DOOM_NUKEM_STRUCTURE_LEVEL_EDITOR_H
