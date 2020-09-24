//
// Created by Hugor Chau on 9/21/20.
//

#include "../../Include/map_struct.h"

static void		parse_type(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	if (!check_line("t_walls", str) ||
			!check_line("t_objects", str))
		return ;
	safe_call_parse_ptr((str = skip_to("type", str)),
				"Parsing error: check in \"parse_type\","
				"\"./src/parse/parse_line.c\".", data, parse);
	if (check_line("water", str))
		(*parse)->cur_sector->type = SEC_WATER;
	else if (check_line("normal", str))
		(*parse)->cur_sector->type = SEC_NORMAL;
	else if (check_line("glassy", str))
		(*parse)->cur_sector->type = SEC_GLASSY;
	else
		safe_call_parse_int(-1, "Parsing error: parse_type,"
					"./src/parse/parse_line.c", data, parse);
}

static void			parse_light(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	safe_call_parse_ptr((str = skip_to("light", str)),
				"Parsing error: check in \"parse_light\","
				"\"./src/parse/parse_line.c\".", data, parse);
	safe_call_parse_ptr((str = skip_to("0x", str)),
				"Parsing error: check in \"parse_light\","
				"\"./src/parse/parse_line.c\".", data, parse);
	safe_call_parse_int(parse_num(str, &(*parse)->cur_sector->render->light),
			"0x0 num error.", data, parse);
}

static void			parse_floor(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	safe_call_parse_ptr((str = skip_to("floor", str)),
		"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data, parse);
	if (*str >= '0' && *str <= '9')
	{
		safe_call_parse_ptr((str = parse_float(str, &(*parse)->cur_sector->render->floor_height)),
					"Parsing error: check in \"parse_floor\","
					"\"./src/parse/parse_line.c\".", data, parse);
		(*parse)->cur_sector->render->textures[FLOOR_TEXT] =
				find_texture_by_name(str, data);
	}
	else
	{
		safe_call_parse_int(-1,
				"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data, parse);
	}
}

/*
**		yeap, I do love typing;
**		it's comfortable for calling functions -
**		I guess it would be easier to read some
**		similar function calls
*/

static void			parse_ceiling(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	safe_call_parse_ptr((str = skip_to("ceiling", str)),
				"Parsing error: check in \"parse_floor\","
				"\"./src/parse/parse_line.c\".", data, parse);
	if (*str >= '0' && *str <= '9')
	{
		safe_call_parse_ptr((str = parse_float(str, &(*parse)->cur_sector->render->floor_height)),
					"Parsing error: check in \"parse_floor\","
					"\"./src/parse/parse_line.c\".", data, parse);
		(*parse)->cur_sector->render->textures[CEILING_TEXT] =
				find_texture_by_name(str, data);
	}
	else
	{
		safe_call_parse_int(-1,
			"Parsing error: check in \"parse_ceiling\","
			"\"./src/parse/parse_line.c\".", data, parse);
	}
}

void			parse_line_sector(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	while (*str)
	{
		if (*str == 'w')
			return (parse_wall(parse, data));
		else if (*str == 'l')
			return (parse_light(parse, data));
		else if (*str == 't')
			return (parse_type(parse, data));
		else if (*str == 'f')
			return (parse_floor(parse, data));
		else if (*str == 'c')
			return (parse_ceiling(parse, data));
		else if (*str == 'o')
			return (parse_objects(parse, data));
		else if ((*str == ' ' || *str == '\t'
		|| *str == '\r') || (*str == '{' || *str == '}'))
			str++;
		else
			safe_call_int(-1, "Hey! Check your map!", data);
	}
}
