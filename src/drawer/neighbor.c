/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:40:06 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/20 23:22:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawer.h"
#include "player.h"
#include "configs.h"
#include "utility.h"

void		draw_neighbor(t_sdl *s, t_pwall w, int i, t_ivertex v)
{
	int		ya;
	int		yb;


	ya = linear_interpolate(i, vertex(w.x.x, w.n1.x),
			vertex(w.x.y, w.n2.x));
	ya = CLAMP(ya, 0, H);
	yb = linear_interpolate(i, vertex(w.x.x, w.n1.y),
			vertex(w.x.y, w.n2.y));
	yb = CLAMP(yb, 0, H);
	draw_vline(s, vertex(i, v.x), vertex(i, ya - 1), 0x097df9);
	(ya > v.x) ? draw_vline(s, vertex(i, ya - 1), vertex(i, ya), 0xffffff) : 0;
	s->ystart[i] = CLAMP(MAX(ya, v.x), s->ystart[i], H - 1);
	(yb < v.y) ? draw_vline(s, vertex(i, yb), vertex(i, yb + 1), 0xffffff) : 0;
	draw_vline(s, vertex(i, yb + 1), vertex(i, v.y), 0x097df9);
	s->yend[i] = CLAMP(MIN(yb, v.y), 0, s->yend[i]);
}

void		init_neighbor(t_ipwall *borders, t_wall w, t_sector s, t_player p)
{
	borders->n1 = INIT_IVERTEX(s.ceil - p.z, s.floor - p.z);
	borders->n2 = INIT_IVERTEX(s.ceil - p.z, s.floor - p.z);
	perspective_transform(w.v1, &borders->n1.x, &borders->n1.y, p);
	perspective_transform(w.v2, &borders->n2.x, &borders->n2.y, p);
}
