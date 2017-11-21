/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:08:05 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 02:12:54 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"
#include <stdlib.h>

t_sector	*parse(char *path, int *num)
{
	t_sector	*s;
	t_sector	tmp;

	(void)path;
	*num = 5;
	s = (t_sector*)malloc(sizeof(t_sector) * *num);
	tmp = sector(30, 0);
	sector_add_vertex(&tmp, vertex( 10,  10), -1);
	sector_add_vertex(&tmp, vertex(-10,  10), -1);
	sector_add_vertex(&tmp, vertex(-10, -10), -1);
	sector_add_vertex(&tmp, vertex( -5, -10),  4);
	sector_add_vertex(&tmp, vertex(  5, -10), -1);
	sector_add_vertex(&tmp, vertex( 10, -10), -1);
	sector_add_vertex(&tmp, vertex( 10,  -5),  1);
	sector_add_vertex(&tmp, vertex( 10,   5), -1);
	sector_add_vertex(&tmp, vertex( 10,  10), -1);
	s[0] = tmp;
	tmp = sector(15, 1);
	sector_add_vertex(&tmp, vertex(40, -5), -1);
	sector_add_vertex(&tmp, vertex(40,  5), -1);
	sector_add_vertex(&tmp, vertex(10,  5),  0);
	sector_add_vertex(&tmp, vertex(10, -5), -1);
	sector_add_vertex(&tmp, vertex(15, -5),  2);
	sector_add_vertex(&tmp, vertex(35, -5), -1);
	sector_add_vertex(&tmp, vertex(40, -5), -1);
	s[1] = tmp;
	tmp = sector(20, 5);
	sector_add_vertex(&tmp, vertex(35,  -5),  1);
	sector_add_vertex(&tmp, vertex(15,  -5), -1);
	sector_add_vertex(&tmp, vertex(15, -15),  3);
	sector_add_vertex(&tmp, vertex(15, -25), -1);
	sector_add_vertex(&tmp, vertex(35, -25), -1);
	sector_add_vertex(&tmp, vertex(35,  -5), -1);
	s[2] = tmp;
	tmp = sector(25, 10);
	sector_add_vertex(&tmp, vertex(15, -15), -1);
	sector_add_vertex(&tmp, vertex( 5, -15),  4);
	sector_add_vertex(&tmp, vertex( 5, -25), -1);
	sector_add_vertex(&tmp, vertex(15, -25),  2);
	sector_add_vertex(&tmp, vertex(15, -15), -1);
	s[3] = tmp;
	tmp = sector(30, 15);
	sector_add_vertex(&tmp, vertex( 5, -15), -1);
	sector_add_vertex(&tmp, vertex( 5, -10),  0);
	sector_add_vertex(&tmp, vertex(-5, -10), -1);
	sector_add_vertex(&tmp, vertex(-5, -25), -1);
	sector_add_vertex(&tmp, vertex( 5, -25),  3);
	sector_add_vertex(&tmp, vertex( 5, -15), -1);
	s[4] = tmp;
	return (s);
}
