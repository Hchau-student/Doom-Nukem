//
// Created by Hugor Chau on 9/23/20.
//

#include "../../Include/map_struct.h"

t_weapon		*find_weapon_by_name(char *name, t_data *data)
{
	t_weapon	*weapon;
	int			i;

	i = 0;
	weapon = data->engine->player->hud->weapon;
	while (i < MAX_WEAPONS)
	{
		if ((check_line(name, weapon->name)) == 0)
			break ;
		weapon = weapon->next;
		i++;
	}
	safe_call_int(check_line(name, weapon->name),
		"Didn't find weapon by name. Check data.", data);
	return (weapon);
}
