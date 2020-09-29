//
// Created by Hugor Chau on 9/28/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static int		check_portal(t_wall *one, t_wall *two)
{
	if (fabs(one->left.x - two->left.x) < 0.001 &&
			fabs(one->left.y - two->left.y) < 0.001 &&
			fabs(one->right.x - two->right.x) < 0.001 &&
			fabs(one->right.y - two->right.y) < 0.001)
		return (TRUE);
	return (FALSE);
}

void	check_portals_data(struct s_data *data, t_parse *parse)
{
	t_list		*tmp;
	t_list		*current_wall;

	current_wall = parse->check_portals;
	while (current_wall)
	{
		tmp = parse->check_portals;
		while (tmp)
		{
			if (tmp == current_wall)
				;
			else if (check_portal((*(t_wall **)tmp->content), (*(t_wall **)current_wall->content)) == TRUE)
			{
				(*(t_wall **)tmp->content)->portal_to =
						*(t_wall **)current_wall->content;
				(*(t_wall **)current_wall->content)->portal_to =
						*(t_wall **)tmp->content;
				break;
			}
			tmp = tmp->next;
		}
//		if ((*(t_wall **)current_wall->content)->portal_to == NULL)
//			safe_call_parse_int(-1,
//					"Portal data does not exists in two sectors.", data, &parse);
		/*
		**		1) беру стену
		 * 		2) ищу в массиве похожую
		 * 		3) нахожу!
		 * 		4) прикрепляю ссылку
		 * 		5) лол профит?
		*/
		current_wall = current_wall->next;
	}
}
