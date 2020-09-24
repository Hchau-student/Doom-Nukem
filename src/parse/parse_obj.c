#include "../../Include/map_struct.h"
#include "../../Include/objects.h"

static void		check_error(t_parse **parse, char brackets, t_data *data, char *end_line)
{
	if ((*parse)->gnl_read_flag == -1)
		safe_call_parse_int(-1, "Read error: gnl returned -1.", data, parse);
	safe_call_parse_int(check_line(end_line, (*parse)->cur_str),
						(*parse)->error_message, data, parse);
	safe_call_parse_int(brackets, "Sector parse error: "
						"check for brackets.", data, parse);
}

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

static t_list	*new_object(t_parse **parse, t_data *data)
{
	t_list		*res;
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
	res = (t_list *)safe_call_parse_ptr(ft_lstnew(obj, obj_size),
		"Malloc crashed in \"./src/parse/parse_obj.c\","
				" \"new_object\".", data, parse);
	ft_memdel((void **)&obj);
	return (res);
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
	char				count_brackets;
	t_list				*tmp;

	count_brackets = 0;
	get_cur_list(&tmp, &(*parse)->cur_sector->objects, parse, data);
	safe_call_parse_int(check_line("objects", (*parse)->cur_str),
		"Objects not objects: check \"./src/parse/parse_obj\".", data, parse);
	ft_strdel(&(*parse)->cur_str);
	while ((((*parse)->gnl_read_flag = get_next_line((*parse)->fd, &(*parse)->cur_str)) == 1)
		 && (check_line("t_objects", (*parse)->cur_str)))
	{
		if (!check_line("{", (*parse)->cur_str))
			count_brackets++;
		else if (!check_line("}", (*parse)->cur_str))
			count_brackets--;
		else
		{
			tmp->next = new_object(parse, data);
			tmp = tmp->next;
		}
		ft_strdel(&(*parse)->cur_str);
	}
	remove_first_list(&(*parse)->cur_sector->objects);
	(*parse)->error_message = ft_strdup("Check for error in "
		"\'objects\' data. There should "
		"be closing flag \'t_objects\'.");
	ft_strdel(&(*parse)->error_message);
	check_error(parse, count_brackets, data, "t_objects");
}
