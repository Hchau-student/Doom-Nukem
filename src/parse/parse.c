//
// Created by Hugor Chau on 9/14/20.
//
#include "../../Include/map_struct.h"

/*
**		works with *.txt for now
*/

int				open_file(char *map_name, t_data *data)
{
	int fd = open(map_name, O_RDONLY);
	if (fd < 3)
	{
		ft_putstr(map_name);
		ft_putendl(":");
		safe_call_int(-1, "Can't open file, try again.", data);
	}
	return (fd);
}

/*
**		if we parsed string without troubles,
**		it would be NULL; I know it's bad, and
**		that is the reason why we can't parse
**		string without "if else" tenses, buuuut
**		I didn't came out with better decision to
**		fight leaks if map is wrong
*/

static void		end_parse(t_parse *parse, t_data *data)
{
	safe_call_parse_int(parse->gnl_read_flag, "Read error: gnl returned -1.", data, &parse);
	if (parse->player_hud_parsed != 1 || parse->player_parsed != 1)
		safe_call_parse_int(-1, "Player and hud should be in your map. Once.", data, &parse);
	ft_strdel(&parse->cur_str);
	data->engine->sectors_count = parse->sector_index;
	remove_parse(&parse);
}

//static void		prepare_skybox(t_data *data, t_parse *parse)
//{
//	parse->sector_index = 1;
//	data->engine->sectors = ft_memalloc(sizeof(t_sector) * 1);
//	data->engine->sectors[0]->render = ft_memalloc(sizeof(t_sector_render));
//	data->engine->sectors_count = 1;
//	data->engine->sectors[0]->type = SEC_NORMAL;
//	data->engine->sectors[0].textures[CEILING_TEXT] = find_texture_by_name("sky", data);
//	data->engine->sectors[0].textures[FLOOR_TEXT] = find_texture_by_name("ground", data);
//	data->engine->sectors[0].textures[FLOOR_TEXT] = find_texture_by_name("ground", data);
//}

static void		parse_file(int fd, t_data *data)
{
	t_parse		*parse;
	char		letter;

	parse = safe_call_ptr(ft_memalloc(sizeof(t_parse)), "Malloc crashed: "
					"./src/parse/parse.c", data);
	parse->fd = fd;
//	prepare_skybox(data, parse);
	while ((parse->gnl_read_flag = get_next_line(parse->fd, &parse->cur_str)) == 1)
	{
		letter = parse->cur_str[0];
		if (letter == 's')
			parse_sector(&parse, data);
		else if (letter == 'p')
			parse_player(&parse, data);
		ft_strdel(&parse->cur_str);
	}
	check_portals_data(data, parse);
	end_parse(parse, data);
}

void	parse(char *str, t_data *data)
{
	parse_file(open_file(str, data), data);
}
