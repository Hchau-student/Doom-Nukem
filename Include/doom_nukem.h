/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 12:46:31 by wpoudre           #+#    #+#             */
/*   Updated: 2020/09/09 12:46:34 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H

# define DOOM_NUKEM_H
# define WIN_TITLE "HAIL TO THE KING"
# include <stdint.h>
# include "../libft/libft.h"
# include "../SDL/include/SDL.h"
# include "parse.h"
# define SCREEN_WIDTH	600
# define SCREEN_HEIGHT	500

struct			s_vec2;
typedef struct	s_data	t_data;
struct			s_engine;
struct			s_wall;
struct			s_square;
#define MINIMAP_H	200
#define MINIMAP_W	200

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum	e_screen_status
{
	MAIN_MENU,
	LEVEL_EDITOR,
	LEVEL_LODE,
	GAME,
	PAUSE_MENU,
	PREFERENCES
}				t_screen_status;

//// TODO разобраться со шрифтами в SDL
//
//typedef struct		s_line
//{
//	struct s_vec2	start;
//	struct s_vec2	end;
//}					t_line;

typedef struct		s_fonts
{
	int 			pref;
}					t_fonts;

typedef struct		s_texture
{
	uint32_t		width;
	uint32_t		height;
	uint32_t		*bit_map;
	char			*text_name;
}					t_texture;

/*
**		кнопки меню, которые можно нажать мышью, со своей текстурой
*/

typedef struct		s_button
{
	int 			x;
	int 			y;
	int 			width;
	int 			height;
	t_bool			brightness;
	uint32_t		*bit_map;
}					t_button;

typedef struct		s_menu
{

}					t_menu;

typedef struct		s_mouse
{
	int				x;
	int				y;
	t_bool			is_pressed;
}					t_mouse;

typedef struct		s_layers
{
	t_texture		*minimap;
	t_texture		*hud;
	t_texture		*draw_3d;
}					t_layers;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Rect		*rect;
	t_layers		*layers;
//	t_texture		*doom_texture;
	SDL_Texture		*target_texture;
	SDL_Surface		*surf;
	SDL_Texture		*tex;
	int				indian;
	uint32_t		*color_buffer;
}					t_sdl;

/*
**	лень писать по-английски; закинем в лупу эти функции, чтобы
**	не париться и обновлять изображение и производить действия по текущему
**	состоянию (menu/load_game/start_game и т.д.); в момент смены состояния
**	игры перепривязываем указатели на функции - пауза, игра, загрузка и т.д.;
**	так мы сможем разделить и обособить блоки, не нагромождая кучу if/else
*/

typedef struct		s_main_actions
{
	void		(*condition)(struct s_data *draw);
	void		(*key_event)(SDL_Event *event, t_data *data);
	void		(*mouse_event)();
}					t_main_actions;

/*
**		текстуры для движка хранятся в движке
*/

struct			s_data
{
	t_sdl			*sdl;
	t_texture		**textures;
	struct s_engine	*engine;
	t_main_actions	*go_to;
};

/*
**		initialize
*/

void			init_data(t_data *data);
void			init_sdl(t_data *data, char *name);
void			init_sdl_layers(t_data *data);
t_texture		**init_textures(char *path, t_data *data);
t_texture		*init_single_texture(char *name, t_data *data);
int				open_file(char *map_name, t_data *data);
t_texture		*find_texture_by_name(char *name, t_data *data);

/*
**		clear (leaks management)
*/

void			remove_sdl(t_sdl **remove);
void			remove_data(t_data *data);
void			remove_textures(t_data *data);
void			remove_layers(t_layers **layers);

/*
**		primitive error management
*/

int 			safe_call_int(int res, char *message, t_data *data);
void			*safe_call_ptr(void *res, char *message, t_data *data);

/*
**		menu
*/

void			menu(t_data *data);
void			load_game(t_data *data);
void			menu_key_event(SDL_Event *event, t_data *data);
void			menu_mouse_event();

/*
**		main loop
*/

void			main_loop(t_data *data);

/*
**		етих функций пока нет
*/

void			start_the_game(t_data *data);
void			pause_game(t_data *data);
void			map_editor(t_data *data);

/*
**		common draw functions
*/

int				scale_image(t_texture *src, t_texture *dst,
							struct s_square borders);
void			update_texture(t_data *data);
void			put_layer(SDL_Texture *texture, uint32_t *bitmap,
								uint32_t width, t_data *data);
void			draw_3d(t_data *data);
#endif
