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


struct			s_vec2;
typedef struct	s_data	t_data;
struct			s_engine;
struct			s_wall;

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

typedef struct		s_fonts
{
	int 			pref;
}					t_fonts;

typedef struct		s_texture
{
	int 			width;
	int 			height;
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

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Rect		*rect;
	SDL_Texture		*color_tex;
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
t_texture		**init_textures(char *path, t_data *data);
int				open_file(char *map_name, t_data *data);
t_texture		*find_texture_by_name(char *name, t_data *data);

/*
**		clear (leaks management)
*/

void			remove_sdl(t_sdl **remove);
void			remove_data(t_data *data);
void			remove_textures(t_data *data);

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

int				scale_image(t_texture *texture, t_data *data,
							struct s_vec2 start, struct s_vec2 end);
void			update_texture(t_data *data);
void			draw_line(struct s_wall *w, uint32_t **pix_array, int color);
void			draw_minimap(t_data *data);

#endif
