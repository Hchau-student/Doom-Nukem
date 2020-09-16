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

/*
**		sorry not sorry; need this for my calculations
*/

# define DEGREES_45		0.785398
# define TANGENT_45		1.61977519054

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
//	WEAPON_SHOOT = 2,
	WEAPON_FRAMES = 2
}						t_weapon_texture;

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
	HEALTH_MAX = 6,
	HEALTH_100 = 5,
	HEALTH_80 = 4,
	HEALTH_60 = 3,
	HEALTH_40 = 2,
	HEALTH_20 = 1,
	HEALTH_0 = 0
}						t_health_texture;

typedef enum			e_player_state
{
	MAX_STATE = 5,
	PLAYER_LEFT = 0,
	PLAYER_RIGHT = 1,
	PLAYER_SMILE = 2,
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
//	t_texture	*remainder;
	void		(*hit)(struct s_shoot *shoot, void *obj);
	int32_t		current_sector;
}						t_shoot;

typedef struct			s_weapon
{
	t_texture			*texture[WEAPON_FRAMES];//do we want to animate this?
	t_weapon_texture	frame;
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

/*
**		to make whole this thing invisible - just ask wall to return
**		portal->to(portal) and see, what it does :)
*/

struct					s_portal
{
	t_wall			*wall;
	t_wall			(*to)(t_portal *portal);
	t_wall_type		type;
};

struct					s_wall//wall->portal.to(wall->portal)
{
	t_vec3		left;
	t_vec3		right;
	float		length;
	t_portal	*portal;//wall type is in here!
	t_sector	*sector;
	t_texture	*textures[3];
};

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
	int8_t				health;
	int8_t				armor;
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
	int32_t		light;//light color???
}						t_sector_render;

/*
**	what if we could throw those walls to the t_sector_render?
**	t_twlist		*walls;
**	int32_t			walls_count;
**	t_texture		*textures[2];
**	neighbors are for searching current sector for the player; won't be sorted
**
*/

struct					s_sector
{
	int				id;
	t_twlist		*walls;
	int32_t			walls_count;
	t_texture		*textures[2];
	t_list			*neighbors;
	float			floor_height;
	float			ceiling_height;
	t_objects		*objects;
	t_sector_type	type;//??? Do we need this?
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
	t_player		*player;
	t_list			*enemies;
	t_list			*shoots;
}						t_engine;

/*
**		initialization
*/

void	start_the_game(t_data *data);
void	init_engine(t_data *data, t_engine *engine);
void	engine_key_event(SDL_Event *event, t_data *data);
void	engine_mouse_event();

/*
**		main loop,
**		2d paintings (remake it, please, let them be beautiful!),
**		3d walls
*/

/*
**		parse
*/

void		parse(char *str, t_data *data);
void		parse_wall();
void		parse_sector();

#endif
