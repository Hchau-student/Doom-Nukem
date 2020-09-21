/*
**		we definitely do need this functions -
**		to scale square images to different sizes
**		right into main bitmap. It would be useful
**		for menu buttons, player's hud or whatever.
**		I'm not sure in which directory it should exist,
**		so for now it would be just in ./src.
*/

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

static int		check_borders_by_screen(t_vec2 *start, t_vec2 *end)
{
	if (start->x > end->x)
		return (-1);
	if (start->y > end->y)
		return (-1);
	if (start->x < 0 || start->x >= SCREEN_WIDTH)
		return (-1);
	if (end->x < 0 || end->x >= SCREEN_WIDTH)
		return (-1);
	if (end->y < 0 || end->y >= SCREEN_HEIGHT)
		return (-1);
	if (start->y < 0 || start->y >= SCREEN_HEIGHT)
		return (-1);
	return (0);
}

int				scale_image(t_texture *texture, t_data *data,
							   t_vec2 start, t_vec2 end)
{
	float	i;
	float	j;
	t_vec2	iter;
	int		start_x;

	j = 0;
	iter.x = texture->width / (end.x - start.x);
	iter.y = texture->height / (end.y - start.y);
	if (check_borders_by_screen(&start, &end))
		return (-1);
	while (j < texture->height)
	{
		i = 0;
		start_x = start.x;
		while (i < texture->width)
		{
			data->sdl->color_buffer[(start_x + (int)start.y * SCREEN_WIDTH)] =
					texture->bit_map[((int)i + (int)j * texture->width)];
			i += iter.x;
			start_x += 1;
		}
		start.y += 1;
		j += iter.y;
	}
	return (0);
}
