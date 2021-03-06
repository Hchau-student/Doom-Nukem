//
// Created by Hugor Chau on 9/29/20.
//

#ifndef DOOM_NUKEM_STRUCTURE_RENDERER_H
#define DOOM_NUKEM_STRUCTURE_RENDERER_H

#include "map_struct.h"

#define ZERO_FLOOR	(float)SCREEN_HEIGHT / 2

typedef struct		s_draw_wall
{
	t_wall			wall_res;
	t_wall			wall_borders;
	t_vec2			shift_step;
	float			angle;
	float			end_x;
	float			start_x;
	float			current_x;
}					t_draw_wall;

/*
**		wall destination
*/


/*
**		draw 3d
*/

t_vec3			horizontal_clipping(t_wall *full_wall,
									  t_vec3 original_dot, t_data *data);
void			draw_wall_3d(t_wall *w_origin, t_data *data);

/*
**		wall preparations
*/

void	text_destination(t_data *data, t_wall w, t_wall *text_extremes);
void	wall_extremes(t_data *data, t_wall w, t_wall *borders, float *end_x);
void	text_extremes(t_wall w, t_wall *w_origin, t_wall *text_extremes);
float 	wall_h(t_vec3 point, float width, t_player *player);
float	find_angle(t_data *data, t_vec3 w1);

/*
**		draw single wall
*/

void	data_text(t_wall borders, float text_x, t_texture *wall_texture, t_data *data);
float 	find_textel(float angle, t_vec3 textels, t_vec3 dist, int text_max);
void	inverse_steps(t_vec2 *step, float *angle, t_wall *borders);
void	texturing_algorithm(t_wall w, t_wall *text_extremes, t_data *data, t_wall *w_origin);
void	portal_texturing(t_wall w, t_wall *text_extremes, t_data *data, t_wall *w_origin);


#endif //DOOM_NUKEM_STRUCTURE_RENDERER_H
