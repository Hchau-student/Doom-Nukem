//
// Created by Hugor Chau on 9/21/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		init_whole_health(t_data *data, t_texture **text, char *name)
{
	char		*normal;
	char		*kill;
	char		*hurt;
	char		*left;
	char		*right;

	normal = ft_strjoin(name, "_normal");
	kill = ft_strjoin(name, "_kill");
	hurt = ft_strjoin(name, "_hurt");
	left = ft_strjoin(name, "_left");
	right = ft_strjoin(name, "_right");
	(text)[PLAYER_NORMAL] = find_texture_by_name(normal, data);
	(text)[PLAYER_KILL] = find_texture_by_name(kill, data);
	(text)[PLAYER_HURT] = find_texture_by_name(hurt, data);
	(text)[PLAYER_LEFT] = find_texture_by_name(left, data);
	(text)[PLAYER_RIGHT] = find_texture_by_name(right, data);
	ft_strdel(&normal);
	ft_strdel(&kill);
	ft_strdel(&hurt);
	ft_strdel(&left);
	ft_strdel(&right);
}

t_display_hud	*init_hud(t_data *data)
{
	t_display_hud	*hud;

	hud = ft_memalloc(sizeof(t_display_hud));
	hud->weapon = init_weapon(data);
	init_whole_health(data, (t_texture **)hud->player_texture[HEALTH_20], "health_20");
	init_whole_health(data, (t_texture **)hud->player_texture[HEALTH_40], "health_40");
	init_whole_health(data, (t_texture **)hud->player_texture[HEALTH_60], "health_60");
	init_whole_health(data, (t_texture **)hud->player_texture[HEALTH_80], "health_80");
	init_whole_health(data, (t_texture **)hud->player_texture[HEALTH_100], "health_100");
	hud->health = 100;
	hud->armor = 0;
	hud->state = PLAYER_NORMAL;
	return hud;
}

void		remove_weapon(t_weapon **weapon)
{
	t_weapon	*cur_w;
	t_weapon	*tmp;

	if (!weapon)
		return;
	tmp = *weapon;
	cur_w = tmp;
	tmp->prev->next = NULL;
	while (tmp)
	{
		tmp = cur_w->next;
		cur_w->next = NULL;
		cur_w->prev = NULL;
		ft_memdel((void **)&cur_w);
		cur_w = tmp;
	}
}

void		remove_hud(t_display_hud **hud)
{
	remove_weapon(&((*hud)->weapon));
	ft_memdel((void **)hud);
}
