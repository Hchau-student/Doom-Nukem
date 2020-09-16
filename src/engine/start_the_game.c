//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	start_the_game(t_data *data)
{
	t_main_actions	actions;

	actions.mouse_event = &engine_mouse_event;
	actions.key_event = &engine_key_event;
	data->go_to = &actions;
}
