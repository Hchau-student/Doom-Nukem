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
		if (data->engine->sectors_count != 0 && data->engine->sectors[data->engine->sectors_count - 1].is_ended == FALSE)
			return;
		sectors = (t_sector *)safe_call_ptr(ft_memalloc(sizeof(t_sector)
			* (data->engine->sectors_count + 50)), "Malloc crashed in"
			"\"./src/parse/parse_sector\", alloc_sectors.", data);
		safe_call_ptr(ft_memcpy(sectors, data->engine->sectors, sizeof(t_sector)
				* (data->engine->sectors_count)),
				"ft_memcpy crashed in"
				"\"./src/parse/parse_sector\", alloc_sectors.", data);
		sectors[data->engine->sectors_count].render =
				(t_sector_render *)safe_call_ptr(ft_memalloc(sizeof(t_sector_render)),
				"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
		sectors[data->engine->sectors_count].render->walls_count = 0;
		data->engine->sectors = sectors;
		data->engine->sectors_count++;
	}
//	data->engine->sectors[data->engine->sectors_count - 1].render->walls = NULL;
}

void		fill_new_wall(t_data *data)
{
	t_wall			*w;

	w = data->engine->sectors[data->engine->sectors_count - 1].render->walls->prev;
	w->sector = &data->engine->sectors[data->engine->sectors_count - 1];
	w->ceiling_height = data->engine->sectors->ceiling_height;
	w->floor_height = data->engine->sectors->floor_height;
	if (data->engine->sectors[data->engine->sectors_count - 1].render->walls_count <= 1)
	{
		w->left = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
		w->right = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
	}
	else
	{

		w->left = w->prev->right;
		w->right = (t_vec3){data->sdl->mouse.x - SCREEN_WIDTH / 2, data->sdl->mouse.y - SCREEN_HEIGHT / 2, 0};
	}
}

void		le_add_new_wall(t_data *data)
{
	t_sector		*sectors;
	int				sec_count;
	t_wall			*w;

	sec_count = data->engine->sectors_count - 1;
	sectors = data->engine->sectors;
	if (sectors[sec_count].render->walls_count == 0)
	{
		printf("1\n");
		w = (t_wall *)safe_call_ptr(ft_memalloc(sizeof(t_wall)),
			"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
		w->next = w;
		w->prev = w;
		data->engine->sectors[sec_count].render->walls = w;
	}
	else
	{
		printf("2\n");

		w = sectors[sec_count].render->walls;
		w->prev->next = (t_wall *)safe_call_ptr(ft_memalloc(sizeof(t_wall)),
			"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
		w->prev->next->prev = w->prev;
		w->prev = w->prev->next;
		w->prev->next = w;
	}
	sectors[sec_count].render->walls_count++;
	fill_new_wall(data);
}

void		le_draw_wall(t_data *data)
{
	static t_wall		*wall;

	if (data->sdl->mouse.is_pressed == TRUE)
	{
		if (data->level_editor->palette.curr_obj == PD_WALL)
		{
			prepare_sector(data);
			le_add_new_wall(data);
//			printf("%d\n", data->engine->sectors_count - 1);
		}
	}
}

void		le_draw_walls(t_data *data)
{
	le_draw_wall(data);
}
