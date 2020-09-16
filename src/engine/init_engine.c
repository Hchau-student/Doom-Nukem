//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	init_engine(t_data *data, t_engine *engine)
{
	engine->sdl = data->sdl;
	engine->textures = data->textures;
	//	data->condition = &game;
//	ft_putendl("POEHALI!");
}//do we need to validate all this stuff or it will come from editor?
