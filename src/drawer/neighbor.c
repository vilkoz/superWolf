/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:40:06 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 22:19:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer.h"
#include "player.h"
#include "configs.h"
#include "utility.h"
#include "sdl.h"

void		draw_vline(t_sdl *s, t_vertex v1, t_vertex v2, unsigned color)
{
	SDL_Rect		rect;

	rect.x = (int)MIN(v1.x, v2.x);
	rect.y = (int)v1.y;
	rect.w = 1;
	rect.h = (int)v2.y - rect.y;
	SDL_FillRect(s->surface, &rect, color);
}

void		draw_neighbor(t_sdl *s, t_pwall w, int i, t_ivertex v)
{
	int		ya;
	int		yb;


	ya = linear_interpolate(i, vertex(w.x.x, w.n1.x),
			vertex(w.x.y, w.n2.x));
	ya = CLAMP(ya, s->ystart[i], s->yend[i]);
	yb = linear_interpolate(i, vertex(w.x.x, w.n1.y),
			vertex(w.x.y, w.n2.y));
	yb = CLAMP(yb, s->ystart[i], s->yend[i]);
	draw_vline(s, vertex(i, v.x), vertex(i, ya - 1), CNEIG);
	(ya > v.x) ? draw_vline(s, vertex(i, ya - 1), vertex(i, ya), CBORD) : 0;
	s->ystart[i] = CLAMP(MAX(ya, v.x), s->ystart[i], H - 1);
	(yb < v.y) ? draw_vline(s, vertex(i, yb), vertex(i, yb + 1), CBORD) : 0;
	draw_vline(s, vertex(i, yb + 1), vertex(i, v.y), CNEIG);
	s->yend[i] = CLAMP(MIN(yb, v.y), 0, s->yend[i]);
}

void		init_neighbor(t_pwall *borders, t_wall w, t_sector s, t_player p)
{
	borders->n1 = INIT_VERTEX(s.ceil - p.z, s.floor - p.z);
	borders->n2 = INIT_VERTEX(s.ceil - p.z, s.floor - p.z);
	perspective_transform(w.v1, &borders->n1.x, &borders->n1.y, p);
	perspective_transform(w.v2, &borders->n2.x, &borders->n2.y, p);
}
