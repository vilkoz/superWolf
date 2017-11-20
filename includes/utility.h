/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:50:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:53:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include "vertex.h"
# include "player.h"

# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define CLAMP(x, a, b) MIN(MAX(x, a), b)
# define CROSS(xa, ya, xb, yb) ((xa) * (yb) - (ya) * (xb))
# define OVERLAP(a, b, c, d) (MIN(a, b) <= MAX(c, d) && MIN(c, d) <= MAX(a, b))
# define POINT_SIDE(a, b, c) (v_cross(v_sub(c, b), v_sub(a, b)))
# define O(a, b, c, d) OVERLAP(a, b, c, d)
# define INTER_BOX(a, b, c, d) (O(a.x, b.x, c.x, d.x) && O(a.y, b.y, c.y, d.y))
# define NEAR_Z (1e-4)
# define NEAR_X (1e-5)
# define FAR_Z (5.0)
# define FAR_X (20.0)

int				perspective_transform(t_vertex v, float *floor, float *ceil,
					t_player p);
t_vertex		rotate_vertex(t_vertex v, float cosa, float sina);
t_vertex		intersect_lines(t_vertex p1, t_vertex p2, t_vertex p3,
						t_vertex p4);
void			clip_wall(t_vertex *v1, t_vertex *v2);
int				linear_interpolate(int x, t_vertex p1, t_vertex p2);

#endif
