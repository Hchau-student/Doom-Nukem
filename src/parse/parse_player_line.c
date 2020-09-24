//
// Created by Hugor Chau on 9/22/20.
//
#include "../../Include/map_struct.h"

static void		parse_position(t_parse **parse, t_data *data)
{
	t_vec2		position;
	char		*str;

	str = (*parse)->cur_str;
	safe_call_parse_ptr(str = skip_to("position", str),
			"Player\'s position is not correct.", data, parse);
	position = data->engine->player->position;
	safe_call_parse_ptr(str = skip_to("x", str),
			"Player\'s position is not correct.", data, parse);
	str = parse_float(str, &position.x);
	safe_call_parse_ptr(str = skip_to("y", str),
			"Player\'s position is not correct.", data, parse);
	str = parse_float(str, &position.y);
	if (*str)
		safe_call_parse_int(-1,
				"Extra characters: player\'s position.", data, parse);
}

static void		parse_direction(t_parse **parse, t_data *data)
{
	t_vec2		direction;
	char		*str;

	str = (*parse)->cur_str;
	safe_call_parse_ptr(str = skip_to("direction", str),
				  "Player\'s direction is not correct.", data, parse);
	direction = data->engine->player->position;
	safe_call_parse_ptr(str = skip_to("x", str),
				  "Player\'s direction is not correct.", data, parse);
	str = parse_float(str, &direction.x);
	safe_call_parse_ptr(str = skip_to("z", str),
				  "Player\'s direction is not correct.", data, parse);
	str = parse_float(str, &direction.y);
	if (*str)
		safe_call_parse_int(-1,
				"Extra characters: player\'s position.", data, parse);
}

static void		parse_move_floats(t_parse **parse, t_move *move, t_data *data)
{
	int					i;
	static t_vec3		flags = {-1.0, -1.0, -1.0};
	char				*str;

	str = skip_to("move", (*parse)->cur_str);
	i = 0;
	while (i < 3 && *str)
	{
		if (*str == 'k')
		{
			str = skip_to("knees", str);
			str = parse_float(str, &move->knees);
			flags.x = 1;
		}
		else if (*str == 'd')
		{
			str = skip_to("ducking", str);
			str = parse_float(str, &move->ducking);
			flags.y = 1;
		}
		else if (*str == 'e')
		{
			str = skip_to("eyes", str);
			str = parse_float(str, &move->eyes);
			flags.z = 1;
		}
		i++;
	}
	if (flags.x < 0 || flags.y < 0 || flags.z < 0)
		safe_call_parse_int(-1, "Parsing error: "
				"\"./src/parse/parse_player_line\".", data, parse);
}

static void		parse_move(t_parse **parse, t_data *data)
{
	t_move		*move;

	if (data->engine->player->move == NULL)
		data->engine->player->move =
		safe_call_parse_ptr(ft_memalloc(sizeof(t_move)),
		"Malloc crashed in \"./src/parse/parse_player_line.c\"", data, parse);
	move = data->engine->player->move;
	parse_move_floats(parse, move, data);
}

static void		parse_fov(t_parse **parse, t_data *data)
{
	char	*str;

	safe_call_parse_ptr(str = skip_to("fov", (*parse)->cur_str), "Fov not fov: "
				"./src/parse/parse_player_line.c.", data, parse);
	parse_float(str, &data->engine->player->fov);
}

void			parse_player_line(t_parse **parse, t_data *data)
{
	char	*str;

	str = (*parse)->cur_str;
	while (*str)
	{
		if (*str == 'h')
			return (parse_hud(parse, data));
		else if (*str == 'p')
			return (parse_position(parse, data));
		else if (*str == 'd')
			return (parse_direction(parse, data));
		else if (*str == 'm')
			return (parse_move(parse, data));
		else if (*str == 'f')
			return (parse_fov(parse, data));
		else if ((*str == ' ' || *str == '\t'
			 || *str == '\r') || (*str == '{' || *str == '}'))
			str++;
		else
			safe_call_parse_int(-1, "Hey! "
				"Check your map, player is not ok!", data, parse);
	}
}
