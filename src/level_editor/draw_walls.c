//
// Created by Hugor Chau on 10/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void		prepare_sector(t_data *data)
{
	t_sector	*sectors;

	if (data->engine->sectors_count % 50 == 0)
	{
		sectors = (t_sector *)safe_call_ptr(ft_memalloc(sizeof(t_sector)
														* (data->engine->sectors_count + 50)), "Malloc crashed in"
																							   "\"./src/parse/parse_sector\", alloc_sectors.", data);
		safe_call_ptr(ft_memcpy(sectors, data->engine->sectors, sizeof(t_sector)
																* (data->engine->sectors_count)),
					  "ft_memcpy crashed in"
					  "\"./src/parse/parse_sector\", alloc_sectors.", data);
		data->engine->sectors = sectors;
	}
	if (data->engine->sectors_count == 0 || data->engine->sectors[data->engine->sectors_count - 1].is_ended == TRUE)
	{
		data->engine->sectors[data->engine->sectors_count].render =
				(t_sector_render *)safe_call_ptr(ft_memalloc(sizeof(t_sector_render)),
				"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
		sectors[data->engine->sectors_count].render->walls_count = 0;
		data->engine->sectors_count++;
		data->engine->sectors[data->engine->sectors_count - 1].is_ended = FALSE;
	}
	printf("%d\n", data->engine->sectors_count);
}

void		new_point(t_data *data, t_vec3 *point, t_wall *wall1)
{
	int		sec_num;
	int		sec_num_max;
	t_wall	*wall;
	t_vec3	new_point;
	int		curr_wall;

	if (wall1 == NULL)
		return ;
	new_point = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
	sec_num_max = data->engine->sectors_count;
	sec_num = 0;
	//1) пройтись по всем стенам в секторе, узнать, не пересекает ли чего;
	//2) сделать точки магнитами
	*point = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
	while (sec_num < sec_num_max)
	{
		curr_wall = data->engine->sectors[sec_num].render->walls_count;
		wall = data->engine->sectors[sec_num].render->walls;
		while (curr_wall > 0)
		{
			if (wall != wall1)
			{
				if (fabs(wall->right.x - new_point.x) < 10 && fabs(wall->right.y - new_point.y) < 10) {
					*point = wall->right;
					printf("wwwww%d\n", curr_wall);
					data->engine->sectors[sec_num].is_ended = TRUE;
					return;
				}
				if (fabs(wall->left.x - new_point.x) < 10 && fabs(wall->left.y - new_point.y) < 10) {
					*point = wall->left;
					printf("wwwww%d\n", curr_wall);
					data->engine->sectors[sec_num].is_ended = TRUE;
					return;
				}
			}
			wall = wall->next;
			curr_wall--;
		}
		sec_num++;
	}
}

void		fill_new_wall(t_data *data, char start, t_wall *wall)
{
	t_wall			*w;
	t_wall			*w1;

	if (wall == NULL)
		return ;
	w = wall;
	w->sector = &data->engine->sectors[data->engine->sectors_count - 1];
	w->ceiling_height = data->engine->sectors->ceiling_height;
	w->floor_height = data->engine->sectors->floor_height;
	if (data->engine->sectors[data->engine->sectors_count - 1].render->walls_count == 0)
	{
		if (start == FALSE)
			new_point(data, &w->left, w);
		else
			new_point(data, &w->right, w);
	}
	else
	{
		w1 = data->engine->sectors[data->engine->sectors_count - 1].render->walls->prev;
		if (start == FALSE)
			w->left = w1->right;
		else
			new_point(data, &w->right, w);
	}
}

void		le_change_wall(t_data *data, char start, t_wall **wall)
{
	if (wall == NULL)
		return ;
	if (start == TRUE)
		return (fill_new_wall(data, start, *wall));
	*wall = (t_wall *)safe_call_ptr(ft_memalloc(sizeof(t_wall)),
		"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
	fill_new_wall(data, start, *wall);
}

void		add_new_wall(t_data *data, t_wall *wall)
{
	t_wall			*w;
	t_sector		*sectors;
	int				sec_count;

	if (wall == NULL)
		return ;
	sec_count = data->engine->sectors_count - 1;
	sectors = data->engine->sectors;
	if (sectors[sec_count].render->walls_count == 0)
	{
//		printf("1\n");
		wall->next = wall;
		wall->prev = wall;
		data->engine->sectors[sec_count].render->walls = wall;
	}
	else
	{
		w = sectors[sec_count].render->walls;
		if (w->prev == wall)
			return ;
//		printf("2\n");
		w->prev->next = wall;
		wall->prev = w->prev;
		w->prev = w->prev->next;
		w->prev->next = w;
	}
	sectors[sec_count].render->walls_count++;
}

void		le_draw_wall(t_data *data)
{
	static char			start = FALSE;
	static t_wall		*wall = NULL;

	if (start == TRUE)
	{
		add_new_wall(data, wall);
//		if (data->engine->sectors[data->engine->sectors_count - 1].render.)
	}
	if (data->sdl->mouse.is_pressed == TRUE)
	{
		if (data->level_editor->palette.curr_obj == PD_WALL)
		{
			if (data->engine->sectors_count % 50 == 0)
			prepare_sector(data);
			le_change_wall(data, start, &wall);
		}
		start = TRUE;
	}
	else
	{
		if (start == TRUE)
		{
			wall = NULL;
			if (data->engine->sectors[data->engine->sectors_count - 1].is_ended == TRUE)
				prepare_sector(data);
		}
		start = FALSE;
	}
}

void		le_draw_walls(t_data *data)
{
	le_draw_wall(data);
}