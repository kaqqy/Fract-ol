/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:42:59 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 21:31:34 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			motion_hook(int x, int y, t_env *env)
{
	if (env->move >= 0)
	{
		env->c.re += (x - env->cx) * env->pixel_len;
		env->c.im += (y - env->cy) * env->pixel_len;
		env->cx = x;
		env->cy = y;
		env->move = 1;
		draw_fractal(env);
	}
	return (0);
}

int			key_release_hook(int k, t_env *env)
{
	if (env->move >= 0 || !((k > 122 && k < 127) || k == 53 || k == 24 ||
			k == 27 || k == 30 || k == 33 || k == 43 || k == 47))
		return (0);
	(k == 123) ? (env->origin.re -= env->pixel_len * 50) : 0;
	(k == 124) ? (env->origin.re += env->pixel_len * 50) : 0;
	(k == 125) ? (env->origin.im += env->pixel_len * 50) : 0;
	(k == 126) ? (env->origin.im -= env->pixel_len * 50) : 0;
	(k == 53) ? exit_prog(env, "") : 0;
	(k == 24) ? (env->iter++) : 0;
	(k == 27) ? (env->iter = MAX(1, env->iter - 1)) : 0;
	(k == 30) ? (env->prec += 0.5) : 0;
	(k == 33) ? (env->prec = MAX(env->prec - 0.5, 0.0)) : 0;
	(k == 43) ? (env->color_rot = (env->color_rot + 1) % 1530) : 0;
	(k == 47) ? (env->color_rot = (env->color_rot + 1529) % 1530) : 0;
	draw_fractal(env);
	return (0);
}

int			mouse_press_hook(int b, int x, int y, t_env *env)
{
	if (b == 4)
	{
		env->origin.re -= env->pixel_len * x * (1.5 - 1);
		env->origin.im -= env->pixel_len * y * (1.5 - 1);
		env->pixel_len *= 1.5;
	}
	else if (b == 5)
	{
		env->origin.re -= env->pixel_len * x * (1 / 1.5 - 1);
		env->origin.im -= env->pixel_len * y * (1 / 1.5 - 1);
		env->pixel_len *= 1 / 1.5;
	}
	else if (b == 1)
	{
		env->cx = x;
		env->cy = y;
		env->move = 0;
		return (0);
	}
	else
		return (0);
	draw_fractal(env);
	return (0);
}

int			mouse_release_hook(int b, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (b == 1)
	{
		if (!env->move)
		{
			env->c = (t_complex){env->origin.re + x * env->pixel_len,
					env->origin.im + y * env->pixel_len};
			draw_fractal(env);
		}
		env->move = -1;
	}
	return (0);
}

int			expose_hook(t_env *env)
{
	draw_fractal(env);
	return (0);
}
