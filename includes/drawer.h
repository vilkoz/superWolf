/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:55:53 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 15:02:45 by vrybalko         ###   ########.fr       */
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
}				t_wall;

typedef struct	s_ivertex
{
	int			x;
	int			y;
}				t_ivertex;

# define INIT_WALL(v1, v2, f, c) ((t_wall) {v1, v2, f, c})
# define INIT_IVERTEX(x, y) ((t_ivertex) {(x), (y)})
# define IVERTEX_TO_V(v) ((t_vertex) {((float)v.x), ((float)v.y)})

void			draw_sectors(t_sdl *s, t_sector *sectors, t_player p);

#endif
