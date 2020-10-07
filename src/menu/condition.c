//
// Created by Hugor Chau on 10/7/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

static void		change_brighthess(t_button *button)
{
	int		i;
	int		border;

	i = 0;
	border = button->texture->height * button->texture->width;
	while (i < border)
	{
		button->texture->bit_map[i] = button->brightness << 24 | button->texture->bit_map[i];
		i++;
	}
}

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
		change_brighthess(&data->menu.buttons[i]);
		scale_image(data->menu.buttons[i].texture, data->sdl->layers->menu, (t_square){(t_vec2){data->menu.buttons[i].x, data->menu.buttons[i].y},
		(t_vec2){data->menu.buttons[i].x + data->menu.buttons[i].width, data->menu.buttons[i].y + data->menu.buttons[i].height}});
		i++;
	}
	put_layer(data->sdl->tex,
			  data->sdl->layers->menu->bit_map,
			  data->sdl->layers->menu->width,
			  data);
}

static void		prepare_buttons(t_data *data)
{
	int		i;

	i = 0;
	while (i < B_COUNT)
	{
		remove_alpha(data->menu.buttons[i].texture);
		data->menu.buttons[i].brightness = 0x60;
		i++;
	}
}

static void		chose_button(t_data *data)
{
//	if (data->sdl->mouse.is_moved == FALSE)
//		return;
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
		load_game(data);
	if (data->menu.pressed_button == B_EXIT)
		remove_data(data);
	if (data->menu.pressed_button == B_LEVEL_EDITOR)
		level_editor(data);
}

void		move_mouse(t_data *data)
{
	int		i;

	i = 0;
	if (data->sdl->mouse.is_moved == FALSE)
		return;
	while (i < B_COUNT)
	{
		if (data->sdl->mouse.x > data->menu.buttons[i].x && data->sdl->mouse.x < data->menu.buttons[i].x + data->menu.buttons[i].width)
		{
			if (data->sdl->mouse.y > data->menu.buttons[i].y && data->sdl->mouse.y < data->menu.buttons[i].y + data->menu.buttons[i].height)
			{
				data->menu.pressed_button = i;
				break ;
			}
		}
		i++;
	}
}

void		menu_condition(t_data *data)
{
	prepare_buttons(data);
	move_mouse(data);
	chose_button(data);
	chose_layers(data);
	change_condition(data);
	update_texture(data);
}
