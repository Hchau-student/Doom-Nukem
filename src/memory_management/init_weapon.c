//
// Created by Hugor Chau on 9/18/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		standard_shoot(struct s_shoot *shoot, void *obj)
{
	t_shoot		*s;
	t_obj		*o;

	s = shoot;
	o = obj;
}

static t_shoot		*init_shoot(t_data *data, char *shoot_name)
{
	t_shoot		*shoot;
	char		*reminder_0;
	char		*reminder_1;

	reminder_0 = ft_strjoin(shoot_name, "_reminder_0");
	reminder_1 = ft_strjoin(shoot_name, "_reminder_1");
	shoot = (t_shoot *)safe_call_ptr(malloc(sizeof(t_shoot)), "Crashed malloc: shoot", data);
	shoot->hit = &standard_shoot;
	shoot->texture = find_texture_by_name(shoot_name, data);
	shoot->remainder[REMAINDER_SHOOT_0] = find_texture_by_name(shoot_name, data);
	shoot->remainder[REMAINDER_SHOOT_1] = find_texture_by_name(shoot_name, data);
	ft_strdel(&reminder_0);
	ft_strdel(&reminder_1);
	return (shoot);
}

static t_weapon		*init_one_weapon(t_data *data, char *weapon_name)
{
	t_weapon	*weapon;
	char		*frame_0;
	char		*frame_1;
	char		*shoot_name;

	frame_0 = ft_strjoin(weapon_name, "_frame_0");
	frame_1 = ft_strjoin(weapon_name, "_frame_1");
	shoot_name = ft_strjoin(weapon_name, "_shoot");
	weapon = (t_weapon *)safe_call_ptr(malloc(sizeof(t_weapon)), "Crashed malloc: weapon", data);
	weapon->name = ft_strdup(weapon_name);
	weapon->bullets = 0;
	weapon->bullets_max = 200;
	weapon->i_have_it = FALSE;
	weapon->frame = WEAPON_0_FRAME;
	weapon->shoot = init_shoot(data, shoot_name);
	weapon->texture[WEAPON_0_FRAME] = find_texture_by_name(frame_0, data);
	weapon->texture[WEAPON_1_FRAME] = find_texture_by_name(frame_1, data);
	ft_strdel(&frame_0);
	ft_strdel(&frame_1);
	ft_strdel(&shoot_name);
	return (weapon);
}

t_weapon			*init_weapon(t_data *data)
{
	t_weapon	*weapon;
	t_weapon	*first;
	int			i;

	i = 0;
	weapon = init_one_weapon(data,"carabine");
	first = weapon;
	while (i < MAX_WEAPONS)
	{
		weapon->next = init_one_weapon(data,"carabine");
		weapon->next->prev = weapon;
		i++;
		weapon = weapon->next;
	}
	first->prev = weapon;
	weapon->next = first;
	return (first);
}
