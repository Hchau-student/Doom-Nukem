//
// Created by Hugor Chau on 9/18/20.
//

#ifndef DOOM_NUKEM_STRUCTURE_OBJECTS_H
#define DOOM_NUKEM_STRUCTURE_OBJECTS_H

//#include "map_struct.h"

struct	s_texture;
struct	s_vec2;
struct	s_wall;

typedef enum			e_health_obj_type
{
	MEDICINE,
	ARMOR,
	POISON
}						t_health_obj_type;

typedef enum			e_obj_type
{
	HEALTH_OBJ,
	POSTER_OBJ,
	WEAPON_OBJ,
	BULLETS_OBJ,
	MAX_OBJ
}						t_obj_type;

/*
**		there are bunch of struct in map_struct.h, if I'll add
**		something in there, it would be impossible to read!
*/

typedef struct			s_health_obj
{
	int8_t				common_type;
	int8_t				type;
	int32_t				plus;
	struct s_vec2		*place;
	struct s_texture	*texture;
}						t_health_obj;

/*
**		тупо для каста; все структуры obj ДОЛЖНЫ
**		начинаться с int8_t type для определения типа
**		и корректного каста
*/

typedef struct			s_obj
{
	int8_t				type;
}						t_obj;

/*
**		what if we could limit enemy's location
**		to one sector? It would be easier
*/

typedef struct			s_objects
{
	t_list		*sprites;
	t_list		*enemies;
}						t_objects;

typedef struct			s_poster
{
	struct s_wall		*wall;
	struct s_vec2		*left;
	struct s_vec2		*right;
	float				indent_bottom;
	float				indent_height;
}						t_poster;

typedef struct			s_bullets_obj
{
	int8_t				common_type;
	char				*weapon_name;
	int64_t				how_many;
	struct s_texture	*texture;
	struct s_texture	*textures[8];//на поворот лол вдруг прикрутим
}						t_bullets_obj;

#endif
