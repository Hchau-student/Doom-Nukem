//
// Created by Hugor Chau on 9/29/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/renderer.h"

/*
**		wall's x on the screen is calculated by
**		angle from the left vector of FOV
*/

float	find_angle(t_data *data, t_vec3 w1)
{
	t_vec3	v1;
	float	res;
	t_vec3	v2;

	v1.x = (data->engine->player->position.x - w1.x);
	v1.y = (data->engine->player->position.y - w1.y);
	v2.x = (cos(data->engine->player->direction_angle.x - (data->engine->player->fov / 2) * M_PI / 180));
	v2.y = (sin(data->engine->player->direction_angle.x - (data->engine->player->fov / 2) * M_PI / 180));
	res = -(((v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											* sqrt(v2.x * v2.x + v2.y * v2.y))));
	res = res >= 1 ? acos(1) : acos(res);
	res = (180 / M_PI * res /* - (60.0 / 3) */) / data->engine->player->fov;
	return (res);
}

float 	wall_h(t_vec3 point, float width, t_player *player)
{
	return width / sqrt(pow(point.x - player->position.x, 2) + pow(player->position.y - point.y, 2))
	* ((SCREEN_HEIGHT / 2) / tan((player->fov / 2) * M_PI / 180));
}

/*
**		finding extreme texture points for affine-correction formula
*/

void	text_extremes(t_wall w, t_wall *w_origin, t_wall *text_extremes)
{
	float original_wall_length;

	original_wall_length = w_origin->length;
	text_extremes->left.x = (float)w_origin->textures[WALL_TEXT]->width
							/ original_wall_length *
							(sqrt(pow(w_origin->left.x - w.left.x, 2)
								  + pow(w_origin->left.y - w.left.y, 2)));
	text_extremes->left.y = (float)w_origin->textures[WALL_TEXT]->width
							/ original_wall_length *
							(sqrt(pow(w_origin->left.x - w.right.x, 2)
								  + pow(w_origin->left.y - w.right.y, 2)));
}

void	wall_extremes(t_data *data, t_wall w, t_wall *borders, float *end_x)
{
	float	left;
	float	right;
	float	left_h;
	float	right_h;

	left = (float)SCREEN_WIDTH * find_angle(data, w.left);
	right = (float)SCREEN_WIDTH * find_angle(data, w.right);
	right_h = wall_h(w.right, w.height, data->engine->player);
	left_h = wall_h(w.left, w.height, data->engine->player);
	*end_x = right;
	borders->left.x = left;
	borders->left.z = wall_h(w.left, -(float)w.floor_height, data->engine->player);
	borders->right.z = wall_h(w.right, -(float)w.floor_height, data->engine->player);
	borders->left.y = ZERO_FLOOR - left_h - borders->left.z;
	borders->right.y = ZERO_FLOOR + borders->left.z;
	if (borders->left.x > *end_x)
	{
		*end_x = left;
		borders->left.x = right;
		borders->left.y = ZERO_FLOOR - right_h - borders->right.z;
		borders->right.y = ZERO_FLOOR + borders->right.z;
	}
}

void	text_destination(t_data *data, t_wall w, t_wall *text_extremes)
{
	text_extremes->right.x = sqrt(pow(w.left.x - data->engine->player->position.x, 2)
								  + pow(data->engine->player->position.y - w.left.y, 2));
	text_extremes->right.y = sqrt(pow(w.right.x - data->engine->player->position.x, 2)
								  + pow(data->engine->player->position.y - w.right.y, 2));
}
