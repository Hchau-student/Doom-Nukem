//
// Created by Hugor Chau on 9/16/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	engine_key_event(SDL_Event *event, t_data *data)
{
	if (event->key.keysym.sym == SDLK_RIGHT)
		data->sdl->key_pressed[RIGHT_ARROW] = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_LEFT)
		data->sdl->key_pressed[LEFT_ARROW] = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_w)
		data->sdl->key_pressed['W'] = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_s)
		data->sdl->key_pressed['S'] = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_a)
		data->sdl->key_pressed['A'] = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_d)
		data->sdl->key_pressed['D'] = event->type == SDL_KEYDOWN;
}