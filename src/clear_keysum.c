//
// Created by Hugor Chau on 9/29/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"
# include "../SDL/include/SDL.h"

void	clear_keysum(t_data *data)
{
	uint32_t	i;

	i = 0;
	ft_memset(data->sdl->key_pressed, FALSE, sizeof(int) * MAX_KEYCODE);
}