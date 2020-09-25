#include "../../Include/map_struct.h"

static void			parse_health_obj_attributes(char *str,
								t_health_obj *obj, t_data *data, t_parse **parse)
{
	static char	names[3][10] = {{"medicine\0"}, {"armor\0"}, {"poison\0"}};
	int8_t		type;

	type = -1;
	type = check_line(names[MEDICINE], str) == 0 ? MEDICINE : type;
	type = check_line(names[POISON], str) == 0 ? POISON : type;
	type = check_line(names[ARMOR], str) == 0 ? ARMOR : type;
	if (type == -1)
		safe_call_parse_int(-1, "Wrong object type. "
				"\"./src/parse/parse_single_object.c\".", data, parse);
	str = skip_to(names[type], str);
	obj->place = (t_vec2 *)ft_memalloc(sizeof(t_vec2));
	if (*str != 'x')
		safe_call_int(-1, "Coordinates are invalid.", data);
	str = skip_to("x", str);
	safe_call_parse_ptr(str = parse_float(str, &obj->place->x),
					"Float parsing error.", data, parse);
	if (*str != 'y')
		safe_call_int(-1, "Coordinates are invalid.", data);
	str = skip_to("y", str);
	safe_call_parse_ptr(str = parse_float(str, &obj->place->x),
					"Float parsing error.", data, parse);
	safe_call_parse_ptr(str = skip_to("hp", str),
					"Health object parsing error.", data, parse);
	if ((*str < '0' || *str > '9') && *str != '-' && *str != '+')
		safe_call_parse_int(-1, "Health object parsing error.", data, parse);
	obj->plus = atoi(str);
	obj->texture = find_texture_by_name(names[type], data);
}

static void			*parse_health_obj(char *str,
										t_data *data, void **object, t_parse **parse)
{
//	static char		names[3][11] = {{"HEALTH_OBJ\0"}, {"POSTER\0"}, {"WEAPON\0"}};
//
//	TODO need to check is an object in the sector or not
	*object = (t_health_obj *)safe_call_ptr(ft_memalloc(sizeof(t_health_obj)),
		"Malloc crashed: "
			"./src/parse/parse_single_object.c, \"parse_health_obj\".", data);
	((t_health_obj *)(*object))->common_type = HEALTH_OBJ;
	parse_health_obj_attributes(str, *object, data, parse);
//	ft_putendl(names[((t_obj *)(*object))->type]);
	return (*object);
}

void				*parse_object(t_parse **parse, t_data *data)
{
	void	*res;
	char	*str;

	str = (*parse)->cur_str;
	res = NULL;
	while (*str)
	{
		if (*str == 'm' || *str == 'a' || *str == 'p')
			return (parse_health_obj(str, data, &res, parse));
//		if (*str == 'p')
//			return (parse_poster(str, sector, data));
//		else if (*str == 's')
//			return (parse_sprite(str, sector, data));
//		else if (*str == 'e')
//			return (parse_enemy(str, sector, data));
		else if ((*str == ' ' || *str == '\t' || *str == '\r'))
			;
		else
			safe_call_int(-1,
				"Hey! Check your objects in map!", data);
		str++;
	}
	return (res);
}
