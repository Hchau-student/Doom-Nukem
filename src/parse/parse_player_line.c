//
// Created by Hugor Chau on 9/22/20.
//
#include "../../Include/map_struct.h"

static void		parse_position(char *str, t_data *data)
{
	t_vec2		position;

	safe_call_ptr(str = skip_to("position", str),
			"Player\'s position is not correct.", data);
	position = data->engine->player->position;
	safe_call_ptr(str = skip_to("x", str),
			"Player\'s position is not correct.", data);
	str = parse_float(str, &position.x);
	safe_call_ptr(str = skip_to("y", str),
			"Player\'s position is not correct.", data);
	str = parse_float(str, &position.y);
	if (*str)
		safe_call_int(-1,
				"Extra characters: player\'s position.", data);
}

static void		parse_direction(char *str, t_data *data)
{
	t_vec2		direction;

	safe_call_ptr(str = skip_to("direction", str),
				  "Player\'s direction is not correct.", data);
	direction = data->engine->player->position;
	safe_call_ptr(str = skip_to("x", str),
				  "Player\'s direction is not correct.", data);
	str = parse_float(str, &direction.x);
	safe_call_ptr(str = skip_to("z", str),
				  "Player\'s direction is not correct.", data);
	str = parse_float(str, &direction.y);
	if (*str)
		safe_call_int(-1,
				"Extra characters: player\'s position.", data);
}

static void		parse_move_floats(char *str, t_move *move, t_data *data)
{
	int					i;
	static t_vec3		flags = {-1.0, -1.0, -1.0};

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
		safe_call_int(-1, "Parsing error: "
				"\"./src/parse/parse_player_line\".", data);
}

static void		parse_move(char *str, t_data *data)
{
	t_move		*move;

	if (data->engine->player->move == NULL)
		data->engine->player->move =
		safe_call_ptr(ft_memalloc(sizeof(t_move)),
		"Malloc crashed in \"./src/parse/parse_player_line.c\"", data);
	move = data->engine->player->move;
	str = skip_to("move", str);
	parse_move_floats(str, move, data);
}

static void		parse_fov(char *str, t_data *data)
{

}

void			parse_player_line(char *str, int fd, t_data *data)
{
	while (*str)
	{
		if (*str == 'h')
			return (parse_hud(str, fd, data));
		if (*str == 'p')
			return (parse_position(str, data));
		if (*str == 'd')
			return (parse_direction(str, data));
		if (*str == 'm')
			return (parse_move(str, data));
		if (*str == 'f')
			return (parse_fov(str, data));
		if ((*str == ' ' || *str == '\t'
			 || *str == '\r') || (*str == '{' || *str == '}'))
			;
		else
			safe_call_int(-1, "Hey! "
				"Check your map, player is not ok!", data);
		str++;
	}
}
