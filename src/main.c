//
// Created by Hugor Chau on 9/14/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"
# include "../SDL/include/SDL.h"

int		main()
{
	t_data		data;

	init_data(&data);
	menu(&data);
	main_loop(&data);
}
