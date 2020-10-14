//
// Created by Hugor Chau on 10/7/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		chose_layers(t_data *data)
{
	int		i;

	i = 0;
	put_layer(data->sdl->tex,
			  data->menu.background->bit_map,
			  data->menu.background->width,
			  data);
	while (i < B_COUNT)
	{
		change_button_brightness(&data->menu.buttons[i]);
		scale_image(data->menu.buttons[i].texture, data->sdl->layers->menu, (t_square){(t_vec2){data->menu.buttons[i].x, data->menu.buttons[i].y},
		(t_vec2){data->menu.buttons[i].x + data->menu.buttons[i].width, data->menu.buttons[i].y + data->menu.buttons[i].height}});
		i++;
	}
	put_layer(data->sdl->tex,
			  data->sdl->layers->menu->bit_map,
			  data->sdl->layers->menu->width,
			  data);
}

static void		chose_button(t_data *data)
{
	if (data->sdl->key_pressed[DOWN_ARROW])
		data->menu.pressed_button++;
	if (data->sdl->key_pressed[TOP_ARROW])
		data->menu.pressed_button--;
	if (data->menu.pressed_button >= B_COUNT)
		data->menu.pressed_button = 0;
	if (data->menu.pressed_button < 0 && data->sdl->key_pressed[TOP_ARROW] == TRUE)
		data->menu.pressed_button = B_COUNT - 1;
	if (data->menu.pressed_button >= 0 && data->menu.pressed_button < B_COUNT)
		data->menu.buttons[data->menu.pressed_button].brightness = 0xFF;
	data->sdl->key_pressed[DOWN_ARROW] = FALSE;
	data->sdl->key_pressed[TOP_ARROW] = FALSE;
}

void		change_condition(t_data *data)
{
	if (data->sdl->key_pressed[ENTER] == FALSE && data->sdl->mouse.is_pressed == FALSE)
		return;
	if (data->menu.pressed_button < 0
			|| data->menu.pressed_button > B_COUNT)
		return;
	if (data->menu.pressed_button == B_NEW_GAME)
	{
		data->menu.pressed_button = -1;
		load_game(data);
	}
	if (data->menu.pressed_button == B_EXIT)
	{
		data->menu.pressed_button = -1;
		remove_data(data);
	}
	if (data->menu.pressed_button == B_LEVEL_EDITOR)
	{
		data->menu.pressed_button = -1;
		level_editor(data);
	}
}

void		menu_condition(t_data *data)
{
	prepare_all_buttons(data->menu.buttons, B_COUNT);
	if (data->sdl->mouse.is_moved != FALSE)
		buttons_move_mouse(data->menu.buttons,
		B_COUNT, &data->sdl->mouse, &data->menu.pressed_button);
	chose_button(data);
	chose_layers(data);
	change_condition(data);
	update_texture(data);
}
