//
// Created by Hugor Chau on 10/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void		move_wall(t_data *data, t_wall *left_changes, t_wall *right_changes)
{
	if (left_changes)
	{
		left_changes->left.x = data->sdl->mouse.x - SCREEN_WIDTH / 2;
		left_changes->left.y = data->sdl->mouse.y - SCREEN_HEIGHT / 2;
	}
	if (right_changes)
	{
		right_changes->right.x = data->sdl->mouse.x - SCREEN_WIDTH / 2;
		right_changes->right.y = data->sdl->mouse.y - SCREEN_HEIGHT / 2;
	}
}

void		chose_wall_move(t_data *data, t_wall **one, t_wall **two)
{
	int		curr_sec;
	t_wall	*wall;
	int		curr_wall;
	t_vec3	mouse;

	mouse = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
	curr_sec = data->engine->sectors_count - 1;
	while (curr_sec >= 0)
	{
		wall = data->engine->sectors[curr_sec].render->walls;
		curr_wall = data->engine->sectors[curr_sec].render->walls_count;
		if (wall != NULL)
		{
			while (curr_wall >= 0) {
				if (point_match(mouse, wall->left) == TRUE)
				{
					*one = wall;
					if (point_match(wall->left, wall->prev->right))
						*two = wall->prev;
					if (point_match(wall->left, wall->next->right))
						*two = wall->next;
					return ;
				}
				else if (point_match(mouse, wall->right) == TRUE)
					*two = wall;
				curr_wall--;
				wall = wall->next;
			}
		}
		curr_sec--;
	}
}

void		chose_wall_to_move(t_data *data, t_wall **left_changes, t_wall **right_changes, char *was_mouse_pressed_before)
{
	if (*was_mouse_pressed_before == FALSE)
	{
		chose_wall_move(data, left_changes, right_changes);
		*was_mouse_pressed_before = TRUE;
	}
}

void		le_move_obj(t_data *data)
{
	static char		new_move = FALSE;
	static t_wall	*left_changes = NULL;
	static t_wall	*right_changes = NULL;

	if (data->sdl->mouse.is_pressed == TRUE)
	{
		chose_wall_to_move(data, &left_changes, &right_changes, &new_move);
		if (new_move == TRUE)
		{
			move_wall(data, left_changes, right_changes);
		}
	}
	else if (new_move == TRUE)
	{
		left_changes = NULL;
		right_changes = NULL;
		new_move = FALSE;
	}
	draw_sector_dots(data, data->level_editor->draw_data.dot_move);
}
