//
// Created by Hugor Chau on 9/23/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static float	check_parsed_walls_intersect(t_wall *one, t_wall *two)
{
	t_vec2		v1;
	t_vec2		v2;
	int			flag;

	flag = 0;
	if (one->right.x <= two->left.x)
		return (0);
	if (one->left.x >= two->right.x)
		return (0);
	if (one->left.y <= two->left.y && one->right.y <= two->left.y &&
		one->right.y <= two->right.y && one->left.y <= two->right.y)
		return (0);
	if (one->left.y >= two->left.y && one->right.y >= two->left.y &&
		one->right.y >= two->right.y && one->left.y >= two->right.y)
		return (0);
	v1.x = one->left.x - two->left.x;
	v1.y = one->left.y - two->left.y;
	v2.x = one->right.x - two->left.x;
	v2.y = one->right.y - two->left.y;
//	if (v1.y < v2.y)
		flag = v1.x * v2.y - v1.y * v2.x <= 0.0 ? 1 : 0;
//	else
//		flag = v2.x * v1.y - v2.y * v1.x < 0 ? 1 : 0;
	v1.x = one->left.x - two->right.x;
	v1.y = one->left.y - two->right.y;
	v2.x = one->right.x - two->right.x;
	v2.y = one->right.y - two->right.y;
//	if (v1.y < v2.y)

		flag += v1.x * v2.y - v1.y * v2.x <= 0.0 ? -1 : 0;
//	else
//		flag += v2.x * v1.y - v2.y * v1.x < 0 ? -1 : 0;
	return flag;
}

static void		check_walls_cross(struct s_sector *sector, struct s_data *data)
{
	int			i;
	int			j;
	t_wall		*wall;
	t_wall		*tmp;
	int			max;

	max = sector->render->walls_count;
	i = 0;
	wall = sector->render->walls;
	while (i < max)
	{
		j = i;
		tmp = wall;
		while (j < max)
		{
			tmp = tmp->next;
			safe_call_int(check_parsed_walls_intersect(wall, wall->next),
				 "Hey!", data);
			j++;
		}
		wall = wall->next;
		i++;
	}
	safe_call_int(0, "check", data);
}

static int		check_wall_connect(t_wall *cur, t_wall *next, t_wall *prev)
{
	if (((int)(cur->left.x) == (int)(next->left.x) && (int)(cur->left.y) == (int)(next->left.y))
		|| ((int)(cur->left.x) == (int)(next->right.x) && (int)(cur->left.y) == (int)(next->right.y)))
	{
		if (((int)(cur->right.x) == (int)(prev->left.x)) && ((int)(cur->right.y) == (int)(prev->left.y)))
			return (TRUE);
		if (((int)(cur->right.x) == (int)(prev->right.x)) && ((int)(cur->right.y) == (int)(prev->right.y)))
			return (TRUE);
	}
	if (((int)(cur->right.x) == (int)(next->left.x) && (int)(cur->right.y) == (int)(next->left.y))
		|| ((int)(cur->right.x) == (int)(next->right.x) && (int)(cur->right.y) == (int)(next->right.y)))
	{
		if ((int)(cur->left.x) == (int)(prev->left.x) && (int)(cur->left.y) == (int)(prev->left.y))
			return (TRUE);
		if ((int)(cur->left.x) == (int)(prev->right.x) && (int)(cur->left.y) == (int)(prev->right.y))
			return (TRUE);
	}
	return (FALSE);
}

static void		check_walls_cycle(struct s_sector *sector, struct s_data *data)
{
	int			i;
	t_wall		*wall;
	int			max;

	max = sector->render->walls_count;
	i = 0;
	wall = sector->render->walls;
	while (i < max)
	{
		i++;
		wall->next->prev = wall;
		wall->height = sector->ceiling_height - sector->floor_height;
		if (!(check_wall_connect(wall,
					wall->next, wall->prev)) || wall->height <= 0)
		{
			safe_call_int(-1, "Walls data is wrong. "
			"./src/parse/check_parsed_walls.c.", data);
		}
		wall = wall->next;
	}
}

void			check_walls_data(struct s_sector *sector, struct s_data *data)
{
	check_walls_cycle(sector, data);
	check_walls_cross(sector, data);
}
