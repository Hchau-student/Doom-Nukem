#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

void			draw_hud(t_display_hud *hud, t_data *data)
{
	t_vec2		start;
	t_vec2		end;
	int			health;

	start.x = SCREEN_WIDTH / 2 - 50;
	start.y = SCREEN_HEIGHT - 100;
	end.x = SCREEN_WIDTH / 2 + 50;
	end.y = SCREEN_HEIGHT - 1;
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
	safe_call_int(scale_image(hud->player_texture[health][hud->state],
	data, start, end), "Borders (start and end coordinates for scale)"
	" are incorrect. Crashed in \"src/engine/draw_hud.c\".", data);
}
