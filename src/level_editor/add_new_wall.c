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

void		draw_changed_wall(t_wall *wall, t_data *data)
{
	t_line		line;
	t_minimap	*minimap;

	if (wall == NULL)
		return;
	minimap = data->engine->minimap;
	line.start.x = (wall->left.x - minimap->start_from.x) / minimap->size_divider;
	line.start.y = (wall->left.y - minimap->start_from.y) / minimap->size_divider;
	line.end.x = (wall->right.x - minimap->start_from.x) / minimap->size_divider;
	line.end.y = (wall->right.y - minimap->start_from.y) / minimap->size_divider;
	if (wall->type == WALL)
		draw_line(line, data->sdl->layers->minimap, 0xFF00FFFF);
	else
		draw_line(line, data->sdl->layers->minimap, 0xFFFF00FF);
}
