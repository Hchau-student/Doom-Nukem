//
// Created by Hugor Chau on 9/18/20.
//

#ifndef DOOM_NUKEM_STRUCTURE_OBJECTS_H
#define DOOM_NUKEM_STRUCTURE_OBJECTS_H

#include "map_struct.h"

/*
**		there are bunch of struct in map_struct.h, if I'll add
**		something in there, it would be impossible to read!
*/

typedef struct			s_poster
{
	t_wall				*wall;
	s_vec2				left;
	s_vec2				right;
	float				indent_bottom;
	float				indent_height;
}						t_poster;

#endif //DOOM_NUKEM_STRUCTURE_OBJECTS_H
