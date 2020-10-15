//
// Created by Hugor Chau on 10/9/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

static void		chose_layers(t_data *data, t_level_editor *l)
{
	int		i;

	i = 0;
	put_layer(data->sdl->tex,
			  l->background->bit_map,
			  l->background->width,
			  data);
	while (i < BL_CONTRL_MAX)
	{
		change_button_brightness(&l->control_buttons->buttons[i]);
		scale_image(l->control_buttons->buttons[i].texture,
			data->sdl->layers->level_editor,
			l->control_buttons->buttons[i].borders);
		i++;
	}
	draw_minimap(data);
	if (l->curr_action)
		l->curr_action(data);
	put_layer(data->sdl->tex,
		  data->sdl->layers->minimap->bit_map,
		  data->sdl->layers->minimap->width,
		  data);
	put_layer(data->sdl->tex,
			  data->sdl->layers->level_editor->bit_map,
			  data->sdl->layers->level_editor->width,
			  data);

}

static void		chose_button(t_control_buttons *buttons)
{
	if (buttons->curr_button >= 0 && buttons->curr_button < BL_CONTRL_MAX)
		buttons->buttons[buttons->curr_button].brightness = 0xFF;
	if (buttons->pressed_button >= 0 && buttons->pressed_button < BL_CONTRL_MAX)
		buttons->buttons[buttons->pressed_button].brightness = 0xFF;
}

void		create_new_file(char *filename)
{
	char					*full_name;

	full_name = ft_strjoin("touch ", filename);
	system(full_name);
	ft_strdel(&full_name);
	full_name = ft_strjoin("chmod 777 ", filename);
	system(full_name);
	ft_strdel(&full_name);
}

void	le_change_condition(t_data *data, int8_t curr_button)
{
	if (curr_button >= 0 && curr_button < BL_CONTRL_MAX)
	{
		if (curr_button == BL_EXIT && data->sdl->mouse.is_pressed == TRUE)
		{
			data->menu.cur_map_name = ft_strjoin(DEFAULT_PATH, DEFAULT_MAP);
			data->level_editor->control_buttons->curr_button = -1;
			data->sdl->mouse.is_pressed = FALSE;
			menu(data);
		}
		else if (curr_button == BL_SAVE && data->sdl->mouse.is_pressed == TRUE)
		{
			create_new_file(data->menu.cur_map_name);
		}
		else if (data->sdl->mouse.is_pressed == TRUE)
		{
			data->level_editor->control_buttons->pressed_button = curr_button;
			data->sdl->mouse.is_pressed = FALSE;
			if (curr_button == BL_DRAW_OBJ)
				data->level_editor->curr_action = &le_draw_walls;
			else
				data->level_editor->curr_action = NULL;
		}
	}
}

void		palette_chose_object(t_data *data)
{
	if (data->level_editor->curr_action == BL_DRAW_OBJ)
	{
//		chose_curr_obj;
		data->level_editor->palette.curr_obj = PD_WALL;
	}
}

void		level_editor_condition(t_data *data)
{
	t_level_editor		*l;

	l = data->level_editor;
	prepare_all_buttons(l->control_buttons->buttons, BL_CONTRL_MAX);
	l->control_buttons->curr_button = -1;
	buttons_move_mouse(l->control_buttons->buttons,
					BL_CONTRL_MAX, &data->sdl->mouse, &l->control_buttons->curr_button);
	chose_button(l->control_buttons);
	le_change_condition(data, data->level_editor->control_buttons->curr_button);
	chose_layers(data, l);
	update_texture(data);
}
