/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:30:11 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:09:36 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

#include "player.h"
#include "utility.h"
#include "sdl.h"

void		detect_sector_change(t_sdl *s, t_player *p, t_vertex d);
t_vertex	horisontal_collision(t_sdl *s, t_player *p, t_vertex d);
void		vertical_collision(t_sdl *s, t_player *p);

#endif
