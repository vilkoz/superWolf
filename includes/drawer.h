/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:55:53 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 20:43:36 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWER_H
# define DRAWER_H

#include "sdl.h"

typedef struct	s_wall
{
	t_vertex	v1;
	t_vertex	v2;
	float		floor;
	float		ceil;
	int			next;
}				t_wall;

typedef struct	s_ivertex
{
	int			x;
	int			y;
}				t_ivertex;

/*
** perspective wall struct
*/

typedef struct	s_ipwall
{
	t_ivertex	v1;
	t_ivertex	v2;
	t_ivertex	n1;
	t_ivertex	n2;
}				t_ipwall;

typedef struct	s_pwall
{
	t_vertex	x;
	t_vertex	v1;
	t_vertex	v2;
	t_vertex	n1;
	t_vertex	n2;
	int			next;
}				t_pwall;

typedef t_pwall	T;

# define INIT_WALL(v1, v2, f, c, n) ((t_wall) {v1, v2, f, c, n})
# define INIT_IVERTEX(x, y) ((t_ivertex) {(x), (y)})
# define IVERTEX_TO_V(v) ((t_vertex) {((float)v.x), ((float)v.y)})

/*
** just to buypass one line macro and 4 arg function restriction, sorry
*/

# define V(v) IVERTEX_TO_V(v)
# define IPWALL_TO_P(w, x, n) ((T){V(x), V(w.v1), V(w.v2), V(w.n1), V(w.n2), n})

void			draw_vline(t_sdl *s, t_vertex v1, t_vertex v2, unsigned color);
void			init_neighbor(t_ipwall *borders, t_wall w, t_sector s,
					t_player p);
void			draw_neighbor(t_sdl *s, t_pwall w, int i, t_ivertex v);
void			draw_sectors(t_sdl *s, t_sector *sectors, t_player p);

#endif
