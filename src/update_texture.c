//
// Created by Hugor Chau on 9/25/20.
//
#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"
#include "../SDL/include/SDL.h"

void	put_layer(SDL_Texture *texture, uint32_t *bitmap, uint32_t width, t_data *data)
{
	SDL_SetRenderTarget(data->sdl->rend, data->sdl->target_texture);

	safe_call_int(SDL_UpdateTexture(texture,
			data->sdl->rect,
			bitmap,
			width * sizeof(uint32_t)),
			"Texture update failed", data);
	safe_call_int(SDL_RenderCopy( data->sdl->rend , texture,
			NULL, NULL ),
			"Can't clear render.", data);
	SDL_SetRenderTarget(data->sdl->rend, NULL);
	safe_call_int(SDL_RenderCopy(data->sdl->rend,
			data->sdl->target_texture, NULL, NULL),
			"Can't render texture.", data);

}

void	update_texture(t_data *data)
{
//	put_layer(data->sdl->tex,
//			data->textures[1]->bit_map,
//			  data->textures[1]->width,
//			data);
//	put_layer(data->sdl->tex,
//			  data->sdl->layers->hud->bit_map,
//			  data->sdl->layers->hud->width,
//			  data);
//	put_layer(data->sdl->tex,
//			  data->sdl->layers->minimap->bit_map,
//			  data->sdl->layers->minimap->width,
//			  data);
	SDL_RenderPresent(data->sdl->rend);
}
