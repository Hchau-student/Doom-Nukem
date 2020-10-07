#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
#include "../../SDL/include/SDL.h"

/*
**		it's absolute because of instruments->leaks
*/

#define ABSOLUTE_PATH_TEXTURES	"/Users/hchau/Downloads/" \
		"Doom-Nukem-structure/extra_src/parse_textures.txt"

//
//void			menu_condition(t_data *data)
//{
//	update_texture(data);
//}

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
