//
// Created by Hugor Chau on 9/27/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void		init_single_layer(t_texture **layer, t_data *data)
{
	(*layer) = (t_texture *)safe_call_ptr(malloc(sizeof(t_texture)),
		"Malloc crashed at \"./src/memory_management/init_window_layer.c\" "
		"in \"init_single_layer\" function.", data);
	(*layer)->bit_map = (uint32_t *)safe_call_ptr(malloc(((SCREEN_HEIGHT) *
		(SCREEN_WIDTH)) * sizeof(uint32_t)),
		"Malloc crashed at \"./src/memory_management/init_window_layer.c\" "
		"in \"init_layers\" function.", data);
	(*layer)->width = SCREEN_WIDTH;
	(*layer)->height = SCREEN_HEIGHT;
}

void		init_sdl_layers(t_data *data)
{
	data->sdl->layers = safe_call_ptr(ft_memalloc(sizeof(t_layers)),
		"Malloc crashed at \"./src/memory_management/init_window_layer.c\" "
		"in \"init_layers\" function.", data);
	init_single_layer(&data->sdl->layers->minimap, data);
	init_single_layer(&data->sdl->layers->hud, data);
	init_single_layer(&data->sdl->layers->draw_3d, data);
	init_single_layer(&data->sdl->layers->menu, data);
	init_single_layer(&data->sdl->layers->level_editor, data);
}

void		remove_layers(t_layers **layers)
{
	ft_memdel((void **) &(*layers)->hud->bit_map);
	ft_memdel((void **) &(*layers)->hud);
	ft_memdel((void **) &(*layers)->minimap->bit_map);
	ft_memdel((void **) &(*layers)->minimap);
	ft_memdel((void **) layers);
}
