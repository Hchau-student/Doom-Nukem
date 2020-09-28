//
// Created by Hugor Chau on 9/24/20.
//

#include "../../Include/map_struct.h"

void		parse_struct(t_parse **parse, t_data *data, void (*parse_thing)(t_parse **, t_data *), char *signal_word)
{
	char				count_brackets;

	count_brackets = 0;
	ft_strdel(&(*parse)->cur_str);
	while ((((*parse)->gnl_read_flag = get_next_line((*parse)->fd, &(*parse)->cur_str)) == 1)
		   && (check_line(signal_word, (*parse)->cur_str)))
	{
		if (!check_line("{", (*parse)->cur_str))
			count_brackets++;
		else if (!check_line("}", (*parse)->cur_str))
			count_brackets--;
		else if (!*(*parse)->cur_str)
			;
		else
			parse_thing(parse, data);
		ft_strdel(&(*parse)->cur_str);
	}
	check_error(parse, count_brackets, data);
//	ft_strdel(&(*parse)->cur_str);
}
