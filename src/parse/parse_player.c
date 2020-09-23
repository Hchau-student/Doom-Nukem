//
// Created by Hugor Chau on 9/22/20.
//

#include "../../Include/map_struct.h"

static void		check_error(char *line, char flag, char brackets, t_data *data)
{
	if (flag == -1)
	{
		safe_call_int(-1, "Read error: gnl returned -1.", data);
	}
	if (check_line("t_player", line))
	{
		safe_call_int(-1,
					  "Check for error in \'player\' data. There should "
					  "be closing flag \'t_player\'.", data);
	}
	if (brackets != 0)
	{
		safe_call_int(-1, "Player parse error: "
						  "check for brackets.", data);
	}
}

//typedef struct			s_player
//{
//	t_vec2			position;
//	t_vec2			direction_angle;
//	t_move			*move;
//	float			fov;
//	t_display_hud	*hud;
//	int32_t			current_sector;
//	t_sector		*cur_sec;
//}						t_player;

void			parse_player(char *str, int fd, t_data *data)
{
	static uint32_t		index = 0;
	char				flag;
	char				*line;
	char				count_brackets;

	count_brackets = 0;
	safe_call_int(check_line("player", str),
				  "No matches: check for error in \'player\' data.", data);
	while (((flag = get_next_line(fd, &line)) == 1)
		   && (check_line("t_player", line)))
	{
		if (check_line("{", line) == 0)
			count_brackets++;
		else if (check_line("}", line) == 0)
			count_brackets--;
		else
			parse_player_line(line, fd, data);
		ft_strdel(&line);
	}
	check_error(line, flag, count_brackets, data);
	ft_strdel(&line);
	index++;
}