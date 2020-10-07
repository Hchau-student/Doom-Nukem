//
// Created by Hugor Chau on 10/7/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

/*
**		entry point to drawing things
*/

static void		chose_layers(t_data *data)
{
	put_layer(data->sdl->tex,
			  data->textures[1]->bit_map,
			  data->textures[1]->width,
			  data);
	put_layer(data->sdl->tex,
			  data->sdl->layers->draw_3d->bit_map,
			  data->sdl->layers->draw_3d->width,
			  data);
	put_layer(data->sdl->tex,
			  data->sdl->layers->hud->bit_map,
			  data->sdl->layers->hud->width,
			  data);
	put_layer(data->sdl->tex,
			  data->sdl->layers->minimap->bit_map,
			  data->sdl->layers->minimap->width,
			  data);
}

static void		move_player(t_data *data)
{
	if (data->sdl->key_pressed[RIGHT_ARROW])
		data->engine->player->direction_angle.x += 0.1;
	if (data->sdl->key_pressed[LEFT_ARROW])
		data->engine->player->direction_angle.x -= 0.1;
	if (data->sdl->key_pressed['W'])
	{
		data->engine->player->position.x += cos(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y += sin(data->engine->player->direction_angle.x) * 2;
	}
	if (data->sdl->key_pressed['S'])
	{
		data->engine->player->position.x -= cos(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y -= sin(data->engine->player->direction_angle.x) * 2;
	}
	if (data->sdl->key_pressed['A'])
	{
		data->engine->player->position.x += sin(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y -= cos(data->engine->player->direction_angle.x) * 2;
	}
	if (data->sdl->key_pressed['D'])
	{
		data->engine->player->position.x -= sin(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y += cos(data->engine->player->direction_angle.x) * 2;
	}
}

void		game_condition(t_data *data)
{
	move_player(data);
	draw_hud(data->engine->player->hud, data);
	data->engine->minimap->start_from = (t_vec2){0, 0};
	data->engine->minimap->size_divider = 5;
	draw_3d(data);
	draw_minimap(data);
	chose_layers(data);
	update_texture(data);
}
