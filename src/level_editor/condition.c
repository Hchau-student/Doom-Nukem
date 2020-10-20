//
// Created by Hugor Chau on 10/9/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void			draw_palette(t_data *data)
{
	t_square		borders;

	borders.start = (t_vec2){0.0, 0.0};
	borders.end = (t_vec2){200.0, SCREEN_HEIGHT - 1};
	scale_image(data->level_editor->palette.background, data->sdl->layers->level_editor, borders);
}

static void		chose_layers(t_data *data, t_level_editor *l)
{
	int		i;

	i = 0;
	put_layer(data->sdl->tex,
			  l->background->bit_map,
			  l->background->width,
			  data);
	while (i < BL_CONTRL_MAX)
	{
		change_button_brightness(&l->control_buttons->buttons[i]);
		scale_image(l->control_buttons->buttons[i].texture,
			data->sdl->layers->level_editor,
			l->control_buttons->buttons[i].borders);
		i++;
	}
	draw_minimap(data);
	draw_palette(data);
	if (l->curr_action)
		l->curr_action(data);
	put_layer(data->sdl->tex,
		  data->sdl->layers->minimap->bit_map,
		  data->sdl->layers->minimap->width,
		  data);
	put_layer(data->sdl->tex,
			  data->sdl->layers->level_editor->bit_map,
			  data->sdl->layers->level_editor->width,
			  data);
//	put_layer(data->sdl->tex,
//			  data->level_editor->palette.background->bit_map,
//			  data->level_editor->palette.background->width,
//			  data);
}

static void		chose_button(t_control_buttons *buttons)
{
	if (buttons->curr_button >= 0 && buttons->curr_button < BL_CONTRL_MAX)
		buttons->buttons[buttons->curr_button].brightness = 0xFF;
	if (buttons->pressed_button >= 0 && buttons->pressed_button < BL_CONTRL_MAX)
		buttons->buttons[buttons->pressed_button].brightness = 0xFF;
}

void		palette_chose_object(t_data *data)
{
	if (data->level_editor->curr_action == BL_DRAW_OBJ)
	{
//		chose_curr_obj;
		data->level_editor->palette.curr_obj = PD_WALL;
	}
}

void		rescale_le_map(t_data *data)
{
	t_vec2		last_start;

	last_start.x = data->engine->minimap->start_from.x / data->engine->minimap->size_divider;
	last_start.y = data->engine->minimap->start_from.y / data->engine->minimap->size_divider;
	if (data->sdl->mouse.is_scrolled_in)
	{
		if (data->engine->minimap->size_divider < 1)
			data->engine->minimap->size_divider += data->engine->minimap->size_divider / 50;
	}
	if (data->sdl->mouse.is_scrolled_out)
	{
		if (data->engine->minimap->size_divider > 0.05)
			data->engine->minimap->size_divider -= data->engine->minimap->size_divider / 50;
	}
	data->engine->minimap->start_from.x = last_start.x * data->engine->minimap->size_divider;
	data->engine->minimap->start_from.y = last_start.y * data->engine->minimap->size_divider;
	if (data->engine->minimap->size_divider > 1)
		data->engine->minimap->size_divider = 1;
}

void		level_editor_condition(t_data *data)
{
	t_level_editor		*l;

	rescale_le_map(data);
	l = data->level_editor;
	prepare_all_buttons(l->control_buttons->buttons, BL_CONTRL_MAX);
	l->control_buttons->curr_button = -1;
	buttons_move_mouse(l->control_buttons->buttons,
					BL_CONTRL_MAX, &data->sdl->mouse, &l->control_buttons->curr_button);
	chose_button(l->control_buttons);
	le_change_condition(data, data->level_editor->control_buttons->curr_button);
	chose_layers(data, l);
	update_texture(data);
}
