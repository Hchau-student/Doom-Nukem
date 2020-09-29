//
// Created by Hugor Chau on 9/28/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/map_struct.h"

void	check_player_place(t_data *data)
{
	uint32_t		i;
	t_vec2			position;
	char			flag;
	static int		j = 0;

	i = 0;
	flag = FALSE;
	position = data->engine->player->position;
	while (i < data->engine->sectors_count)
	{
		if (is_inside(position.x, position.y, data->engine->sectors[i].render) % 2 == 1)
		{
			data->engine->player->current_sector = &data->engine->sectors[i];
			flag = TRUE;
			break ;
		}
		i++;
	}
	if (flag == FALSE)
	{
		ft_putendl("ERROR!");
		printf("%d\n", j);
	}
	j++;
}

void	draw_sector_3d(t_sector *sector, uint32_t walls_count, t_data *data)
{
	uint32_t	i;
	t_wall		*wall;

	i = 0;
	wall = sector->render->walls;
	while (i < walls_count)
	{
		if (wall->type == WALL)
			draw_wall_3d(wall, data);
		if (wall->type == PORTAL || wall->type == WINDOW)
		{
			wall->portal_to->sector->render->walls = wall->portal_to->next;
			draw_sector_3d(wall->portal_to->sector,
					wall->portal_to->sector->render->walls_count - 1, data);
		}
		wall = wall->next;
		i++;
	}
}

void	clear_bitmap(t_texture *texture)
{
	uint32_t	i;

	i = 0;
	while (i < texture->width * texture->height)
	{
		texture->bit_map[i] = 0x0;
		i++;
	}
}

void	draw_3d(t_data *data)
{
	uint32_t		i;

	i = 0;
	clear_bitmap(data->sdl->layers->draw_3d);
	check_player_place(data);
//	while (i < data->engine->sectors_count)
//	{
//		draw_sector_3d(&data->engine->sectors[i],
//					   data->engine->sectors[i].render->walls_count, data);
//		i++;
//	}
	draw_sector_3d(data->engine->player->current_sector,
		data->engine->player->current_sector->render->walls_count, data);
}
