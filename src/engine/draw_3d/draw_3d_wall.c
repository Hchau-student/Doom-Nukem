//
// Created by Hugor Chau on 9/28/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/map_struct.h"

//add perspective correction by height to make textures with incline (добавить
// коррекцию текстурирования для стен с наклоном на будущее)

void	data_text(t_wall borders, float text_x, t_texture *wall_texture, t_data *data)
{
	float step = (float)wall_texture->height / (fabs((borders.right.y) - (borders.left.y)));
	float y = borders.left.y;
	float y1 = 0.0;

	if (y < 0.0) {
		y1 = -y * step;
		y = 0.0;
	}
	if (y > SCREEN_HEIGHT) {
		return;
	}

	if (text_x < 0 || text_x > wall_texture->width)
		return;
	if (borders.left.x < 0 || borders.left.x > SCREEN_WIDTH)
		return;
	while (y < borders.right.y) {
		if (y1 >= wall_texture->height || y1 < 0)
			return;
		if (y >= SCREEN_HEIGHT)
			return;
		if (borders.left.x >= 0 && y >= 0 &&
			borders.left.x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
			data->sdl->layers->draw_3d->bit_map[(int)((int)borders.left.x + (int)y * SCREEN_WIDTH)] =
					wall_texture->bit_map[(int)((int)y1 * wall_texture->width + text_x)];
		}
		y += 1;
		y1 += step;
	}
}

float 	wall_h(t_vec3 point, float width, t_player *player) {
	return width / sqrt(pow(point.x - player->position.x, 2) + pow(player->position.y - point.y, 2)) * ((SCREEN_HEIGHT / 2) / TANGENT_45);
}

/*
**		formula for finding textel
*/

float 	find_textel(float angle, t_vec3 textels, t_vec3 dist, int text_max)
{
	float t_start_x = ((1.0 - angle) * (textels.x / dist.x)) +
					  ((angle) * (textels.y / dist.y));
	t_start_x = (int)(t_start_x /
					  ((1.0 - angle) * (1.0 / dist.x) + (angle * (1.0 / dist.y)))) % text_max;
	return t_start_x;
}

void	inverse_steps(t_vec2 *step, float *angle)
{
	step->y *= -1;
	*angle = 1;
	step->x *= -1;
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

void	text_destination(t_data *data, t_wall w, t_wall *text_extremes)
{
	text_extremes->right.x = sqrt(pow(w.left.x - data->engine->player->position.x, 2)
								  + pow(data->engine->player->position.y - w.left.y, 2));
	text_extremes->right.y = sqrt(pow(w.right.x - data->engine->player->position.x, 2)
								  + pow(data->engine->player->position.y - w.right.y, 2));
}
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

void	wall_extremes(t_data *data, t_wall w, t_wall *borders, float *end_x)
{
	float	left;
	float	right;
	float	left_h;
	float	right_h;

	left = (float)SCREEN_WIDTH * find_angle(data, w.left);
	right = (float)SCREEN_WIDTH * find_angle(data, w.right);
	right_h = wall_h(w.right, 40, data->engine->player);
	left_h = wall_h(w.left, 40, data->engine->player);
	*end_x = right;
	borders->left.x = left;
	borders->left.y = (float)SCREEN_HEIGHT / 2 - left_h;
	borders->right.y = (float)SCREEN_HEIGHT / 2 + left_h;
	if (borders->left.x > *end_x)
	{
		*end_x = left;
		borders->left.x = right;
		borders->left.y = (float)SCREEN_HEIGHT / 2 - right_h;
		borders->right.y = (float)SCREEN_HEIGHT / 2 + right_h;
	}
}

void	texturing_algorithm(t_wall w, t_wall *text_extremes, t_data *data, t_wall *w_origin)
{
	t_wall		borders;
	float		end_x;
	t_vec2		step;
	float		angle;
	float		t_start_x;

	wall_extremes(data, w, &borders, &end_x);
	step.y = (wall_h(w.left, 40, data->engine->player)
			  - wall_h(w.right, 40, data->engine->player)) / (end_x - borders.left.x);
	angle = 0;
	step.x = (1.0) / (end_x - borders.left.x);
	if (find_angle(data, w.left) > find_angle(data, w.right))
		inverse_steps(&step, &angle);
	while (borders.left.x < end_x)
	{
		borders.right.x = (int)borders.left.x;
		t_start_x = find_textel(angle, text_extremes->left,
			text_extremes->right, w_origin->textures[WALL_TEXT]->width);
		data_text(borders, t_start_x, w_origin->textures[WALL_TEXT], data);
		borders.left.x = (int)borders.left.x + 1;
		borders.left.y += step.y;
		angle += step.x;
		borders.right.y -= step.y;
	}
}

void	draw_wall_3d(t_wall *w_origin, t_data *data)
{
	t_wall		w;
	t_wall		text_extreme;

	w.right = horizontal_clipping(w_origin, w_origin->right, data);
	w.left = horizontal_clipping(w_origin, w_origin->left, data);
	if (w.left.x < 0 || w.right.x < 0)
		return ;
	text_extremes(w, w_origin, &text_extreme);
	text_destination(data, w, &text_extreme);
	texturing_algorithm(w, &text_extreme, data, w_origin);
}
