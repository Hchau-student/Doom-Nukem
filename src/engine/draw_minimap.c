//
// Created by Hugor Chau on 9/23/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	draw_walls_minimap(t_sector_render *sector, t_data *data)
{
	t_twlist	*tmp;
	int			i;

	if (sector == NULL)
		return;
	tmp = sector->walls;
	i = 0;
	while (i < sector->walls_count)
	{
		draw_line(tmp->content, &data->sdl->color_buffer, 0xFFFFFF);
		i++;
		tmp = tmp->next;
	}
}

void	draw_sector_minimap(int i, t_data *data)
{
	draw_walls_minimap(data->engine->sectors[i].render, data);
}

void	draw_minimap(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->engine->sectors_count)
	{
		draw_sector_minimap(i, data);
		i++;
	}
}
