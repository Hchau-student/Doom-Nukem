//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		remove_object(void *obj, size_t size)
{
	if (((t_obj *)obj)->type == HEALTH_OBJ)
		ft_memdel((void **)&((t_health_obj *)obj)->place);
}

static void		remove_wall(void *wall, size_t size)
{
	//
}

static void		remove_sectors(t_engine **engine)
{
	t_engine	*tmp;
	uint32_t	i;

	i = 0;
	tmp = *engine;
	while (i < tmp->sectors_count)
	{
//		ft_twlstdel(&tmp->sectors[i].render->walls, &remove_object);
		ft_memdel((void **)&tmp->sectors[i].render);
		ft_lstdel(&tmp->sectors[i].objects, &remove_wall);
		i++;
	}
	ft_memdel((void **)&(*engine)->sectors);
}

void			remove_engine(t_data *data)
{
	t_engine	*engine;

	if (!data)
		return;
	engine = data->engine;
	if (engine)
	{
		remove_sectors(&data->engine);
		remove_player(&data->engine->player);
	}
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
