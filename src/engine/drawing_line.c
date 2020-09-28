//
// Created by Hugor Chau on 9/3/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	draw_line(t_line line, t_texture *texture, int color)
{
	int		x0 = line.start.x;
	int		x1 = line.end.x;
	int		y0 = line.start.y;
	int		y1 = line.end.y;

	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = y0;
	int x = x0;
	int diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	int dirx = x0 < x1 ? 1 : -1;
	if (abs(x1 - x0) > abs(y1 - y0)) {
		while (x != x1) {
			if (x >= 0 && y >= 0 && x < (int)texture->width && y < (int)texture->height)
				texture->bit_map[((x) + y * texture->width) - 0] = color;
			error = error + deltaerr;
			if (error >= (deltax + 1)) {
				y = y + diry;
				error = error - (deltax + 1);
			}
			x += dirx;
		}
	}
	else {
		int diry = y0 < y1 ? 1 : -1;
		int dirx = x1 - x0;
		if (dirx > 0)
			dirx = 1;
		if (dirx < 0)
			dirx = -1;
		int deltaerr = (deltax + 1);
		while (y != y1) {
			if (x >= 0 && y >= 0 && x < (int)texture->width && y < (int)texture->height)
				texture->bit_map[((x) + y * texture->width) - 0] = color;
			error = error + deltaerr;
			if (error >= (deltay + 1)) {
				x = x + dirx;
				error = error - (deltay + 1);
			}
			y += diry;
		}
	}
}
