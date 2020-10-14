//
// Created by Hugor Chau on 9/15/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

void	main_loop(t_data *data)
{
	int quit = 0;
	SDL_Event event;

//    int KEYS[322]; если нужно запомнить клаву, крутой пример
	while(!quit) {
		data->go_to->condition(data);
		while (SDL_PollEvent(&event))
		{
			mouse_event(&event, data);
//			SDL_PumpEvents(); // обработчик событий.
			if(event.type == SDL_QUIT)
				quit=1;
			if (quit == 1) {
				remove_data(data);
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				key_event(&event, data);
			}
			if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				key_event(&event, data);
			}
		}
	}
	remove_data(data);
}
