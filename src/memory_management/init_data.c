#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
#include "../../SDL/include/SDL.h"

/*
**		it's absolute because of instruments->leaks
*/

#define ABSOLUTE_PATH_TEXTURES	"/Users/hchau/Downloads/" \
		"Doom-Nukem-structure/extra_src/parse_textures.txt"

void	put_bitmap(t_data *data) {
	t_display_hud	*hud;

	hud = ((t_engine *)data->engine)->player->hud;
	draw_hud(hud, data);
	safe_call_int(SDL_UpdateTexture(
			data->sdl->tex,
			data->sdl->rect,
			data->sdl->color_buffer,
			SCREEN_WIDTH * sizeof(uint32_t)
			), "Texture update failed", data);
	safe_call_int(SDL_SetRenderDrawColor( data->sdl->rend , 0, 0, 0, SDL_ALPHA_OPAQUE ), "Can't clear render.", data);
	safe_call_int(SDL_RenderClear( data->sdl->rend  ), "Can't clear render.", data);
	safe_call_int(SDL_RenderCopy( data->sdl->rend , data->sdl->tex, NULL, NULL ), "Can't clear render.", data);
	SDL_RenderPresent( data->sdl->rend );
	hud->state++;
	if (hud->state > 4)
		hud->state = 0;
}

void	update_texture(t_data *data)
{//сделать методом?
//	clear_bitmap(data);
	put_bitmap(data);
}

void			menu_condition(t_data *data)
{
	update_texture(data);
}

void			init_main_actions(t_data *data)
{
	t_main_actions		*actions;

	actions = safe_call_ptr(malloc(sizeof(t_main_actions)),
			"Malloc crashed in function: init_main_actions", data);
	actions->key_event = &menu_key_event;
	actions->mouse_event = &menu_mouse_event;
	actions->condition = &menu_condition;
	data->go_to = actions;
}

void			init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->sdl = (t_sdl *)safe_call_ptr(ft_memalloc(sizeof(t_sdl)),
			"Malloc crashed in function: init_data", data);
	init_sdl(data, WIN_TITLE);
	data->textures = init_textures(ABSOLUTE_PATH_TEXTURES, data);
	init_main_actions(data);
}

void			remove_data(t_data *data)
{
	remove_sdl(&data->sdl);
	remove_textures(data);
	remove_engine(data);
	ft_memdel((void **)&data->go_to);
	exit(0);
}
