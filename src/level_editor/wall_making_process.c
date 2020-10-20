//
// Created by Hugor Chau on 10/15/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

int			point_match(t_vec3 point1, t_vec3 point2, float check_area)
{
	if (fabs(point1.x - point2.x) < check_area && fabs(point1.y - point2.y) < check_area)
		return (TRUE);
	return (FALSE);
}
//
//int 		change_point(t_vec3 *point1, t_vec3 point2)
//{
//	*point1 = point2;
//	return (TRUE);
//}

int		change_point1(t_vec3 *point1, t_vec3 point2, int curr_wall)
{
	*point1 = point2;
	printf("wwwww%d\n", curr_wall);
	return (TRUE);
}

int		new_point(t_data *data, t_vec3 *point, t_wall *wall1)
{
	int		sec_num;
	int		sec_num_max;
	t_wall	*wall_iter;
	int		curr_wall;
	float	check_area;

	if (wall1 == NULL)
		return FALSE;
	check_area = 10 * data->engine->minimap->size_divider;
	*point = (t_vec3){MOUSE_X, MOUSE_Y, 0};
	sec_num_max = data->engine->sectors_count;
	sec_num = 0;
	while (sec_num < sec_num_max)
	{
		curr_wall = data->engine->sectors[sec_num].render->walls_count;
		wall_iter = data->engine->sectors[sec_num].render->walls;
		while (curr_wall > 0)
		{
			if (point_match(wall_iter->right, *point, check_area) == TRUE)
//				return (change_point(point, wall_iter->right));
				return (change_point1(point, wall_iter->right, curr_wall));
			if (point_match(wall_iter->left, *point, check_area) == TRUE)
//				return (change_point(point, wall_iter->left));
				return (change_point1(point, wall_iter->left, curr_wall));
			wall_iter = wall_iter->next;
			curr_wall--;
		}
	sec_num++;
	}
	return (FALSE);
}
