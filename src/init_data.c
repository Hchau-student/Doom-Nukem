#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"
#include "../SDL/include/SDL.h"

void			init_main_actions(t_data *data)
{
	t_main_actions		actions;

	actions.key_event = &menu_key_event;
	actions.mouse_event = &menu_mouse_event;
	data->go_to = &actions;
}

void			init_data(t_data *data)
{
	data->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_sdl(data, WIN_TITLE);
//	data->textures = init_textures((char **){NULL}, 0, data);
//	data->engine = (t_engine *)malloc(sizeof(t_engine));
//	init_main_actions(data);
}

void			remove_data(t_data *data)
{
	remove_sdl(&data->sdl);
	remove_textures(data);
//	remove_engine();
	exit(0);
}
