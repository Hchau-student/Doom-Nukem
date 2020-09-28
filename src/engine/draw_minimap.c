//
// Created by Hugor Chau on 9/23/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	delete_extra_lines(t_minimap *minimap)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < minimap->texture->width)
	{
		j = 0;
		while (j < minimap->texture->height)
		{
			if (j >= minimap->texture->height / minimap->size_divider || i >= minimap->texture->width / minimap->size_divider)
				minimap->texture->bit_map[i + j * minimap->texture->width] = 0x00000000;
			j++;
		}
		i++;
	}
}

void	rescale_minimap(t_minimap *minimap, t_data *data)
{
	minimap->start_from.x = data->engine->player->position.x - SCREEN_WIDTH / 2;
	minimap->start_from.y = data->engine->player->position.y - SCREEN_HEIGHT / 2;
	minimap->size_divider = 3.2;
}

void	draw_minimap(t_data *data)
{
	t_minimap	*minimap;

	minimap = data->engine->minimap;
	rescale_minimap(minimap, data);
	draw_minimap_background(minimap);
	draw_minimap_sectors(data);
	draw_minimap_player(data);
	delete_extra_lines(minimap);
}
