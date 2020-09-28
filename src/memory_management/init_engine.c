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

static void		remove_walls(t_sector_render *remove)
{
	t_twlist	*tmp;

	while (remove->walls)
	{
		tmp = remove->walls->next;
		ft_memdel(&remove->walls->content);
		ft_memdel(&remove->walls);
		remove->walls = tmp;
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
		remove_walls(&tmp->sectors[i].render);
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

void	create_minimap(t_data *data)
{
//	int			i;
//	int			j;
	t_texture	*minimap;

	minimap = (ft_memalloc(sizeof(t_texture)));
//	minimap->height = MINIMAP_H;
//	minimap->width = MINIMAP_W;
	minimap->height = SCREEN_HEIGHT;
	minimap->width = SCREEN_WIDTH;
	minimap->bit_map =
			(ft_memalloc(sizeof(uint32_t) * minimap->height * minimap->width));
	data->engine->minimap = minimap;
}

void	init_engine(t_data *data)
{
	t_engine		*engine;

	data->engine = (t_engine *)safe_call_ptr(ft_memalloc(sizeof(t_engine)),
				"Malloc crashed in function: init_data", data);
	engine = data->engine;
	engine->sdl = data->sdl;
	engine->textures = data->textures;
//	engine->minimap = (t_texture *)safe_call_ptr(ft_memalloc(sizeof(t_texture)),
//						"Malloc crashed: engine init", data);
	create_minimap(data);
	engine->player = init_player(data);
}
