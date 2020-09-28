//
// Created by Hugor Chau on 9/16/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	engine_key_event(SDL_Event *event, t_data *data)
{
	if (event->key.keysym.sym == SDLK_RIGHT)
		data->engine->player->direction_angle.x += 0.1;
	if (event->key.keysym.sym == SDLK_LEFT)
		data->engine->player->direction_angle.x -= 0.1;
	if (event->key.keysym.sym == SDLK_w)
	{
		data->engine->player->position.x += cos(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y += sin(data->engine->player->direction_angle.x) * 2;
	}
	if (event->key.keysym.sym == SDLK_s)
	{
		data->engine->player->position.x -= cos(data->engine->player->direction_angle.x) * 2;
		data->engine->player->position.y -= sin(data->engine->player->direction_angle.x) * 2;
	}
}