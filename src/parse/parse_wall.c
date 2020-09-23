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

void			parse_wall(char *str, int fd, t_sector *sector, t_data *data)
{
	char				*line;
	char				count_brackets;
	char				flag;
	t_twlist			*tmp;

	count_brackets = 0;
	tmp = ft_twlstnew(NULL, 0);
	safe_call_int(check_line("walls", str),
		"Walls not walls: check \"./src/parse/parse_wall.c\".", data);
	while (((flag = get_next_line(fd, &line)) == 1)
		   && (check_line("t_walls", line)))
	{
		ft_putendl(line);
		if (!check_line("{", line))
			count_brackets++;
		else if (!check_line("}", line))
			count_brackets--;
		else
		{
			tmp->next = parse_single_wall(line, fd, sector, data);
			tmp = tmp->next;
		}
		ft_strdel(&line);
	}
	check_error(line, flag, count_brackets, data);
}
