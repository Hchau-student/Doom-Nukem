//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	game(t_data *data)
{

}

void			remove_engine(t_data *data)
{
	t_engine	*engine;

	if (!data)
		return;
	engine = data->engine;
	if (engine)
		remove_player(&((t_engine *)data->engine)->player);
	ft_memdel((void **)&data->engine);
}

void	init_engine(t_data *data)
{
	t_engine		*engine;

	data->engine = (t_engine *)safe_call_ptr(ft_memalloc(sizeof(t_engine)),
											 "Malloc crashed in function: init_data", data);
	engine = data->engine;
	engine->sdl = data->sdl;
	engine->textures = data->textures;
	engine->player = init_player(data);
}
