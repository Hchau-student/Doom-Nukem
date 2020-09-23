/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:23:25 by wpoudre           #+#    #+#             */
/*   Updated: 2020/09/09 13:23:27 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCT_H

# define MAP_STRUCT_H

# include "doom_nukem.h"
# include "../libft/libft.h"
# include <math.h>
# include "../SDL/include/SDL.h"
# define SCREEN_WIDTH	600
# define SCREEN_HEIGHT	500
# define CENTRE_W		SCREEN_WIDTH / 2
/*
**		sorry not sorry; need this for my calculations
*/

# define DEGREES_45		0.785398
# define TANGENT_45		1.61977519054

/*
**		some defines for static amount
*/

# define MAX_WEAPONS	3

/*
**		DOOR - horizontal or what?
**		WINDOW - Портал с 2 текстурами
**		GLASSY - formally it should behave as a portal,
**		but should to be sorted separately
*/

typedef enum			e_wall_type
{
	WALL,
	DOOR,
	WINDOW,
	PORTAL,
	GLASSY
}						t_wall_type;

/*
**		SEC_GLASSY, it would effect to the sorting part
**		SEC_WATER ????? Or let's consider one height level as water by default
*/

typedef enum			e_sector_type
{
	SEC_NORMAL,
	SEC_GLASSY,
	SEC_WATER
}						t_sector_type;

typedef enum			e_texture_type
{
	WALL_TEXT = 0,
	UP_TEXT = 0,
	MIDDLE_TEXT = 1,
	DOWN_TEXT = 2,
	FLOOR_TEXT = 0,
	CEILING_TEXT = 1
}						t_texture_type;

typedef enum			e_enemy_texture
{
	ENEMY_SIDE_0 = 0,
	ENEMY_SIDE_45 = 1,
	ENEMY_SIDE_90 = 2,
	ENEMY_SIDE_135 = 3,
	ENEMY_SIDE_180 = 4,
	ENEMY_SIDE_225 = 5,
	ENEMY_SIDE_270 = 6,
	ENEMY_SIDE_315 = 7,
	ENEMY_SIDES = 8,
	ENEMY_FRAME_1 = 0,
	ENEMY_FRAME_2 = 1,
	ENEMY_FRAMES = 2
}						t_enemy_texture;

typedef enum			e_weapon_texture
{
	WEAPON_0_FRAME = 0,
	WEAPON_1_FRAME = 1,
	WEAPON_FRAMES = 2
}						t_weapon_texture;

typedef enum			e_animate_shoot
{
	REMAINDER_SHOOT_ANIMATE = 2,
	REMAINDER_SHOOT_0 = 0,
	REMAINDER_SHOOT_1 = 1
}						t_animate_shoot;

/*
**	it is from mandatory part: player should be able to swim or fly
*/

//typedef enum			e_gravity
//{
//	NORMAL,
//	SWIMMING,
//	FALLING,
//	RUNNING
//}						t_gravity;

typedef enum			e_health_texture
{
	HEALTH_MAX = 5,
	HEALTH_100 = 4,
	HEALTH_80 = 3,
	HEALTH_60 = 2,
	HEALTH_40 = 1,
	HEALTH_20 = 0,
}						t_health_texture;

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

typedef enum			e_player_state
{
	MAX_STATE = 5,
	PLAYER_LEFT = 0,
	PLAYER_RIGHT = 1,
	PLAYER_NORMAL = 2,
	PLAYER_HURT = 3,
	PLAYER_KILL = 4,
}						t_player_state;

typedef struct			s_vec2
{
	float				x;
	float				y;
}						t_vec2;

typedef struct			s_vec3
{
	float	x;
	float	y;
	float	z;
}						t_vec3;

/*
**		every part of render reminds a square,
**		so it could be useful to have such a
**		square before render;
**		there are 4 2d points, soooo
**		I hope you've got it
*/

typedef struct			s_polygon
{
	t_vec2		left_bottom;
	t_vec2		left_top;
	t_vec2		right_bottom;
	t_vec2		right_top;
}						t_polygon;

typedef struct			s_shoot
{
	t_vec3		position;
	t_vec3		direction;
	t_texture	*texture;
	t_texture	*remainder[REMAINDER_SHOOT_ANIMATE];
	void		(*hit)(struct s_shoot *shoot, void *obj);
	int32_t		current_sector;
}						t_shoot;

typedef struct			s_weapon
{
	int8_t				common_type;
	char				*name;
	t_texture			*texture[WEAPON_FRAMES];//do we want to animate this?
	int64_t				frame;
	int64_t				bullets;
	int64_t				bullets_max;
	char				i_have_it;
	t_shoot				*shoot;
	struct s_weapon		*next;
	struct s_weapon		*prev;
}						t_weapon;

typedef struct			s_enemy
{
	t_texture			*texture[ENEMY_SIDES][ENEMY_FRAMES];//do we want to rotate or animate it?
	t_enemy_texture		side;
	t_enemy_texture		frame;
	int8_t				health;
}						t_enemy;

