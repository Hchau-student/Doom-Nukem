//
// Created by Hugor Chau on 7/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

t_square		scale_dot_borders(t_vec3 point, t_minimap *minimap)
{
	t_square		borders;

	borders.start.x = (point.x - minimap->start_from.x) / minimap->size_divider - 7;
	borders.start.y = (point.y - minimap->start_from.y) / minimap->size_divider - 7;
	borders.end.x = (point.x - minimap->start_from.x) / minimap->size_divider + 7;
	borders.end.y = (point.y - minimap->start_from.y) / minimap->size_divider + 7;
	return (borders);
}

void		draw_sector_dots(t_data *data, t_texture *dot)
{
	int			curr_sec;
	t_wall		*wall;
	int			curr_wall;
	t_square	borders;

	curr_sec = data->engine->sectors_count - 1;
	while (curr_sec >= 0)
	{
		wall = data->engine->sectors[curr_sec].render->walls;
		curr_wall = data->engine->sectors[curr_sec].render->walls_count;
		while (curr_wall > 0)
		{
			borders = scale_dot_borders(wall->left, data->engine->minimap);
			scale_image(dot, data->sdl->layers->minimap, borders);
			borders = scale_dot_borders(wall->right, data->engine->minimap);
			scale_image(dot, data->sdl->layers->minimap, borders);
			curr_wall--;
			wall = wall->next;
		}
		curr_sec--;
	}
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

void		draw_wall_dots(t_data *data, t_wall *new_wall)
{
	t_square	borders;

	draw_changed_wall(new_wall, data);
	draw_sector_dots(data, data->level_editor->draw_data.dot_draw);
	if (new_wall != NULL)
	{
		borders = scale_dot_borders(new_wall->left, data->engine->minimap);
		scale_image(data->level_editor->draw_data.dot_draw, data->sdl->layers->minimap, borders);
		borders = scale_dot_borders(new_wall->right, data->engine->minimap);
		scale_image(data->level_editor->draw_data.dot_move, data->sdl->layers->minimap, borders);
	}
}
