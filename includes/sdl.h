/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:29:03 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 23:18:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_H
# define SDL_H

# include <SDL2/SDL.h>
# include "player.h"
# include "sector.h"

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*surface;
	char		quit;
	t_sector	*sectors;
	t_player	player;
	SDL_Window	*win2;
	SDL_Renderer	*r;
}				t_sdl;

#endif
