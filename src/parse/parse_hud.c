//
// Created by Hugor Chau on 9/22/20.
//
#include "../../Include/map_struct.h"

static void		check_error(char *line, char flag, char brackets, t_data *data)
{
	if (flag == -1)
		safe_call_int(-1, "Read error: gnl returned -1.", data);
	safe_call_int(check_line("t_hud", line),
				  "Check for error in \'t_walls\' data. There should "
				  "be closing flag \'t_walls\'.", data);
	safe_call_int(brackets, "Sector parse error: "
							"check for brackets.", data);
}

static void		parse_weapon_by_name(char *name, t_data *data)
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
	safe_call_ptr(name = skip_to("bullets", name + i),
			   "Bullets not bullets: weapon parse error.", data);
	weapon->bullets = ft_atoi(name);
	weapon->i_have_it = TRUE;
}

static void	parse_hud_main(char *str, int fd, t_data *data)
{
	str = skip_to("", str);
	if (*str == 'w')
	{
		safe_call_ptr(str = skip_to("weapon", str),
			"Weapon not weapon: check hud, please.", data);
		parse_weapon_by_name(str, data);
	}
	else if (*str == 'h')
	{
		safe_call_ptr(str = skip_to("health", str),
			"Health not health: check hud, please.", data);
		data->engine->player->hud->health = ft_atoi(str);
	}
	else if (*str == 'a')
	{
		safe_call_ptr(str = skip_to("armor", str),
			"Armor not armor: check hud, please.", data);
		data->engine->player->hud->armor = ft_atoi(str);
	}
	else
		safe_call_int(-1, "Parsing hud error, "
			"\"./src/parse/parse_hud.c\"", data);
}

void		parse_hud(char *str, int fd, t_data *data)
{
	char				*line;
	char				count_brackets;
	char				flag;

	count_brackets = 0;
	safe_call_int(check_line("hud", str),
				  "Hud not walls: check \"./src/parse/parse_hud.c\".", data);
	while (((flag = get_next_line(fd, &line)) == 1)
		   && (check_line("t_hud", line)))
	{
		ft_putendl(line);
		if (!check_line("{", line))
			count_brackets++;
		else if (!check_line("}", line))
			count_brackets--;
		else
		{
			parse_hud_main(line, fd, data);
		}
		ft_strdel(&line);
	}
	check_error(line, flag, count_brackets, data);
}
