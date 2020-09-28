//
// Created by Hugor Chau on 9/23/20.
//
#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
//проверить, все ли сектора являются замкнутыми фигурами
//проверить, не пересекают ли стены других секторов друг друга

void		check_sector_crossing()
{

}

void		check_sector_data(struct s_sector *sector, struct s_data *data)
{
	t_sector	*s;

	safe_call_int(0, "check", data);
	s = sector;
}
//проверить, все ли порталы есть в двух (и только двух) секторах