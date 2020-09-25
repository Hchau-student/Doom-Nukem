//
// Created by Hugor Chau on 9/22/20.
//

#include "../../Include/map_struct.h"

void			parse_player(t_parse **parse, t_data *data)
{
	safe_call_parse_int(check_line("player", (*parse)->cur_str),
						"No matches: check for error in \'player\' data.", data, parse);
	parse_struct(parse, data, &parse_player_line, "t_player");
	safe_call_parse_int(check_line("t_player", (*parse)->cur_str),
						"Check for error in "
						"\'player\' data. There should "
						"be closing flag \'t_player\'.", data, parse);
	ft_strdel(&(*parse)->cur_str);
	(*parse)->player_parsed++;
}
