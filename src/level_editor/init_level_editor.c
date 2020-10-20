#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
#include "../../Include/level_editor.h"
/*
**		init_buttons should be in one function!
*/

void		le_init_buttons(t_level_editor *l, t_data *data)
{
	char		*name[BL_CONTRL_MAX] = LEVEL_EDITOR_BUTTONS_NAMES;
	int			i;

	i = 0;
	while (i < BL_CONTRL_MAX)
	{
		l->control_buttons->buttons[i].height = 50;
		l->control_buttons->buttons[i].width = 50;
		l->control_buttons->buttons[i].x = SCREEN_WIDTH - 70;
		l->control_buttons->buttons[i].y = 70 * i + 20;
		l->control_buttons->buttons[i].borders.start = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
		l->control_buttons->buttons[i].borders.end = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
		l->control_buttons->buttons[i].borders.end.x += 50;
		l->control_buttons->buttons[i].borders.end.y += 50;
		l->control_buttons->buttons[i].texture = find_texture_by_name(name[i], data);
		i++;
	}
}

void		init_palette(t_data *data)
{
	char		*name[PD_COUNT] = PALETTE_DATA_NAMES;
	int			i;

	i = 0;
	data->level_editor->palette.background = find_texture_by_name("palette_background", data);
//	while (i < PD_COUNT)
//	{
//		data->level_editor->palette.choose_data[i].height = 50;
//		data->level_editor->palette.choose_data[i].width = 50;
//		data->level_editor->palette.choose_data[i].x = SCREEN_WIDTH - 70;
//		data->level_editor->palette.choose_data[i].y = 70 * i + 20;
//		data->level_editor->palette.choose_data[i].borders.start = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
//		data->level_editor->palette.choose_data[i].borders.end = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
//		data->level_editor->palette.choose_data[i].borders.end.x += 50;
//		data->level_editor->palette.choose_data[i].borders.end.y += 50;
//		data->level_editor->palette.choose_data[i].texture = find_texture_by_name(name[i], data);
//		i++;
//	}
}

void		init_level_editor(t_data *data)
{
	t_level_editor		*level_editor;

	data->engine->minimap->size_divider = 1;
	rescale_minimap(data->engine->minimap, data);
	level_editor = (t_level_editor *)safe_call_ptr(ft_memalloc(sizeof(t_level_editor)),
				"Malloc crashed, ./src/level_editor/level_editor.c",
				data);
	level_editor->control_buttons->pressed_button = -1;
	level_editor->draw_data.dot_draw = find_texture_by_name("wall_dot_draw", data);
	level_editor->draw_data.dot_move = find_texture_by_name("wall_dot_move", data);
	level_editor->background = find_texture_by_name("bedy_c_mamami", data);
	data->level_editor = level_editor;
	le_init_buttons(data->level_editor, data);
	init_palette(data);
	//1) init_palette_buttons_and_pallete_background
	//2) resize_img_to_background
//	resize_img
}
