/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:32:03 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 22:34:33 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_point(t_env *env, int x, int y, int color)
{
	int		ind;

	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_WID)
		return ;
	ind = env->sl * y + env->bpp * x;
	env->data[ind + (env->endian ? (env->bpp - 1) : 0)] = color % 256;
	env->data[ind + (env->endian ? (env->bpp - 2) : 1)] = (color >> 8) % 256;
	env->data[ind + (env->endian ? (env->bpp - 3) : 2)] = (color >> 16) % 256;
}
