//
// Created by Hugor Chau on 7/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void		draw_wall_dots(t_data *data, t_wall *new_wall)
{
	int		curr_sec;
	t_wall	*wall;
	int		curr_wall;

	curr_sec = data->engine->sectors_count - 1;
	while (curr_sec >= 0)
	{
		wall = data->engine->sectors[curr_sec].render->walls;
		curr_wall = data->engine->sectors[curr_sec].render->walls_count;
		while (curr_wall > 0)
		{
			scale_image(data->level_editor->draw_data.dot, data->sdl->layers->minimap, (t_square){(t_vec2){wall->left.x - 7 + SCREEN_WIDTH / 2, wall->left.y - 7 + SCREEN_HEIGHT / 2},
				(t_vec2){wall->left.x + 7 + SCREEN_WIDTH / 2, wall->left.y + 7 + SCREEN_HEIGHT / 2}});
			scale_image(data->level_editor->draw_data.dot, data->sdl->layers->minimap, (t_square){(t_vec2){wall->right.x - 7 + SCREEN_WIDTH / 2, wall->right.y - 7 + SCREEN_HEIGHT / 2},
																								  (t_vec2){wall->right.x + 7 + SCREEN_WIDTH / 2, wall->right.y + 7 + SCREEN_HEIGHT / 2}});
			curr_wall--;
			wall = wall->next;
		}
		curr_sec--;
	}
	if (new_wall != NULL)
	{
		scale_image(data->level_editor->draw_data.dot, data->sdl->layers->minimap, (t_square){(t_vec2){new_wall->left.x - 7 + SCREEN_WIDTH / 2, new_wall->left.y - 7 + SCREEN_HEIGHT / 2},
				 (t_vec2){new_wall->left.x + 7 + SCREEN_WIDTH / 2, new_wall->left.y + 7 + SCREEN_HEIGHT / 2}});
		scale_image(data->level_editor->draw_data.dot, data->sdl->layers->minimap, (t_square){(t_vec2){new_wall->right.x - 7 + SCREEN_WIDTH / 2, new_wall->right.y - 7 + SCREEN_HEIGHT / 2},
				(t_vec2){new_wall->right.x + 7 + SCREEN_WIDTH / 2, new_wall->right.y + 7 + SCREEN_HEIGHT / 2}});
	}
}