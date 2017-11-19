/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:04:55 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 21:33:03 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <math.h> 
#include "utility.h"
#include "sdl.h"

t_player			player(void)
{
	t_player		p;

	p.pos = vertex(0, 0);
	p.angle = 0;
	p.sin = sinf(p.angle);
	p.cos = cosf(p.angle);
	p.z = 6;
	p.sector = 0;
	return (p);
}

inline t_vertex		player_coords(t_player p, t_vertex v)
{
	t_vertex	n;

	n = v_sub(v, p.pos);
	n = rotate_vertex(n, p.cos, p.sin);
	return (rotate_vertex(v_sub(v, p.pos), p.cos, p.sin));
}

inline void			player_rotate(t_player *p, float angle)
{
	p->angle += angle;
	p->sin = sinf(p->angle);
	p->cos = cosf(p->angle);
}

inline void			player_move(t_sdl *s, t_player *p, float amp)
{
	int				i;
	t_sector		*sect;
	t_vertex		*v;
	t_vertex		d;

	d = INIT_VERTEX(p->cos * 0.2 * amp, p->sin * 0.2 * amp);
	sect = &s->sectors[p->sector];
	v = sect->vertices;
	i = -1;
	while ((unsigned)++i < sect->num_vertices - 1)
		if (sect->neighbors[i] >= 0
		&& INTER_BOX(p->pos, V_ADD(p->pos, d), v[i], v[i+1])
		&& POINT_SIDE(V_ADD(p->pos, d), v[i], v[i+1]) < 0)
		{
			p->sector = sect->neighbors[i];
			break ;
		}
	p->pos = V_ADD(p->pos, d);
}
