//
// Created by Hugor Chau on 9/18/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = ft_memalloc(sizeof(t_player));
	player->hud = init_hud(data);
	return (player);
}

void		remove_player(t_player **player)
{
	if (!*player)
		return;
	remove_hud(&(*player)->hud);
	ft_memdel((void **)(*player)->move);
	ft_memdel((void **)(player));
}
