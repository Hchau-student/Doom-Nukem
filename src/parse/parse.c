//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/parse.h"
//#include "../../Include/map_struct.h"

/*
**		works with *.txt for now
*/

static void		parse_vertex()
{

}

static int		open_file(char *map_name, t_data *data)
{
	int fd = open(map_name, O_RDONLY);
	if (fd < 0)
		safe_call_int(-1, "Can't open file, try again.", data);
	return (fd);
}

static void		parse_file(int fd, t_data *data)
{
	char	*line;
	char	flag;

	while ((flag = get_next_line(fd, &line)) != 0)
	{
		line[0] == 'v' ? parse_vertex() : 0;
		line[0] == 'w' ? parse_wall() : 0;
		line[0] == 's' ? parse_sector() : 0;

		//распихать все данные в *engine
	}
	safe_call_int(flag, "Read error: gnl returned -1.", data);
	ft_strdel(&line);
}

void	parse(char *str, t_data *data)
{
	parse_file(open_file(str, data), data);
}
