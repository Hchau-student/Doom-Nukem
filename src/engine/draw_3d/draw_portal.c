//
// Created by Hugor Chau on 9/30/20.
//

#include "../../../Include/doom_nukem.h"
#include "../../../Include/map_struct.h"
#include "../../../Include/renderer.h"

void	prepare_portal(float h1, float h2, t_wall *w, t_draw_wall *wall, t_data *data)
{
	t_sector	*sector;

	wall->wall_res = *w;
	sector = ft_memalloc(sizeof(t_sector));
	*sector = *w->sector;
	wall->wall_res.sector = sector;
	if (h1 < h2)
	{
		wall->wall_res.floor_height = h1;
		wall->wall_res.ceiling_height = h2;
	}
	else
	{
		wall->wall_res.floor_height = h2;
		wall->wall_res.ceiling_height = h1;
	}
	wall->wall_res.height = wall->wall_res.ceiling_height + wall->wall_res.floor_height;
}

void	move_borders(t_wall *borders, t_vec2 *step)
{
	borders->left.x = (int)borders->left.x + 1;
	borders->left.y += step->y + borders->left.z;
	borders->right.y -= borders->left.z;
}

void	prepare_borders(t_draw_wall *wall, t_data *data)
{
	float		common_wall_h;

	common_wall_h = (wall_h(wall->wall_res.left, wall->wall_res.height, data->engine->player)
	 - wall_h(wall->wall_res.right, wall->wall_res.height, data->engine->player));
	wall->shift_step.y = (common_wall_h) / (wall->end_x - wall->wall_borders.left.x);
	wall->shift_step.x = (1.0) / (wall->end_x - wall->wall_borders.left.x);
	wall->wall_borders.left.z = (wall->wall_borders.left.z
					  - wall->wall_borders.right.z) / (wall->end_x - wall->wall_borders.left.x);
}

void	inverse_steps_portal(float *angle, t_draw_wall *wall)
{
	wall->shift_step.y *= -1;
	*angle = 1;
	wall->shift_step.x *= -1;
	wall->wall_borders.left.z *= -1;
}

void	wall_extremes_portal(t_data *data, t_draw_wall *wall)
{
	float	left;
	float	right;
	float	left_h;
	float	right_h;

	left = (float)SCREEN_WIDTH * find_angle(data, wall->wall_res.left);
	right = (float)SCREEN_WIDTH * find_angle(data, wall->wall_res.right);
	right_h = wall_h(wall->wall_res.right, wall->wall_res.height, data->engine->player);
	left_h = wall_h(wall->wall_res.left, wall->wall_res.height, data->engine->player);
	wall->end_x = right;
	wall->wall_borders.left.x = left;
	wall->wall_borders.left.z = wall_h(wall->wall_res.left, -(float)wall->wall_res.floor_height, data->engine->player);
	wall->wall_borders.right.z = wall_h(wall->wall_res.right, -(float)wall->wall_res.floor_height, data->engine->player);
	wall->wall_borders.left.y = ZERO_FLOOR - left_h - wall->wall_borders.left.z;
	wall->wall_borders.right.y = ZERO_FLOOR + wall->wall_borders.left.z;
	if (wall->wall_borders.left.x > wall->end_x)
	{
		wall->end_x = left;
		wall->wall_borders.left.x = right;
		wall->wall_borders.left.y = ZERO_FLOOR - right_h - wall->wall_borders.right.z;
		wall->wall_borders.right.y = ZERO_FLOOR + wall->wall_borders.right.z;
	}
}

void	prepare_all_portal_data(t_data *data, t_draw_wall *wall, float *angle)
{
	wall_extremes_portal(data, wall);
	prepare_borders(wall, data);
	wall->current_x = wall->wall_borders.left.x;
	wall->wall_borders.right.x = (int)wall->current_x;
	*angle = 0;
	if (find_angle(data, wall->wall_res.left) > find_angle(data, wall->wall_res.right))
		inverse_steps_portal(angle, wall);
}

void	portal_texturing(t_wall w, t_wall *text_extremes, t_data *data, t_wall *w_origin)
{
	t_draw_wall		down_part;
	t_draw_wall		up_part;
	float			angle;

	prepare_portal(w.sector->floor_height, w.portal_to->sector->floor_height/* - data->engine->player->current_sector->floor_height - 20*/, &w, &down_part, data);
	prepare_portal(w.sector->ceiling_height, w.portal_to->ceiling_height/* - data->engine->player->current_sector->floor_height - 20*/, &w, &up_part, data);
	prepare_all_portal_data(data, &down_part, &angle);
	prepare_all_portal_data(data, &up_part, &angle);
	while (up_part.current_x < up_part.end_x)
	{
		down_part.wall_borders.right.x = (int)up_part.current_x;
		up_part.wall_borders.right.x = (int)up_part.current_x;
		data_text(down_part.wall_borders, find_textel(angle, text_extremes->left,
					text_extremes->right, w_origin->textures[WALL_TEXT]->width), w_origin->textures[DOWN_TEXT], data);
		data_text(up_part.wall_borders, find_textel(angle, text_extremes->left,
					text_extremes->right, w_origin->textures[WALL_TEXT]->width), w_origin->textures[UP_TEXT], data);
		move_borders(&down_part.wall_borders, &down_part.shift_step);
		move_borders(&up_part.wall_borders, &up_part.shift_step);
		angle += down_part.shift_step.x;
		up_part.current_x = (int)up_part.current_x + 1;
	}
}
