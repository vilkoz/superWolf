/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:26:41 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 01:39:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"
#include "configs.h"
#include "collision.h"
#include "drawer.h"
#include "libft.h"

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		perror(SDL_GetError());
		exit(1);
	}
	if ((sdl->win = SDL_CreateWindow("wolf == duke", 0, 0, W, H, 0)) == NULL)
	{
		perror(SDL_GetError());
		exit(1);
	}
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	sdl->quit = 0;
	sdl->player = player();
	ft_bzero((void*)&sdl->keys, sizeof(t_keys));
	SDL_SetRelativeMouseMode(1);
}

void	close_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->surface);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	handle_mouse(t_sdl *s)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	s->player.yaw += y * 0.02f;
	if (x != 0)
		player_rotate(&s->player, (x * 0.5f) / 90.0f);
}

void	handle_events(t_sdl *s)
{
	SDL_Event		e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			s->quit = 1;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			(SYM(e) == SDLK_w) ? s->keys.w = e.type == SDL_KEYDOWN : 0;
			(SYM(e) == SDLK_a) ? s->keys.a = e.type == SDL_KEYDOWN : 0;
			(SYM(e) == SDLK_s) ? s->keys.s = e.type == SDL_KEYDOWN : 0;
			(SYM(e) == SDLK_d) ? s->keys.d = e.type == SDL_KEYDOWN : 0;
			(SYM(e) == SDLK_SPACE) ? s->keys.space = e.type == SDL_KEYDOWN : 0;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (SYM(e) == SDLK_q)
				SDL_SetRelativeMouseMode(!(s->keys.q ^= 1));
			(SYM(e) == SDLK_ESCAPE) ? s->quit = 1 : 0;
		}
	}
	(!s->keys.q) ? handle_mouse(s) : 0;
	(s->keys.w) ? player_move(s, &s->player, 2.5) : 0;
	(s->keys.s) ? player_move(s, &s->player, -2.5) : 0;
	(s->keys.a) ? player_rotate(&s->player, -10.0/90.0) : 0;
	(s->keys.d) ? player_rotate(&s->player, 10.0/90.0) : 0;
	(s->keys.space) ? player_jump(&s->player) : 0;
	vertical_collision(s, &s->player);
}

int		main(void)
{
	t_sdl		s;

	s.sectors = parse("map.txt", &s.num_sectors);
	init_sdl(&s);
	while (!s.quit)
	{
		SDL_FillRect(s.surface, NULL, 0);
		draw_sectors(&s, s.sectors, s.player);
		handle_events(&s);
		SDL_UpdateWindowSurface(s.win);
		SDL_Delay(100);
	}
	close_sdl(&s);
	return (0);
}
