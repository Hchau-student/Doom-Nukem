//
// Created by Hugor Chau on 9/21/20.
//

#include "../../Include/map_struct.h"

static void		parse_type(char *str, t_sector *sector, t_data *data)
{
	if (!check_line("t_walls", str) ||
			!check_line("t_objects", str))
		return ;
	safe_call_ptr((str = skip_to("type", str)),
				"Parsing error: check in \"parse_type\","
				"\"./src/parse/parse_line.c\".", data);
	if (check_line("water", str))
		sector->type = SEC_WATER;
	else if (check_line("normal", str))
		sector->type = SEC_NORMAL;
	else if (check_line("glassy", str))
		sector->type = SEC_GLASSY;
	else
		safe_call_int(-1, "Parsing error: parse_type,"
					"./src/parse/parse_line.c", data);
}

static void			parse_light(char *str, t_sector *sector, t_data *data)
{
	safe_call_ptr((str = skip_to("light", str)),
				"Parsing error: check in \"parse_light\","
				"\"./src/parse/parse_line.c\".", data);
	safe_call_ptr((str = skip_to("0x", str)),
				"Parsing error: check in \"parse_light\","
				"\"./src/parse/parse_line.c\".", data);
	safe_call_int(parse_num(str, &sector->render->light),
			"0x0 num error.", data);
}

static void			parse_floor(char *str, t_sector *sector, t_data *data)
{
	safe_call_ptr((str = skip_to("floor", str)),
		"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data);
	if (*str >= '0' && *str <= '9')
	{
		safe_call_ptr((str = parse_float(str, &sector->render->floor_height)),
					"Parsing error: check in \"parse_floor\","
					"\"./src/parse/parse_line.c\".", data);
		sector->render->textures[FLOOR_TEXT] =
				find_texture_by_name(str, data);
	}
	else
	{
		safe_call_int(-1,
				"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data);
	}
}

/*
**		yeap, I do love typing;
**		it's comfortable for calling functions -
**		I guess it would be easier to read some
**		similar function calls
*/

static void			parse_ceiling(char *str, t_sector *sector, t_data *data)
{
	safe_call_ptr((str = skip_to("ceiling", str)),
				"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data);
	if (*str >= '0' && *str <= '9')
	{
		safe_call_ptr((str = parse_float(str, &sector->render->floor_height)),
					"Parsing error: check in \"parse_floor\","
					"\"./src/parse/parse_line.c\".", data);
		sector->render->textures[CEILING_TEXT] =
				find_texture_by_name(str, data);
	}
	else
	{
		safe_call_int(-1,
					"Parsing error: check in \"parse_ceiling\","
					"\"./src/parse/parse_line.c\".", data);
	}
}

void			parse_line(char *str, int fd, t_sector *sector, t_data *data)
{
	while (*str)
	{
		if (*str == 'w')
			return (parse_wall(str, fd, sector, data));
		if (*str == 'l')
			return (parse_light(str, sector, data));
		if (*str == 't')
			return (parse_type(str, sector, data));
		if (*str == 'f')
			return (parse_floor(str, sector, data));
		if (*str == 'c')
			return (parse_ceiling(str, sector, data));
		if (*str == 'o')
			return (parse_objects(str, fd, sector, data));
		if ((*str == ' ' || *str == '\t'
		|| *str == '\r') || (*str == '{' || *str == '}'))
			;
		else
			safe_call_int(-1, "Hey! Check your map!", data);
		str++;
	}
}
