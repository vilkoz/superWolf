/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:29:32 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/20 22:58:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h> 
#include "collision.h"

void		detect_sector_change(t_sdl *s, t_player *p, t_vertex d)
{
	int				i;
	t_sector		*sect;
	t_vertex		*v;

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
}

t_vertex	horisontal_collision(t_sdl *s, t_player *p, t_vertex d)
{
	int				i;
	t_vertex		*v;
	t_vertex		wall;
	t_vertex		tmp;

	v = s->sectors[p->sector].vertices;
	i = -1;
	while ((unsigned)++i < s->sectors[p->sector].num_vertices - 1)
		if (INTER_BOX(p->pos, V_ADD(p->pos, d), v[i], v[i + 1])
		&& POINT_SIDE(V_ADD(p->pos, d), v[i], v[i + 1]) < 0)
		{
			/* TODO: check bumping into top or bottom wall */
			wall = v_sub(v[i], v[i + 1]);
			tmp = d;
			d.x = wall.x * V_DOT(tmp, wall) / V_SQR(wall);
			d.y = wall.y * V_DOT(tmp, wall) / V_SQR(wall);
		}
	return (d);
}
