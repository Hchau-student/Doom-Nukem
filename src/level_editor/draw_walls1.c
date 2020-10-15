//
// Created by Hugor Chau on 10/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

/*
 * TODO
 * */


int		fill_new_wall(t_data *data, char is_old_wall, t_wall *wall)
{
	t_wall			*w;
	t_wall			*w1;

	if (wall == NULL)
		return FALSE;
	w = wall;
	w->sector = &data->engine->sectors[data->engine->sectors_count - 1];
	w->ceiling_height = data->engine->sectors->ceiling_height;
	w->floor_height = data->engine->sectors->floor_height;
	if (data->engine->sectors[data->engine->sectors_count - 1].render->walls_count == 0)
	{
		if (is_old_wall == FALSE)
		{
			(new_point(data, &w->right, w));
			(new_point(data, &w->left, w));
		}
		else
			return (new_point(data, &w->right, w));
	}
	else
	{
		w1 = data->engine->sectors[data->engine->sectors_count - 1].render->walls->prev;
		if (is_old_wall == FALSE)
		{
			w->left = w1->right;
			w->right = w1->right;
		}
		else
			return (new_point(data, &w->right, w));
	}
	return (FALSE);
}

int		le_change_wall(t_data *data, char is_old_wall, t_wall **wall)
{
	if (wall == NULL)
		return FALSE;
	if (is_old_wall == TRUE)
		return (fill_new_wall(data, is_old_wall, *wall));
	*wall = (t_wall *)safe_call_ptr(ft_memalloc(sizeof(t_wall)),
		"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
	return (fill_new_wall(data, is_old_wall, *wall));
}

void		check_if_ended(t_data *data, int is_sector_ended)
{
	int			sec_count;

	sec_count = data->engine->sectors_count - 1;
	if (is_sector_ended == TRUE)
		data->engine->sectors[sec_count].is_ended = TRUE;
	prepare_sector(data);
}

int			check_clickable_area(t_data *data)
{
	if (data->level_editor->control_buttons->curr_button == BL_SAVE)
		return (FALSE);
	return (TRUE);
}

void		le_draw_wall(t_data *data)
{
	static char			new_wall = FALSE;
	static t_wall		*wall = NULL;
	static int			is_sector_ended = FALSE;

	if (check_clickable_area(data) == FALSE)
	{
		draw_wall_dots(data, wall);
		return ;
	}
	if (data->sdl->mouse.is_pressed == TRUE)
	{
		draw_changed_wall(wall, data);
		if (data->engine->sectors_count % 50 == 0)
			prepare_sector(data);
		is_sector_ended = le_change_wall(data, new_wall, &wall);
		new_wall = TRUE;
	}
	else
	{
		if (new_wall == TRUE)
		{
			add_new_wall(data, wall);
			check_if_ended(data, is_sector_ended);
			wall = NULL;
		}
		new_wall = FALSE;
	}
	draw_wall_dots(data, wall);
}

void		le_draw_walls(t_data *data)
{
	le_draw_wall(data);
}
