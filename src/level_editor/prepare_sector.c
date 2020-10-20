//
// Created by Hugor Chau on 10/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

int			do_we_need_new_sector(t_sector *sectors, int sectors_count)
{
	if (sectors_count == 0 || sectors[sectors_count - 1].is_ended == TRUE)
		return TRUE;
	return FALSE;
}

void		prepare_new_sector(t_sector *sectors, int sectors_count, t_data *data)
{
	sectors[sectors_count].render =
			(t_sector_render *)safe_call_ptr(ft_memalloc(sizeof(t_sector_render)),
											 "Lol malloc crashed in \'./src/parse/parse_sector_line.c\'.", data);
	sectors[sectors_count].render->walls_count = 0;
	sectors[sectors_count].is_ended = FALSE;
	sectors[sectors_count].render->ceiling_height = DEFAULT_CEIL;
	sectors[sectors_count].render->floor_height = DEFAULT_FLOOR;
	sectors[sectors_count].ceiling_height = DEFAULT_CEIL;
	sectors[sectors_count].floor_height = DEFAULT_FLOOR;
	data->engine->sectors_count++;
}

void		if_sectors_overflowed(int sectors_count, t_data *data)
{
	t_sector *sectors;

	if (sectors_count % 50 == 0)
	{
		sectors = (t_sector *)safe_call_ptr(ft_memalloc(sizeof(t_sector)
														* (sectors_count + 50)), "Malloc crashed in"
																				 "\"./src/parse/parse_sector\", alloc_sectors.", data);
		safe_call_ptr(ft_memcpy(sectors, data->engine->sectors, sizeof(t_sector)
																* (sectors_count)),
					  "ft_memcpy crashed in"
					  "\"./src/parse/parse_sector\", alloc_sectors.", data);
		data->engine->sectors = sectors;
	}
}

void		prepare_sector(t_data *data)
{
	t_sector	*sectors;
	int			sectors_count;

	if_sectors_overflowed(data->engine->sectors_count, data);
	sectors = data->engine->sectors;
	sectors_count = data->engine->sectors_count;
	if (do_we_need_new_sector(sectors, sectors_count) == TRUE)
	{
		prepare_new_sector(sectors, sectors_count, data);
	}
	printf("sec = %d\n", data->engine->sectors_count);
}
