#include "../../Include/map_struct.h"

static void		check_error(char *line, char flag, char brackets, t_data *data)
{
	if (flag == -1)
		safe_call_int(-1, "Read error: gnl returned -1.", data);
	safe_call_int(check_line("t_objects", line),
		"Check for error in \'objects\' data. There should "
		"be closing flag \'t_objects\'.", data);
	safe_call_int(brackets, "Sector parse error: "
						"check for brackets.", data);
}

static void		get_cur_list(t_list **cur, t_list **all, t_data *data)
{
	t_list		*tmp;

	if (*all == NULL)
	{
		*all = (t_list *)safe_call_ptr(ft_lstnew(NULL, sizeof(void *)),
				"Malloc crashed in \"./src/parse/parse_obj.c\", "
				"\"new_object\".", data);
		*cur = *all;
		return ;
	}
	tmp = *all;
	while (tmp->next)
		tmp = tmp->next;
	*cur = tmp;
}

static t_list	*new_object(char *str, int fd, t_sector *sector, t_data *data)
{
	t_list		*res;
	void		*obj;
	size_t		obj_size;

	obj_size = MAX_OBJ;
	obj = parse_object(str, fd, sector, data);
	obj_size = ((t_obj *)obj)->type == HEALTH_OBJ ?
			sizeof(t_health_obj) : obj_size;
//	obj_size = ((t_obj *)obj)->type == POSTER ? sizeof(t_poster_obj) : obj_size;
	obj_size = ((t_obj *)obj)->type == WEAPON_OBJ ? sizeof(t_weapon) : obj_size;
//	obj_size = ((t_obj *)obj)->type == BULLETS ? sizeof(t_bullets) : obj_size;
	if (obj_size == MAX_OBJ)
		safe_call_int(-1, "Wrong obj type."
		"Error in \"./src/parse/parse_obj.c\", \"new_object\".", data);
	res = (t_list *)safe_call_ptr(ft_lstnew(obj, obj_size),
		"Malloc crashed in \"./src/parse/parse_obj.c\","
				" \"new_object\".", data);
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

void			parse_objects(char *str, int fd, t_sector *sector, t_data *data)
{
	char				*line;
	char				count_brackets;
	char				flag;
	t_list				*tmp;

	count_brackets = 0;
	get_cur_list(&tmp, &sector->objects, data);
	safe_call_int(check_line("objects", str),
		"Objects not objects: check \"./src/parse/parse_obj\".", data);
	while (((flag = get_next_line(fd, &line)) == 1)
		 && (check_line("t_objects", line)))
	{
		ft_putendl(line);
		if (!check_line("{", line))
			count_brackets++;
		else if (!check_line("}", line))
			count_brackets--;
		else
		{
			tmp->next = new_object(line, fd, sector, data);
			tmp = tmp->next;
		}
		ft_strdel(&line);
	}
	remove_first_list(&sector->objects);
	check_error(line, flag, count_brackets, data);
}
