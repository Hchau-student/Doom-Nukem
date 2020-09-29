//
// Created by Hugor Chau on 9/28/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		draw_wall_minimap(t_wall *wall, t_data *data)
{
	t_line		line;
	t_minimap	*minimap;

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

static void		draw_walls_minimap(t_sector_render *sector, t_data *data)
{
	t_wall		*tmp;
	int			i;
	t_wall		curr_wall;

	if (sector == NULL)
		return;
	tmp = sector->walls;
	i = 0;
	while (i < sector->walls_count)
	{
		curr_wall = *tmp;
		draw_wall_minimap(&curr_wall, data);
		i++;
		tmp = tmp->next;
	}
}

/*
**		draw player and his/her FOV;
**		need to be improved, cause я хочу
**		клёвые лучи!
*/

void			draw_minimap_player(t_data *data)
{
	t_ivec2		pos;
	uint32_t	centre;
	t_minimap	*minimap;
	t_line		line;
	float		fov;

	centre = 4;
	minimap = data->engine->minimap;
	pos.x = SCREEN_WIDTH / 2 / minimap->size_divider - 1;
	pos.y = SCREEN_HEIGHT / 2 / minimap->size_divider - 1;
	line.start.x = pos.x + centre;
	line.start.y = pos.y + centre;
	fov = (data->engine->player->fov / 2) * M_PI / 180;
	line.end.x = pos.x + centre + cos(data->engine->player->direction_angle.x + fov) * 30;
	line.end.y = pos.y + centre + sin(data->engine->player->direction_angle.x + fov) * 30;
	draw_line(line, minimap->texture, 0xFFFF5050);
	line.end.x = pos.x + centre + cos(data->engine->player->direction_angle.x - fov) * 30;
	line.end.y = pos.y + centre + sin(data->engine->player->direction_angle.x - fov) * 30;
	draw_line(line, minimap->texture, 0xFFFF5050);
	scale_image(minimap->player_icon, minimap->texture,
		(t_square){(t_vec2){pos.x, pos.y},
		(t_vec2){pos.x + 8, pos.y + 8}});
}

void			draw_minimap_sectors(t_data *data)
{
	uint32_t		i;

	i = 0;
	while (i < data->engine->sectors_count)
	{
		draw_walls_minimap(data->engine->sectors[i].render, data);
		i++;
	}
}

void			draw_minimap_background(t_minimap *minimap)
{
	scale_image(minimap->background, minimap->texture,
		(t_square){(t_vec2){0, 0},
		(t_vec2){minimap->texture->width / minimap->size_divider,
		minimap->texture->height / minimap->size_divider}});
}
