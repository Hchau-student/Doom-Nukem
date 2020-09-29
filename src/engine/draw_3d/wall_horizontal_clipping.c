//
// Created by Hugor Chau on 9/28/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/map_struct.h"

/*
**		function finding point of crossing two vectors -
**		original wall and one of player's FOV
*/

static t_vec3	find_new_dot(t_player *p, t_wall *w, float angle)
{
	t_vec3	res;
	t_wall	line;
	t_vec3	p_dot;
	t_vec3	line_coefficients;
	t_vec3	p_coefficients;

	line.left = w->left.x <= w->right.x ? w->left : w->right;
	line.right = w->left.x <= w->right.x ? w->right : w->left;
	if (fabs(sin(angle)) <= 0.00001 || fabs(cos(angle)) <= 0.00001)
		angle += 0.00001;
	p_dot.x = cos(angle) > 0 ? p->position.x : p->position.x + cos(angle);
	p_dot.y = cos(angle) > 0 ? p->position.y : p->position.y + sin(angle);
	p_coefficients.x = tan(angle);
	line_coefficients.x = ((-line.right.y + line.left.y)
						   / (-line.right.x + line.left.x + 0.00001));
	p_coefficients.y = (p_dot.y - (p_coefficients.x * p_dot.x));
	line_coefficients.y = (line.left.y - line_coefficients.x * line.left.x);
	res.x = ((p_coefficients.y - line_coefficients.y)
			 / (line_coefficients.x - p_coefficients.x));
	res.y = (p_coefficients.x * res.x + p_coefficients.y);
	return (res);
}

/*
**		function checks if dot is behind vector
**		from player's pos with some angle
*/

static int		is_overlap(t_data *data, t_vec3 w1, float angle)
{
	t_vec3	v1;
	t_vec3	check;

	v1.x = (data->engine->player->position.x - w1.x);
	v1.y = (data->engine->player->position.y - w1.y);
	check.x = (cos(angle));
	check.y = (sin(angle));
	if ((-(v1.x * check.x + v1.y * check.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											   * sqrt(check.x * check.x + check.y * check.y)) < 0))
		return (TRUE);
	return (FALSE);
}

/*
**		function returns vertex location placed in the FOV and corrects it
**		if it's necessary
*/

t_vec3		horizontal_clipping(t_wall *full_wall, t_vec3 original_dot, t_data *data)
{
	t_vec3	res;
	float	angle;
	float	fov;

	fov = (data->engine->player->fov / 2) * M_PI / 180;
	angle = data->engine->player->direction_angle.x;
	res = original_dot;
	if (is_overlap(data, res, angle) == TRUE)
	{
		res = (find_new_dot(data->engine->player, full_wall,
						angle + fov * 2));
	}
	if (is_overlap(data, res, angle + fov) == TRUE)
	{
		res = (find_new_dot(data->engine->player, full_wall,
							angle - fov));
	}
	if (is_overlap(data, res, angle - fov) == TRUE)
	{
		res = (find_new_dot(data->engine->player, full_wall,
							angle + fov));
	}
	return (res);
}
