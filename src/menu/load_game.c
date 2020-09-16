#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	load_game(t_data *data)
{
	init_engine(data, data->engine);
	parse("./maps/3", data);
//	start_the_game(data);
}
