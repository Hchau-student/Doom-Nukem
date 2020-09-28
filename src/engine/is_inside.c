#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
/*
**		second variant
** 		(as simple as previous, but includes
** 		vector cross product and WORKS WITH FLOATS)
**		needs for extra tests; the whole code need to be cleared
*/

/*
**		using structs:
**
** 		struct vertex { float x; float y }
*/

static float	cross_product_2d(const t_vec2 *v1, const t_vec2 *v2)
{
	if (v1->y < v2->y)
		return (v1->x * v2->y - v1->y * v2->x);
	return (v2->x * v1->y - v2->y * v1->x);
}

/*
**		using structs:
**
**  	struct wall { vertex left; vertex right; }
*/

int				is_rhs(float x, float y, t_wall *wal)
{
	t_vec2		v1;
	t_vec2		v2;

	v1.x = wal->left.x - x;
	v2.x = wal->right.x - x;
	v1.y = wal->left.y - y;
	v2.y = wal->right.y - y;
	return (cross_product_2d(&v1, &v2) <= 0 ? 1 : 0);
}

/*
**		using structs:
**
**		struct data { map *m; } //only one sector for now
** 		struct map { wall *walls; int w_count; }
**		all walls in sector as walls[w_count + 1]
*/

uint32_t		is_inside(float x, float y, t_sector_render *sector)
{
	t_wall	*wal;
	int		i;
	int		cross_counter;

	wal = sector->walls;
	i = sector->walls_count;
	cross_counter = 0;
	while (i >= 0)
	{
		if ((y - wal->left.y) * (y - wal->right.y) < 0)
		{
			if (x > wal->left.x && x > wal->right.x)
			{
				cross_counter += 1;
			}
			else if (((x - wal->left.x)) * ((x - wal->right.x)) < 0)
			{
				cross_counter += is_rhs(x, y, wal);
			}
		}
		wal++;
		i--;
	}
	return (cross_counter);
}
