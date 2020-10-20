//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

/*
**		changing game condition
*/

void			start_the_game(t_data *data)
{
	clear_keysum(data);
	data->engine->minimap->size_divider = 3.2;
	data->engine->minimap->background = find_texture_by_name("minimap", data);
	data->go_to->condition = &game_condition;
	data->go_to->condition_name = GAME;
}
