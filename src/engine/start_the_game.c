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
	data->go_to->mouse_event = &engine_mouse_event;
	data->go_to->key_event = &engine_key_event;
	data->go_to->condition = &game_condition;
}
