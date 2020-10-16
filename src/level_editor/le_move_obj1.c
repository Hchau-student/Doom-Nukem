//
// Created by Hugor Chau on 10/16/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void		move_wall(t_data *data, t_wall_change *left_changes, t_wall_change *right_changes)
{
	while (left_changes)
	{
		if (left_changes->wall != NULL)
		{
			left_changes->wall->left.x = MOUSE_X;
			left_changes->wall->left.y = MOUSE_Y;
		}
		left_changes = left_changes->next_change;
	}
	while (right_changes)
	{
		if (right_changes->wall != NULL)
		{
			right_changes->wall->right.x = MOUSE_X;
			right_changes->wall->right.y = MOUSE_Y;
		}
		right_changes = right_changes->next_change;
	}
//	printf("Here\n");
}

void		remember_changed_wall(t_wall_change **wall_change, t_wall *wall)
{
	if ((*wall_change) == NULL)
		return;
	if ((*wall_change)->wall == NULL)
	{
		(*wall_change)->wall = wall;
		(*wall_change)->next_change = NULL;
	}
	else
	{
		(*wall_change)->next_change = ft_memalloc(sizeof(t_wall_change));
		(*wall_change)->next_change->wall = wall;
		(*wall_change) = (*wall_change)->next_change;
		(*wall_change)->next_change = NULL;
	}
}

void		chose_wall_move(t_data *data, t_wall_change **one, t_wall_change **two)
{
	int				curr_sec;
	t_wall_change	*left;
	t_wall_change	*right;
	t_wall			*wall;
	int				curr_wall;
	t_vec3			mouse;

	*one = ft_memalloc(sizeof(t_wall_change));
	*two = ft_memalloc(sizeof(t_wall_change));
	left = *one;
	right = *two;
	mouse = (t_vec3){MOUSE_X, MOUSE_Y, 0};
	curr_sec = data->engine->sectors_count - 1;
	while (curr_sec >= 0)
	{
		wall = data->engine->sectors[curr_sec].render->walls;
		curr_wall = data->engine->sectors[curr_sec].render->walls_count;
		if (wall != NULL)
		{
			while (curr_wall >= 0)
			{
				if (point_match(mouse, wall->left) == TRUE)
					remember_changed_wall(&left, wall);
				else if (point_match(mouse, wall->right) == TRUE)
					remember_changed_wall(&right, wall);
				curr_wall--;
				wall = wall->next;
			}
		}
		curr_sec--;
	}
}

void		chose_wall_to_move(t_data *data, t_wall_change **left_changes, t_wall_change **right_changes, char *was_mouse_pressed_before)
{
	if (*was_mouse_pressed_before == FALSE)
	{
		chose_wall_move(data, left_changes, right_changes);
		*was_mouse_pressed_before = TRUE;
	}
}

void		remove_all_walls(t_wall_change **l, t_wall_change **r)
{
	t_wall_change		*tmp;

	if (*l)
	{
		tmp = (*l)->next_change;
		while (tmp)
		{
			ft_memdel((void **)l);
			(*l) = tmp;
			tmp = (*l)->next_change;
		}
	}
	if (*r)
	{
		tmp = (*r)->next_change;
		while (tmp)
		{
			ft_memdel((void **)r);
			(*r) = tmp;
			tmp = (*r)->next_change;
		}
	}
}

void		le_move_obj(t_data *data)
{
	static char				move_screen = FALSE;
	static char				new_move = FALSE;
	static t_wall_change	*left_changes = NULL;
	static t_wall_change	*right_changes = NULL;

	if (data->sdl->mouse.is_pressed == TRUE)
	{
		if (new_move == FALSE)
			chose_wall_to_move(data, &left_changes, &right_changes, &new_move);
		else
			move_wall(data, left_changes, right_changes);
	}
	else if (new_move == TRUE)
	{
		remove_all_walls(&left_changes, &right_changes);
		new_move = FALSE;
	}
	draw_sector_dots(data, data->level_editor->draw_data.dot_move);
}
