//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		remove_object(void *obj, size_t size)
{
	size = 0;
	if (((t_obj *)obj)->type == HEALTH_OBJ)
		ft_memdel((void **)&((t_health_obj *)obj)->place);
}

static void		remove_walls(t_sector_render *remove)
{
	t_wall		*tmp;
	int			i;

	i = 0;
	while (i < remove->walls_count)
//	while ((remove)->walls)
	{
		tmp = (remove)->walls->next;
		ft_memdel((void **)&(remove->walls));
		(remove)->walls = tmp;
		i++;
	}
}

static void		remove_sectors(t_engine **engine)
{
	t_engine	*tmp;
	uint32_t	i;

	i = 0;
	tmp = *engine;
	while (i < tmp->sectors_count)
	{
		remove_walls((tmp->sectors[i].render));
		ft_memdel((void **)&tmp->sectors[i].render);
		ft_lstdel(&tmp->sectors[i].objects, &remove_object);
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
		ft_memdel((void **)&data->engine->minimap);
	}
	ft_memdel((void **)&data->engine);
}

void	init_minimap(t_data *data)
{
	uint32_t		i;
	uint32_t		max;
	t_texture		*touch;

	i = 0;
	data->engine->minimap = ft_memalloc(sizeof(t_minimap));
	data->engine->minimap->texture = data->sdl->layers->minimap;
	data->engine->minimap->player_icon = find_texture_by_name("player_icon", data);
	data->engine->minimap->background = find_texture_by_name("minimap", data);
	max = (data->engine->minimap->background->height) * (data->engine->minimap->background->width);
	touch = data->engine->minimap->background;
	while (i < max)
	{
		touch->bit_map[i] -= 0x40000000;
		i++;
	}
}

void	init_engine(t_data *data)
{
	t_engine		*engine;

	data->engine = (t_engine *)safe_call_ptr(ft_memalloc(sizeof(t_engine)),
				"Malloc crashed in function: init_data", data);
	engine = data->engine;
	engine->sdl = data->sdl;
	engine->textures = data->textures;
	engine->quality = 2;
//	engine->minimap = (t_texture *)safe_call_ptr(ft_memalloc(sizeof(t_texture)),
//						"Malloc crashed: engine init", data);
	init_minimap(data);
	engine->player = init_player(data);
}
