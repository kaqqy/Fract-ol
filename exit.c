/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:05:19 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 21:11:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_prog(t_env *env, char *msg)
{
	env ? 0 : exit(1);
	free(env->threads);
	free(env->colors);
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	free(env->mlx);
	ft_putstr_fd(msg, 2);
	*msg ? exit(1) : exit(0);
}
