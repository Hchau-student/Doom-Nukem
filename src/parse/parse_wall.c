//
// Created by Hugor Chau on 9/16/20.
//
#include "../../Include/map_struct.h"

static void		check_error(char *line, char flag, char brackets, t_data *data)
{
	if (flag == -1)
		safe_call_int(-1, "Read error: gnl returned -1.", data);
	safe_call_int(check_line("t_walls", line),
				  "Check for error in \'t_walls\' data. There should "
				  "be closing flag \'t_walls\'.", data);
	safe_call_int(brackets, "Sector parse error: "
							"check for brackets.", data);
}

void			parse_wall(t_parse **parse, t_data *data)
{
	char				count_brackets;
	char				flag;
	t_twlist			*tmp;

	count_brackets = 0;
	tmp = ft_twlstnew(NULL, 0);
	safe_call_int(check_line("walls", (*parse)->cur_str),
		"Walls not walls: check \"./src/parse/parse_wall.c\".", data);
	ft_strdel(&(*parse)->cur_str);
	(*parse)->cur_sector->render->walls = tmp;
	while (((flag = get_next_line((*parse)->fd, &(*parse)->cur_str)) == 1)
		   && (check_line("t_walls", (*parse)->cur_str)))
	{
		if (!check_line("{", (*parse)->cur_str))
			count_brackets++;
		else if (!check_line("}", (*parse)->cur_str))
			count_brackets--;
		else
		{
			tmp->next = parse_single_wall(parse, data);
			tmp->next->prev = tmp;
			tmp = tmp->next;
			(*parse)->cur_sector->render->walls_count++;
		}
		ft_strdel(&(*parse)->cur_str);
	}
	tmp->next = (*parse)->cur_sector->render->walls->next;
	(*parse)->cur_sector->render->walls = tmp;
	check_walls_data((*parse)->cur_sector, data);
	check_error((*parse)->cur_str, flag, count_brackets, data);
}
