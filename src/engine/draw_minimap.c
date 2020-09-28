//
// Created by Hugor Chau on 9/23/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	draw_walls_minimap(t_sector_render *sector, uint32_t denum, t_data *data, t_vec2 start_from)
{
	t_twlist	*tmp;
	int			i;
	t_wall		curr_wall;

	if (sector == NULL)
		return;
	tmp = sector->walls;
	i = 0;
	while (i < sector->walls_count)
	{
		curr_wall = *((t_wall *)(tmp->content));
		curr_wall.left.x = (curr_wall.left.x - start_from.x) / denum;
		curr_wall.left.y = (curr_wall.left.y - start_from.y) / denum;
		curr_wall.right.x = (curr_wall.right.x - start_from.x) / denum;
		curr_wall.right.y = (curr_wall.right.y - start_from.y) / denum;
		draw_line(&curr_wall, &data->engine->minimap->bit_map, 0xFF00FFFF);
		i++;
		tmp = tmp->next;
	}
}

void	draw_sector_minimap(int i, t_data *data, uint32_t denum, t_vec2 start_from)
{
	draw_walls_minimap(data->engine->sectors[i].render, denum, data, start_from);
}

void	draw_minimap(t_data *data, uint32_t denum, t_vec2 start_from)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	denum = 5;
	while (i < data->engine->minimap->width / denum)
	{
		j = 0;
		while (j < data->engine->minimap->height / denum)
		{
			data->engine->minimap->bit_map[i + j * data->engine->minimap->width] = 0x600000FF;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->engine->sectors_count)
	{
		draw_sector_minimap(i, data, denum, start_from);
		i++;
	}
	scale_image(data->engine->minimap, data->sdl->layers->minimap,
			data,
			(t_square){(t_vec2){0.0, 0.0},
			(t_vec2){SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1}});
}
