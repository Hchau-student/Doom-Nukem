#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void	load_game(t_data *data)
{
	init_engine(data);
	parse("/Users/hchau/Downloads/Doom-Nukem-structure/parse_maps/1", data);
	start_the_game(data);
}
