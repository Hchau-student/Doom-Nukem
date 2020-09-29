//
// Created by Hugor Chau on 9/14/20.
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

static void		game_condition(t_data *data)
{
	draw_hud(data->engine->player->hud, data);
	data->engine->minimap->start_from = (t_vec2){0, 0};
	data->engine->minimap->size_divider = 5;
	draw_3d(data);
	draw_minimap(data);
	chose_layers(data);
	update_texture(data);
}

/*
**		changing game condition
*/

void			start_the_game(t_data *data)
{
	data->go_to->mouse_event = &engine_mouse_event;
	data->go_to->key_event = &engine_key_event;
	data->go_to->condition = &game_condition;
}
