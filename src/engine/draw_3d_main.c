//
// Created by Hugor Chau on 9/28/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	draw_sector_3d(t_sector *sector, uint32_t walls_count)
{
	uint32_t	i;
	t_wall		*wall;

	i = 0;
//	ft_putnbr(walls_count);
//	wall = sector->render->walls;
//	while (i < walls_count)
//	{
////		if (wall->type == WALL)
////			draw;
////		if (wall->type == PORTAL || wall->type == WINDOW)
////		{
////			wall->portal_to->sector->render->walls = wall->portal_to;
////			draw_sector(wall->portal_to->sector,
////					wall->portal_to->sector->render->walls_count);
////		}
////		wall = wall->next;
//		i++;
//	}
}

void	check_player_place(t_data *data)
{
	uint32_t		i;
	t_vec2			position;

	i = 0;
	position = data->engine->player->position;
	while (i < data->engine->sectors_count)
	{
		if (is_inside(position.x, position.y, data->engine->sectors[i].render) % 2 == 1)
		{
			data->engine->player->current_sector = &data->engine->sectors[i];
		}
		i++;
	}
	if (data->engine->player->current_sector == NULL)
		ft_putendl("ERROR!");
}

void	draw_3d(t_data *data)
{
	check_player_place(data);
//	draw_sector_3d(data->engine->player->current_sector,
//		data->engine->player->current_sector->render->walls_count);
}
