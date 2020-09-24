//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

/*
**		entry point to drawing things
*/

void	game_condition(t_data *data)
{
	draw_hud(((t_engine *)data->engine)->player->hud, data);
	draw_minimap(data);
	update_texture(data);
}

/*
**		changing game condition
*/

void	start_the_game(t_data *data)
{
	data->go_to->mouse_event = &engine_mouse_event;
	data->go_to->key_event = &engine_key_event;
	data->go_to->condition = &game_condition;
}
