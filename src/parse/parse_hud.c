//
// Created by Hugor Chau on 9/22/20.
//
#include "../../Include/map_struct.h"

static void		parse_weapon_by_name(char *name, t_parse **parse, t_data *data)
{
	char		box;
	int			i;
	t_weapon	*weapon;

	i = 0;
	while (name[i] && (name[i] != ' '
		&& name[i] != '\t' && name[i] != '\r'))
		i++;
	box = name[i];
	name[i] = '\0';
	weapon = find_weapon_by_name(name, data);
	name[i] = box;
	while (name[i] && (name[i] != ' '
		   && name[i] != '\t' && name[i] != '\r'))
		i++;
	safe_call_parse_ptr(name = skip_to("bullets", name + i),
			   "Bullets not bullets: weapon parse error.", data, parse);
	weapon->bullets = ft_atoi(name);
	weapon->i_have_it = TRUE;
}

//TODO: check atoi!
static void	parse_hud_main(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	str = skip_to("", str);
	if (*str == 'w')
	{
		safe_call_parse_ptr(str = skip_to("weapon", str),
			"Weapon not weapon: check hud, please.", data, parse);
		parse_weapon_by_name(str, parse, data);
	}
	else if (*str == 'h')
	{
		safe_call_parse_ptr(str = skip_to("health", str),
			"Health not health: check hud, please.", data, parse);
//		if ()
		data->engine->player->hud->health = ft_atoi(str);
	}
	else if (*str == 'a')
	{
		safe_call_parse_ptr(str = skip_to("armor", str),
			"Armor not armor: check hud, please.", data, parse);
		data->engine->player->hud->armor = ft_atoi(str);
	}
	else
		safe_call_parse_int(-1, "Parsing hud error, "
			"\"./src/parse/parse_hud.c\"", data, parse);
}

void		parse_hud(t_parse **parse, t_data *data)
{

	safe_call_parse_int(check_line("hud", (*parse)->cur_str),
						"Hud not walls: check \"./src/parse/parse_hud.c\".", data, parse);
	parse_struct(parse, data, parse_hud_main, "t_hud");
	safe_call_parse_int(check_line("t_hud", (*parse)->cur_str),
						"Check for error in "
						"\'hud\' data. There should "
						"be closing flag \'t_hud\'.", data, parse);
	ft_strdel(&(*parse)->cur_str);
	(*parse)->player_hud_parsed++;
}
