//
// Created by Hugor Chau on 9/22/20.
//
#include "../../Include/map_struct.h"
#include <stdio.h>

static void		get_wall_type(char *str, t_wall *wall, t_data *data)
{
	wall->type = -1;
	safe_call_ptr(str = skip_to("type", str),
				  "Check wall type.", data);
	wall->type = !(check_line("normal", str)) ? WALL : wall->type;
	wall->type = !(check_line("glassy", str)) ? GLASSY : wall->type;
	wall->type = !(check_line("portal", str)) ? PORTAL : wall->type;
	wall->type = !(check_line("door", str)) ? DOOR : wall->type;
	wall->type = !(check_line("window", str)) ? WINDOW : wall->type;
	if (wall->type == -1)
		safe_call_int(-1, "Check wall type.", data);
}

static void		get_wall_coordinates(char *str, t_wall *wall, t_data *data)
{
	static char		error_message[100] = "Check your coordinates for wall.\0";
	t_vec3			box;

	while (*str && (*str == ' ' || (*str >= '0' && *str <= '9')))
		str++;
	safe_call_ptr(str = skip_to("x1", str), error_message, data);
	safe_call_ptr(str = parse_float(str, &wall->left.x), "parse float error", data);
	safe_call_ptr(str = skip_to("y1", str), error_message, data);
	safe_call_ptr(str = parse_float(str, &wall->left.y), "parse float error", data);
	safe_call_ptr(str = skip_to("x2", str), error_message, data);
	safe_call_ptr(str = parse_float(str, &wall->right.x),  "parse float error", data);
	safe_call_ptr(str = skip_to("y2", str), error_message, data);
	safe_call_ptr(str = parse_float(str, &wall->right.y), "parse float error", data);
	if (wall->left.x > wall->right.x)
	{
		box = wall->left;
		wall->left = wall->right;
		wall->right = box;
	}
	wall->length = sqrt(pow(wall->left.x - wall->right.x, 2)
						+ pow(wall->left.y - wall->right.y, 2));
	get_wall_type(str, wall, data);
}

static char		*find_texture(char *str, t_wall *wall, int text_where, t_data *data)
{
	int		i;
	char	box;

	i = 0;

	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\r'))
		i++;
	box = str[i];
	str[i] = '\0';
	if (i > 0)
	wall->textures[text_where] = find_texture_by_name(str, data);
	str[i] = box;
	str = (str + i);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r'))
		str++;
	return (str);
}

static void		get_wall_textures(char *str, t_wall *wall, t_data *data, t_parse **parse)
{
	int			i;

	i = 0;
	safe_call_parse_ptr(str = skip_to("textures", str),
				  "Check wall\'s texture.", data, parse);
	while (i < 3)
	{
		str = find_texture(str, wall, i, data);
		i++;
		if (!*str)
			break ;
	}
	if (*str)
		safe_call_parse_int(-1, "Should be max 3 "
					"textures for a wall.", data, parse);
	if (i == 1 && wall->type != WALL && wall->type != GLASSY)
		safe_call_parse_int(-1, "Should be more than "
						  "1 texture for all kind of wall "
						  "except of normal and glassy.", data, parse);
	if (i == 3 && (wall->type != DOOR))
		safe_call_parse_int(-1, "Should be "
						  "3 textures for door type wall.", data, parse);
	if (i == 2 && (wall->type != WINDOW && wall->type != PORTAL))
		safe_call_parse_int(-1, "Should be 2 textures "
					"for window and portal kinds of wall.", data, parse);
}

void			parse_single_wall(t_parse **parse, t_data *data)
{
	t_twlist	*res;
	t_wall		*wall;
	char		*str;

	str = (*parse)->cur_str;
	wall = safe_call_parse_ptr(ft_memalloc(sizeof(t_wall)),
		"Malloc crashed in \"./src/parse/parse_wall.c\"", data, parse);
	wall->sector = (*parse)->cur_sector;
	safe_call_parse_ptr(str = skip_to("wall_", str),
		"Check your walls.", data, parse);
	get_wall_coordinates(str, wall, data);
	ft_strdel(&(*parse)->cur_str);
	if ((get_next_line((*parse)->fd, &(*parse)->cur_str)) != 1)
		safe_call_int(-1, "Map error: no texture for a wall.", data);
	get_wall_textures((*parse)->cur_str, wall, data, parse);
	res = safe_call_parse_ptr(ft_twlstnew(wall, sizeof(t_wall)),
		"Malloc crashed in \"./src/parse/parse_wall.c\"", data, parse);
	ft_memdel(&wall);
	(*parse)->walls_tmp->next = res;
	res->prev = (*parse)->walls_tmp;
	(*parse)->walls_tmp = (*parse)->walls_tmp->next;
	(*parse)->cur_sector->render->walls_count++;
	ft_strdel(&(*parse)->cur_str);
}
