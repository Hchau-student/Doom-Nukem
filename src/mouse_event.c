//
// Created by Hugor Chau on 10/8/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

void	mouse_event(SDL_Event *event, t_data *data)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		data->sdl->mouse.is_moved = TRUE;
	}
	data->sdl->mouse.x = event->motion.x;
	data->sdl->mouse.y = event->motion.y;
//	data->sdl->mouse.is_pressed = FALSE;
	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			data->sdl->mouse.is_pressed = TRUE;
		}
	}
	if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y > 0)
			data->sdl->mouse.is_scrolled_in = TRUE;
		else if (event->wheel.y < 0)
			data->sdl->mouse.is_scrolled_out = TRUE;
	}
	else
	{
		data->sdl->mouse.is_scrolled_in = FALSE;
		data->sdl->mouse.is_scrolled_out = FALSE;
	}
	if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			data->sdl->mouse.is_pressed = FALSE;
		}
	}
}
