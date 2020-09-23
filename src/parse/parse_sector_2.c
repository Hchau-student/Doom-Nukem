//
// Created by Hugor Chau on 9/21/20.
//

#include "../../Include/map_struct.h"

static void		check_error(char *line, char flag, char brackets, t_data *data)
{
	if (flag == -1)
	{
		safe_call_int(-1, "Read error: gnl returned -1.", data);
	}
	if (check_line("t_sector", line))
	{
		safe_call_int(-1,
					"Check for error in \'sector\' data. There should "
					"be closing flag \'t_sector\'.", data);
	}
	if (brackets != 0)
	{
		safe_call_int(-1, "Sector parse error: "
						"check for brackets.", data);
	}
}

static void		alloc_sectors(uint32_t cur_sec, t_data *data, t_engine *engine)
{
	t_sector	*sectors;

	if (cur_sec >= engine->sectors_count)
	{
		engine->sectors_count += 50;
		sectors = (t_sector *)safe_call_ptr(ft_memalloc(sizeof(t_sector)
				* (engine->sectors_count)), "Malloc crashed in"
				"\"./src/parse/parse_sector\", alloc_sectors.", data);
		safe_call_ptr(ft_memcpy(sectors, engine->sectors, sizeof(t_sector)
				* (engine->sectors_count - 50)),
			"ft_memcpy crashed in"
			"\"./src/parse/parse_sector\", alloc_sectors.", data);
		engine->sectors = sectors;
	}
	engine->sectors[cur_sec].render =
		(t_sector_render *)safe_call_ptr(ft_memalloc(sizeof(t_sector_render)),
		"Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
	engine->sectors[cur_sec].id = cur_sec;
}

void			parse_sector(char *str, int fd, t_data *data)
{
	static uint32_t		index = 0;
	char				flag;
	char				*line;
	t_sector			*res;
	char				count_brackets;

	alloc_sectors(index, data, (t_engine *)data->engine);
	count_brackets = 0;
	res = &((t_engine *)data->engine)->sectors[index];
	safe_call_int(check_line("sector", str),
				"No matches: check for error in \'sector\' data.", data);
	while (((flag = get_next_line(fd, &line)) == 1)
		&& (check_line("t_sector", line)))
	{
		if (!check_line("{", line))
			count_brackets++;
		else if (!check_line("}", line))
			count_brackets--;
		else
			parse_line(line, fd, res, data);
		ft_strdel(&line);
	}
	check_error(line, flag, count_brackets, data);
	ft_strdel(&line);
	index++;
}