typedef struct s_sector	t_sector;
typedef struct s_portal	t_portal;
typedef struct s_wall	t_wall;

struct					s_wall
{
	int8_t		type;
	t_vec3		left;
	t_vec3		right;
	float		length;
	t_wall		*portal_to;
	t_sector	*sector;
	t_texture	*textures[3];
};

typedef struct			s_health_obj
{
	int8_t				common_type;
	int8_t				type;
	int32_t				plus;
	t_vec2				*place;
	t_texture			*texture;
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

typedef struct			s_move
{
	float		knees;
	float		ducking;
	float		eyes;
//	int8_t		gravity;
}						t_move;

/*
**		heads-up display (hud)
*/

typedef struct			s_display_hud
{
	t_texture			*display;//main texture
	t_weapon			*weapon;
	t_texture			*player_texture[HEALTH_MAX][MAX_STATE];
	t_texture			*armor_texture;
	int8_t				health;
	int8_t				armor;
	int8_t				state;
}						t_display_hud;

/*
**		fov could be replaced, buuuuut carefully;
**		current_sector - should it be int (sec id) or link to the sector?
*/

typedef struct			s_player
{
	t_vec2			position;
	t_vec2			direction_angle;
	t_move			*move;
	float			fov;
	t_display_hud	*hud;
	int32_t			current_sector;
	t_sector		*cur_sec;
}						t_player;

/*
**		it is not necessary, but could be more comfortable,
**		because, I guess, we would need it only in iterations;
**		so the first render-part of any kind of sector could be described as
*/

typedef struct			s_sector_render
{
	t_twlist	*walls;
	int32_t		walls_count;
	float		floor_height;
	float		ceiling_height;
	t_texture	*textures[2];
	uint32_t		light;//light color???
}						t_sector_render;

/*
**	what if we could throw those walls to the t_sector_render?
**	t_twlist		*walls;
**	int32_t			walls_count;
**	t_texture		*textures[2];
**	neighbors are for searching current sector for the player; won't be sorted
*/

struct					s_sector
{
	int				id;
	t_texture		*textures[2];
	t_list			*neighbors;
	t_sector_render	*render;
	float			floor_height;
	float			ceiling_height;
	t_list			*objects;
	t_sector_type	type;
	//don't you wanna add gravity in here?
};

/*
**		the main structure of engine
*/

typedef struct			s_engine
{
	t_sdl			*sdl;
	t_texture		**textures;
	t_sector		*sectors;
	uint32_t		sectors_count;
	t_player		*player;
	t_list			*enemies;
	t_list			*shoots;
}						t_engine;

/*
**		Да, это костыль. Мне нужно распарсить
**		сектора, которые стоит поместить в массив,
**		но количество секторов заранее неизвестно.
**		Есть вариант сразу инициализировать огромный массив
**		секторов или положить всё в листы, а потом переложить
**		в массив. Либо в огромный массив, а потом его
**		урезать. Мне больше нравится варик с листами, но
**		их придётся чистить, а это проблема - ссылки на листы
**		не могут лежать внутри основной структуры, это будет
**		уродством.
*/
//
//typedef struct		s_parse
//{
//	t_list			*sectors;
//}					t_parse;

/*
**		initialization
*/

void			start_the_game(t_data *data);
void			init_engine(t_data *data);
t_weapon		*init_weapon(t_data *data);
t_player		*init_player(t_data *data);
t_display_hud	*init_hud(t_data *data);

/*
**		leaks management
*/

void			remove_hud(t_display_hud **hud);
void			remove_player(t_player **player);
void			remove_engine(t_data *data);

/*
**		main loop,
**		2d paintings (remake it, please, let them be beautiful!),
**		3d walls
*/

void			engine_key_event(SDL_Event *event, t_data *data);
void			engine_mouse_event();

/*
**		parse
*/

void			parse(char *str, t_data *data);
void			parse_wall(char *str, int fd, t_sector *sector, t_data *data);
void			parse_sector(char *str, int fd, t_data *data);
void			parse_line(char *str, int fd, t_sector *sector, t_data *data);
void			parse_objects(char *str, int fd, t_sector *sector, t_data *data);
void			*parse_object(char *str, int fd, t_sector *sector, t_data *data);
t_twlist		*parse_single_wall(char *str, int fd, t_sector *sector, t_data *data);
void			parse_player(char *str, int fd, t_data *data);
void			parse_hud(char *str, int fd, t_data *data);
void			parse_player_line(char *str, int fd, t_data *data);

/*
**		parse tools
*/

char			*skip_to(char *check, char *original);
int				parse_num(char *str, uint32_t *box);
char			*parse_float(char *str, float *box);
int				check_line(char *should_be, char *check);

/*
**		simple drawings
*/

void			draw_hud(t_display_hud *hud, t_data *data);

/*
**		tools for objects
*/

t_weapon		*find_weapon_by_name(char *name, t_data *data);

#endif
