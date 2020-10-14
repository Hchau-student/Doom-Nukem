//
// Created by Hugor Chau on 10/14/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

void		change_button_brightness(t_button *button)
{
	int		i;
	int		border;

	i = 0;
	border = button->texture->height * button->texture->width;
	while (i < border)
	{
		if (button->texture->bit_map[i] >> 24 != 0)
			button->texture->bit_map[i] = button->brightness << 24 | button->texture->bit_map[i] << 8 >> 8;
		i++;
	}
}

void			prepare_all_buttons(t_button *buttons, int32_t count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		buttons[i].brightness = 0x60;
		i++;
	}
}

void		buttons_move_mouse(t_button *buttons, int8_t max_size, t_mouse *mouse, int8_t *change)
{
	int				i;
	t_button		*iter_buttons;

	iter_buttons = buttons;
	i = 0;
	while (i < max_size)
	{
		if (mouse->x > iter_buttons[i].x && mouse->x < iter_buttons[i].x + iter_buttons[i].width)
		{
			if (mouse->y > iter_buttons[i].y && mouse->y < iter_buttons[i].y + iter_buttons[i].height)
			{
				*change = i;
				return ;
			}
		}
		i++;
	}
}

//void		init_buttons(t_data *data, t_button *buttons, int8_t count, char **name)
//{
//	int			i;
//
//	i = 0;
//	while (i < count)
//	{
//		buttons[i].height = 50;
//		buttons[i].width = 50;
//		buttons[i].x = SCREEN_WIDTH - 70;
//		buttons[i].y = 70 * i + 20;
//		buttons[i].borders.start = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
//		buttons[i].borders.end = (t_vec2){SCREEN_WIDTH - 70, 70 * i + 20};
//		buttons[i].borders.end.x += 50;
//		buttons[i].borders.end.y += 50;
//		buttons[i].texture = find_texture_by_name(name[i], data);
//		i++;
//	}
//}
