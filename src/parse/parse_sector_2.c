//
// Created by Hugor Chau on 9/21/20.
//

#include "../../Include/map_struct.h"

static void		check_error(t_parse **parse, char brackets, t_data *data)
{
	if ((*parse)->gnl_read_flag == -1)
	{
		safe_call_parse_int(-1, "Read error: gnl returned -1.", data, parse);
	}
	if (check_line("t_sector", (*parse)->cur_str))
	{
		safe_call_parse_int(-1,
					"Check for error in \'sector\' data. There should "
					"be closing flag \'t_sector\'.", data, parse);
	}
	if (brackets != 0)
	{
		safe_call_parse_int(-1, "Sector parse error: "
						"check for brackets.", data, parse);
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

void			parse_sector(t_parse **parse, t_data *data)
{
	char				count_brackets;

	alloc_sectors((*parse)->sector_index, data, (t_engine *)data->engine);
	count_brackets = 0;
	(*parse)->cur_sector = &((t_engine *)data->engine)->sectors[(*parse)->sector_index];
	safe_call_parse_int(check_line("sector", (*parse)->cur_str),
		"No matches: check for error in \'sector\' data.", data, parse);
	ft_strdel(&(*parse)->cur_str);
	while ((((*parse)->gnl_read_flag = get_next_line((*parse)->fd, &(*parse)->cur_str)) == 1)
		   && (check_line("t_sector", (*parse)->cur_str)))
	{
		if (!check_line("{", (*parse)->cur_str))
			count_brackets++;
		else if (!check_line("}", (*parse)->cur_str))
			count_brackets--;
		else
			parse_line_sector(parse, data);
		ft_strdel(&(*parse)->cur_str);
	}
	check_error(parse, count_brackets, data);
	ft_strdel(&(*parse)->cur_str);
	(*parse)->sector_index++;
}
