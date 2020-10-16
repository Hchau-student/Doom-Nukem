//
// Created by Hugor Chau on 10/16/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

char	check_exit(t_data *data, int8_t curr_button)
{
	if (curr_button == BL_EXIT && data->sdl->mouse.is_pressed == TRUE)
	{
		data->menu.cur_map_name = ft_strjoin(DEFAULT_PATH, DEFAULT_MAP);
		data->level_editor->control_buttons->curr_button = -1;
		data->sdl->mouse.is_pressed = FALSE;
		menu(data);
	}
	return (FALSE);
}

char	check_save(t_data *data, int8_t curr_button)
{
	if (curr_button == BL_SAVE && data->sdl->mouse.is_pressed == TRUE)
	{
		create_new_file(data->menu.cur_map_name);
		data->sdl->mouse.is_pressed = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

char	check_draw_obj(t_data *data, int8_t curr_button)
{

	if (curr_button == BL_DRAW_OBJ)
		data->level_editor->curr_action = &le_draw_walls;
	else if (curr_button == BL_MOVE_OBJ)
		data->level_editor->curr_action = &le_move_obj;
	else
		data->level_editor->curr_action = NULL;
	return (TRUE);
}

char	buttons_are_disabled(t_data *data, int8_t curr_button)
{
	static char		old_press = FALSE;

	if (data->sdl->mouse.is_pressed == FALSE)
	{
		old_press = FALSE;
		return (FALSE);
	}
	if (old_press == TRUE)
		return (TRUE);
	if (data->sdl->mouse.is_pressed == TRUE)
		old_press = TRUE;
	return (FALSE);
}

int 	check_quick_click(t_data *data, int8_t curr_button)
{
	if (check_exit(data, curr_button))
		return (TRUE);
	else if (check_save(data, curr_button))
		return (TRUE);
	return (FALSE);
}

void	check_condition_changes(t_data *data, int8_t curr_button)
{
	if (data->sdl->mouse.is_pressed == TRUE)
	{
		data->level_editor->control_buttons->pressed_button = curr_button;
		data->sdl->mouse.is_pressed = FALSE;
		if (curr_button == BL_DRAW_OBJ)
			data->level_editor->curr_action = &le_draw_walls;
		else if (curr_button == BL_MOVE_OBJ)
			data->level_editor->curr_action = &le_move_obj;
		else
			data->level_editor->curr_action = NULL;
	}
}

void	le_change_condition(t_data *data, int8_t curr_button)
{
	if (buttons_are_disabled(data, data->level_editor->control_buttons->pressed_button))
		return;
	if (curr_button >= 0 && curr_button < BL_CONTRL_MAX)
	{
		if (!check_quick_click(data, curr_button))
		{
			check_condition_changes(data, curr_button);
			if (data->sdl->mouse.is_pressed == TRUE)
			{
				data->level_editor->control_buttons->pressed_button = curr_button;
				data->sdl->mouse.is_pressed = FALSE;
			}
		}
	}
}
