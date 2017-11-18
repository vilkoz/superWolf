/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:50:47 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 13:38:08 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include "vertex.h"

# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define CLAMP(x, a, b) MIN(MAX(x, a), b)
# define CROSS(xa, ya, xb, yb) ((xa) * (yb) - (ya) * (xb))
# define OVERLAP(a, b, c, d) (MIN(a, b) <= MAX(c, d) && MIN(c, d) <= MAX(a, b))
# define NEAR_Z (1e-4)
# define NEAR_X (1e-5)
# define FAR_Z (5.0)
# define FAR_X (20.0)

int				perspective_transform(t_vertex v, int *floor, int *ceil);
t_vertex		rotate_vertex(t_vertex v, float cosa, float sina);
t_vertex		intersect_lines(t_vertex p1, t_vertex p2, t_vertex p3,
						t_vertex p4);
void			clip_wall(t_vertex *v1, t_vertex *v2);
int				linear_interpolate(int x, t_vertex p1, t_vertex p2);

#endif
