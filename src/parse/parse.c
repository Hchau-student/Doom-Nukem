//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/map_struct.h"

/*
**		works with *.txt for now
*/

/*
**		this function checks if word or line were correct
*/

int				check_line(char *should_be, char *check)
{
	int		i;

	i = 0;
	while (should_be[i] == check[i])
		i++;
	return (should_be[i] == '\0' ? 0 : 1);
}

void			parse_vertex(char *str, t_data *data)
{
	static char		check[7] = "vertex\0";

	safe_call_int(check_line(check, str), "No matches: check for error in \'vertex\' data", data);
}

int				open_file(char *map_name, t_data *data)
{
	int fd = open(map_name, O_RDONLY);
	if (fd < 3)
		safe_call_int(-1, "Can't open file, try again.", data);
	return (fd);
}

static void		parse_file(int fd, t_data *data)
{
	char	*line;
	char	flag;

	while ((flag = get_next_line(fd, &line)) == 1)
	{
		line[0] == 'v' ? parse_vertex(line, data) : 0;
		line[0] == 'w' ? parse_wall() : 0;
		line[0] == 's' ? parse_sector() : 0;
		ft_strdel(&line);
		//распихать все данные в *engine
	}
	safe_call_int(flag, "Read error: gnl returned -1.", data);
	ft_strdel(&line);
}

void	parse(char *str, t_data *data)
{
	parse_file(open_file(str, data), data);
//	safe_call_int(close(fd), "Can\'t close file."
//					  "Function parse, module parse.", data);
}
