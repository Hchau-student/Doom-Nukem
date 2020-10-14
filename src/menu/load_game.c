#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	load_game(t_data *data)
{
	init_engine(data);
	parse(data->menu.cur_map_name, data);
	start_the_game(data);
}
