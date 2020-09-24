//
// Created by Hugor Chau on 9/22/20.
//

#include "../../Include/map_struct.h"

static void		check_error(t_parse **parse, char brackets, t_data *data)
{
	if ((*parse)->gnl_read_flag == -1)
	{
		safe_call_parse_int(-1, "Read error: gnl returned -1.", data, parse);
	}
	if (check_line("t_player", (*parse)->cur_str))
	{
		safe_call_parse_int(-1,
					  "Check for error in \'player\' data. There should "
					  "be closing flag \'t_player\'.", data, parse);
	}
	if (brackets != 0)
	{
		safe_call_parse_int(-1, "Player parse error: "
						  "check for brackets.", data, parse);
	}
}

void			parse_player(t_parse **parse, t_data *data)
{
	char	brackets;

	brackets = 0;
	safe_call_parse_int(check_line("player", (*parse)->cur_str),
				  "No matches: check for error in \'player\' data.", data, parse);
	ft_strdel(&(*parse)->cur_str);
	while ((((*parse)->gnl_read_flag = get_next_line((*parse)->fd, &(*parse)->cur_str)) == 1)
		   && (check_line("t_player", (*parse)->cur_str)))
	{
		if (check_line("{", (*parse)->cur_str) == 0)
			brackets++;
		else if (check_line("}", (*parse)->cur_str) == 0)
			brackets--;
		else
			parse_player_line(parse, data);
		ft_strdel(&(*parse)->cur_str);
	}
	check_error(parse, brackets, data);
	ft_strdel(&(*parse)->cur_str);
	(*parse)->player_parsed++;
}
