//
// Created by Hugor Chau on 9/28/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/map_struct.h"
#include "../../../Include/renderer.h"

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
	if (y < 0)
	{
		y1 += y1 * step * y * -1;
		y = 0;
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

void	inverse_steps(t_vec2 *step, float *angle, t_wall *borders)
{
	step->y *= -1;
	*angle = 1;
	step->x *= -1;
	borders->left.z *= -1;
}

void	texturing_algorithm(t_wall w, t_wall *text_extremes, t_data *data, t_wall *w_origin)
{
	t_wall		borders;
	float		end_x;
	t_vec2		step;
	float		angle;
	float		t_start_x;

	wall_extremes(data, w, &borders, &end_x);
	step.y = (wall_h(w.left, w.height, data->engine->player)
			  - wall_h(w.right, w.height, data->engine->player)) / (end_x - borders.left.x);
	borders.left.z = (borders.left.z
					  - borders.right.z) / (end_x - borders.left.x);
	/*
	**	TODO step.y for borders.right.y
	*/
	angle = 0;
	step.x = (1.0) / (end_x - borders.left.x);
	if (find_angle(data, w.left) > find_angle(data, w.right))
		inverse_steps(&step, &angle, &borders);
	while (borders.left.x < end_x)
	{
		borders.right.x = (int)borders.left.x;
		t_start_x = find_textel(angle, text_extremes->left,
			text_extremes->right, w_origin->textures[WALL_TEXT]->width);
		data_text(borders, t_start_x, w_origin->textures[WALL_TEXT], data);
		borders.left.x = (int)borders.left.x + 1;
		borders.left.y += step.y + borders.left.z;
		borders.right.y -= borders.left.z;
		angle += step.x;
	}
}

void	draw_wall_3d(t_wall *w_origin, t_data *data)
{
	t_wall		w;
	t_wall		text_extreme;

	w = *w_origin;
	w.right = horizontal_clipping(w_origin, w_origin->right, data);
	w.left = horizontal_clipping(w_origin, w_origin->left, data);
	if (w.left.x < 0 || w.right.x < 0)
		return ;
	text_extremes(w, w_origin, &text_extreme);
	text_destination(data, w, &text_extreme);
	texturing_algorithm(w, &text_extreme, data, w_origin);
}
