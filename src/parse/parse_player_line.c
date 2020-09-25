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
	safe_call_parse_ptr(str = parse_float(str, &position.x),
			"Player\'s position is not correct.", data, parse);
	safe_call_parse_ptr(str = skip_to("y", str),
			"Player\'s position is not correct.", data, parse);
	safe_call_parse_ptr(str = parse_float(str, &position.y),
			"Player\'s position is not correct.", data, parse);
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
	safe_call_parse_ptr(str = parse_float(str, &direction.x),
				"Parse float error. Player\'s direction", data, parse);
	safe_call_parse_ptr(str = skip_to("z", str),
				  "Player\'s direction is not correct.", data, parse);
	safe_call_parse_ptr(str = parse_float(str, &direction.y),
						"Parse float error. Player\'s direction", data, parse);
	if (*str)
		safe_call_parse_int(-1,
				"Extra characters: player\'s direction.", data, parse);
}

static void		parse_move_floats(t_parse **parse, t_move *move, t_data *data)
{
	int					i;
	static t_vec3		flags = {-1.0, -1.0, -1.0};
	char				*str;

	safe_call_parse_ptr(str = skip_to("move", (*parse)->cur_str),
		"player\'s move parsing error.", data, parse);
	i = 0;
	while (i < 3 && *str)
	{
		if (*str == 'k')
		{
			safe_call_parse_ptr(str = skip_to("knees", str),
				"Player\'s move parsing error.", data, parse);
			safe_call_parse_ptr(str = parse_float(str, &move->knees),
				"Float parse error, player\'s move.", data, parse);
			flags.x = 1;
		}
		else if (*str == 'd')
		{
			safe_call_parse_ptr(str = skip_to("ducking", str),
				"player\'s move parsing error.", data, parse);
			safe_call_parse_ptr(str = parse_float(str, &move->ducking),
				"Float parse error, player\'s move.", data, parse);
			flags.y = 1;
		}
		else if (*str == 'e')
		{
			safe_call_parse_ptr(str = skip_to("eyes", str),
				"player\'s move parsing error.", data, parse);
			safe_call_parse_ptr(str = parse_float(str, &move->eyes),
				"Float parse error, player\'s move.", data, parse);
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
	if (data->engine->player->move == NULL)
		data->engine->player->move =
		(t_move *)safe_call_parse_ptr(ft_memalloc(sizeof(t_move)),
		"Malloc crashed in \"./src/parse/parse_player_line.c\"", data, parse);
	parse_move_floats(parse, data->engine->player->move, data);
}

static void		parse_fov(t_parse **parse, t_data *data)
{
	char	*str;

	safe_call_parse_ptr(str = skip_to("fov", (*parse)->cur_str), "Fov not fov: "
				"./src/parse/parse_player_line.c.", data, parse);
	safe_call_parse_ptr(parse_float(str, &data->engine->player->fov), "Float parsing error. Player FOV.",
					data, parse);
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
