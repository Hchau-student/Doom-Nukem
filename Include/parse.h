//
// Created by Hugor Chau on 9/16/20.
//


#ifndef DOOM_NUKEM_STRUCTURE_PARSE_H
#define DOOM_NUKEM_STRUCTURE_PARSE_H

#include "doom_nukem.h"
#include "map_struct.h"

/*
**		we don't actually know, how much of everything do we have
**		while we parse, so lists indeed!
*/

//void		parse_wall();
//void		parse_sector();

/*
**		это для утечек
*/

typedef struct		s_parse
{
	t_list			*gnl_str;
	flag			gnl_read_flag;
	char			brackets;
}					t_parse;

#endif //DOOM_NUKEM_STRUCTURE_PARSE_H
