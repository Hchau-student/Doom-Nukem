#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

/*
**		TODO: SCREEN_WIDTH / 2 - 50? Seriously?
**		Do you want to add some defines?
*/

static void		draw_player_icon(t_display_hud *hud, t_data *data)
{
	t_vec2		start;
	t_vec2		end;
	int			health;

	start.x = SCREEN_WIDTH / 2 - 40;
	start.y = SCREEN_HEIGHT - 70;
	end.x = SCREEN_WIDTH / 2 + 40;
	end.y = SCREEN_HEIGHT - 1;
	if (hud->health < 0 || hud->health > 100)
		safe_call_int(-1, "player\'s health is incorrect.", data);
	if (hud->state < 0 || hud->state > 4)
		safe_call_int(-1, "Error in player\'s state. "
		"Nor PLAYER_NORMAL | PLAYER_HURT | PLAYER_KILL |"
		"PLAYER_LEFT | PLAYER_RIGHT. Check this out, please.", data);
	if (hud->health > 80)
		health = HEALTH_100;
	else if (hud->health > 60)
		health = HEALTH_80;
	else if (hud->health > 40)
		health = HEALTH_60;
	else if (hud->health > 20)
		health = HEALTH_40;
	else
		health = HEALTH_20;
	safe_call_int(scale_image(hud->player_texture[health][hud->state], data->sdl->layers->hud,
	(t_square){start, end}), "Borders (start and end coordinates for scale)"
	" are incorrect. Crashed in \"src/engine/draw_hud.c\" (icon).", data);
}

void			draw_weapon(t_display_hud *hud, t_data *data)
{
	t_vec2		start_point;
	t_vec2		end_point;

	start_point.x = SCREEN_WIDTH / 2 - 70;
	start_point.y = SCREEN_HEIGHT - 170;
	end_point.x = SCREEN_WIDTH / 2 + 70;
	end_point.y = SCREEN_HEIGHT - 1 - 70;
	safe_call_int(scale_image(hud->weapon->texture[hud->weapon->frame], data->sdl->layers->hud,
	(t_square){start_point, end_point}),
	"Borders (start and end coordinates for scale)"
	" are incorrect. Crashed in \"src/engine/draw_hud.c\" (weapon).", data);
}

void			draw_hud(t_display_hud *hud, t_data *data)
{
	draw_weapon(hud, data);
	draw_player_icon(hud, data);
}
