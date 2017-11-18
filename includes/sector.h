/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:04:24 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 02:20:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

# include "vertex.h"

typedef struct		s_sector
{
	float			ceil;
	float			floor;
	t_vertex		*vertices;
	int				*neighbors;
	unsigned		num_vertices;
}					t_sector;

t_sector			*parse(char *path);

#endif
