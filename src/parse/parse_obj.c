#include "../../Include/map_struct.h"
#include "../../Include/objects.h"

static void		get_cur_list(t_list **cur, t_list **all, t_parse **parse, t_data *data)
{
	t_list		*tmp;

	if (*all == NULL)
	{
		*all = (t_list *)safe_call_parse_ptr(ft_lstnew(NULL, sizeof(void *)),
				"Malloc crashed in \"./src/parse/parse_obj.c\", "
				"\"new_object\".", data, parse);
		*cur = *all;
		return ;
	}
	tmp = *all;
	while (tmp->next)
		tmp = tmp->next;
	*cur = tmp;
}

static void		new_object(t_parse **parse, t_data *data)
{
	void		*obj;
	size_t		obj_size;

	obj_size = MAX_OBJ;
	obj = parse_object(parse, data);
	obj_size = ((t_obj *)obj)->type == HEALTH_OBJ ?
			sizeof(t_health_obj) : obj_size;
//	obj_size = ((t_obj *)obj)->type == POSTER_OBJ ? sizeof(t_poster_obj) : obj_size;
	obj_size = ((t_obj *)obj)->type == WEAPON_OBJ ? sizeof(t_weapon) : obj_size;
	obj_size = ((t_obj *)obj)->type == BULLETS_OBJ ? sizeof(t_bullets_obj) : obj_size;
	if (obj_size == MAX_OBJ)
		safe_call_int(-1, "Wrong obj type."
		"Error in \"./src/parse/parse_obj.c\", \"new_object\".", data);
	(*parse)->obj->next = (t_list *)safe_call_parse_ptr(ft_lstnew(obj, obj_size),
		"Malloc crashed in \"./src/parse/parse_obj.c\","
				" \"new_object\".", data, parse);
	ft_memdel((void **)&obj);
	(*parse)->obj = (*parse)->obj->next;
}

static void		remove_first_list(t_list **all)
{
	t_list		*res;

	res = (*all)->next;
	(*all)->next = NULL;
	ft_memdel((void **)&(*all)->content);
	ft_memdel((void **)&(*all));
	*all = res;
}

void			parse_objects(t_parse **parse, t_data *data)
{
	get_cur_list(&(*parse)->obj, &(*parse)->cur_sector->objects, parse, data);
	safe_call_parse_int(check_line("objects", (*parse)->cur_str),
		"Objects not objects: check \"./src/parse/parse_obj\".", data, parse);
	parse_struct(parse, data, &new_object, "t_objects");
	remove_first_list(&(*parse)->cur_sector->objects);
	safe_call_parse_int(check_line("t_objects", (*parse)->cur_str),
						"Check for error in "
						"\'objects\' data. There should "
						"be closing flag \'t_objects\'.", data, parse);
}
