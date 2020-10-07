//
// Created by Hugor Chau on 10/7/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"
# include "../SDL/include/SDL.h"

void	remove_alpha(t_texture *texture)
{
	int		i;
	int		border;

	i = 0;
	border = texture->width * texture->height;
	while (i < border)
	{
		texture->bit_map[i] = texture->bit_map[i] << 8 >> 8;
		i++;
	}
}
