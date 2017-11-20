/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 00:22:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:39:57 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"
#include "libft.h"

t_sector	sector(float ceil, float floor)
{
	t_sector	s;

	s.ceil = ceil;
	s.floor = floor;
	s.neighbors = NULL;
	s.num_vertices = 0;
	return (s);
}

void		sector_add_vertex(t_sector *s, t_vertex v, int neighbor)
{
	s->neighbors = ft_realloc(s->neighbors, sizeof(int) * s->num_vertices, 
		sizeof(int) * (s->num_vertices + 1));
	s->vertices = ft_realloc(s->vertices, sizeof(t_vertex) * s->num_vertices, 
		sizeof(t_vertex) * (s->num_vertices + 1));
	s->num_vertices++;
	s->vertices[s->num_vertices - 1] = v;
	s->neighbors[s->num_vertices - 1] = neighbor;
}
