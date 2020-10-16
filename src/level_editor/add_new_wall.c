//
// Created by Hugor Chau on 10/15/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

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
