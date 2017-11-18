/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:08:05 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 23:46:27 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"
#include <stdlib.h>

t_sector	*parse(char *path)
{
	t_sector	*s;

	(void)path;
	s = (t_sector*)malloc(sizeof(t_sector) * 1);
	s[0].ceil = 10;
	s[0].floor = 0;
	s[0].vertices = (t_vertex*)malloc(sizeof(t_vertex) * 5);
	s[0].neighbors = (int*)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
		s[0].neighbors[i] = -1;
	s[0].vertices[0] = vertex(10, 10);
	s[0].vertices[1] = vertex(-10, 10);
	s[0].vertices[2] = vertex(-10, -10);
	s[0].vertices[3] = vertex(10, -10);
	s[0].vertices[4] = vertex(10, 10);
	s[0].num_vertices = 5;
	return (s);
}
