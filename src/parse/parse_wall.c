//
// Created by Hugor Chau on 9/16/20.
//
#include "../../Include/map_struct.h"

void			parse_wall(t_parse **parse, t_data *data)
{
	t_twlist	*tmp;
	t_twlist	*del;

	(*parse)->walls_tmp = ft_twlstnew(NULL, 0);
	safe_call_parse_int(check_line("walls", (*parse)->cur_str),
						"Walls not walls: check \"./src/parse/parse_wall.c\".", data, parse);
	del = (*parse)->walls_tmp;
	parse_struct(parse, data, &parse_single_wall, "t_walls");
	tmp = (*parse)->walls_tmp;
	(*parse)->cur_sector->render->walls = del->next;
	tmp->next = (*parse)->cur_sector->render->walls;
	(*parse)->cur_sector->render->walls->prev = tmp;
	safe_call_parse_int(check_line("t_walls", (*parse)->cur_str),
						"Check for error in \'t_walls\' data. There should "
						"be closing flag \'t_walls\'.", data, parse);
	ft_strdel(&(*parse)->cur_str);
	ft_memdel(&del);
	check_walls_data((*parse)->cur_sector, data);
}
