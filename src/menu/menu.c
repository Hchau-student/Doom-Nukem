#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
# include "../../SDL/include/SDL.h"


/*
**		уже здесь должен быть main_loop и обработчик событий;
**		нужно отрисовать менюху, например, и только потом,
**		если кнопка "загрузи карту" будет нажата,
**		загрузить блин эту карту
*/

void	init_buttons(t_data *data)
{
	int				i;
	static char		*names[B_COUNT] = {"start_new_game", "chose_level", "level_editor",
							"game_preferences", "exit"};

	i = 0;
	while (i < B_COUNT)
	{
		data->menu.buttons[i].height = (SCREEN_HEIGHT - 100) / B_COUNT;
		data->menu.buttons[i].width = (SCREEN_WIDTH - 100);
		data->menu.buttons[i].x = (50);
		data->menu.buttons[i].y = (50) + i * (SCREEN_HEIGHT - 100) / B_COUNT;
		data->menu.buttons[i].brightness = 0x60;
		data->menu.buttons[i].texture = find_texture_by_name(names[i], data);
		remove_alpha(data->menu.buttons[i].texture);
		i++;
	}
}

void	init_menu(t_data *data)
{
	data->menu.background = find_texture_by_name("menu_background", data);
	data->menu.pressed_button = -1;
	data->sdl->mouse.is_moved = FALSE;
	init_buttons(data);
}

void	menu(t_data *data)
{
	init_menu(data);
	clear_keysum(data);
	data->go_to->mouse_event = &engine_mouse_event;
	data->go_to->key_event = &engine_key_event;
	data->go_to->condition = &menu_condition;
//	draw_background;
//	load_game(data);
//	data->condition = &draw_menu;
}
